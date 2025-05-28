#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "nav.h"
#include "task.h"
#include "tree.h"
#include "queue.h"
#include "production.h"


int saveSession(const char* filename);
int loadSession(const char* filename);


int main() {

    const char* saveFileName = "session.dat";

    TreeNode* factoryTree = createFactoryTree();  
    int choice;
    
    do {
        printf("\033[36m\n===============\033[33m RFALM Menu\033[36m ===============\n");
        printf("\033[36m1.\033[97m    Manage Robots \n");
        printf("\033[36m2.\033[97m    Manage Tasks \n");
        printf("\033[36m3.\033[97m    View & Control Task Queue \n");
        printf("\033[36m4.\033[97m    Assign Task to Robot \n");
        printf("\033[36m5.\033[97m    Undo Last Task (Stack) \n");
        printf("\033[36m6.\033[97m    Display Factory Structure Tree \n");
        printf("\033[36m7.\033[97m    View Production Summary \n");
        printf("\033[36m8.\033[97m    Save Session to File \n");
        printf("\033[36m9.\033[97m    Load Session from File \n");
        printf("\033[36m10.\033[97m   Exit \n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1: managerobotssubmenu(); break; 
            case 2: managetaskssubmenu(); break;
            case 3: controlQueueSubmenu(); break;
            case 4: assignTaskToRobot(); break;
            case 5: {
                Task undoneTask = popUndo();
                if(undoneTask.id != -1) {
                    enqueue(undoneTask);
                    printf("Undid task %d\n", undoneTask.id);
                }
                break;
            }
            case 6: displayFactoryTree(factoryTree, 0); break;
            case 7: generateProductionSummary(); break;
            case 8: 
            if(saveSession(saveFileName) == 0) {
                printf("Session saved to %s successfully!\n", saveFileName);
            } else {
                printf("Failed to save session!\n");
            }
            break;
        case 9: 
            if(loadSession(saveFileName) == 0) {
                printf("Session loaded from %s successfully!\n", saveFileName);
            } else {
                printf("Failed to load session!\n");
            }
            break;
            
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 10);


    freeQueue(&assemblyQueue);
    freeStack(&undoStack);
    freeFactoryTree(factoryTree);
    

    return 0;
}


int saveSession(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    if (fwrite(&robotCount, sizeof(int), 1, file) != 1 ||
        fwrite(robots, sizeof(Robot), robotCount, file) != robotCount ||
        fwrite(&taskCount, sizeof(int), 1, file) != 1 ||
        fwrite(tasks, sizeof(Task), taskCount, file) != taskCount) {
        perror("Error writing robots or tasks");
        fclose(file);
        return -1;
    }

    int queueSize = assemblyQueue.size;
    if (fwrite(&queueSize, sizeof(int), 1, file) != 1) {
        perror("Error writing queue size");
        fclose(file);
        return -1;
    }

    for (QueueNode* current = assemblyQueue.front; current; current = current->next) {
        if (fwrite(&current->task, sizeof(Task), 1, file) != 1) {
            perror("Error writing queue task");
            fclose(file);
            return -1;
        }
    }

    int stackSize = undoStack.size;
    if (fwrite(&stackSize, sizeof(int), 1, file) != 1) {
        perror("Error writing stack size");
        fclose(file);
        return -1;
    }

    for (StackNode* current = undoStack.top; current; current = current->next) {
        if (fwrite(&current->task, sizeof(Task), 1, file) != 1) {
            perror("Error writing stack task");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

int loadSession(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return -1;
    }

    freeQueue(&assemblyQueue);
    freeStack(&undoStack);
    robotCount = 0;
    taskCount = 0;

    if (fread(&robotCount, sizeof(int), 1, file) != 1 ||
        fread(robots, sizeof(Robot), robotCount, file) != robotCount ||
        fread(&taskCount, sizeof(int), 1, file) != 1 ||
        fread(tasks, sizeof(Task), taskCount, file) != taskCount) {
        perror("Error reading robots or tasks");
        fclose(file);
        return -1;
    }

    int queueSize = 0;
    if (fread(&queueSize, sizeof(int), 1, file) != 1) {
        perror("Error reading queue size");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < queueSize; i++) {
        Task task;
        if (fread(&task, sizeof(Task), 1, file) != 1) {
            perror("Error reading queue task");
            fclose(file);
            return -1;
        }
        enqueue(task);
    }

    int stackSize = 0;
    if (fread(&stackSize, sizeof(int), 1, file) != 1) {
        perror("Error reading stack size");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < stackSize; i++) {
        Task task;
        if (fread(&task, sizeof(Task), 1, file) != 1) {
            perror("Error reading stack task");
            fclose(file);
            return -1;
        }
        pushUndo(task);
    }

    fclose(file);
    return 0;
}
