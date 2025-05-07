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

    if (fwrite(&robotCount, sizeof(int), 1, file) != 1) goto write_error;
    if (fwrite(robots, sizeof(Robot), robotCount, file) != robotCount) goto write_error;

    if (fwrite(&taskCount, sizeof(int), 1, file) != 1) goto write_error;
    if (fwrite(tasks, sizeof(Task), taskCount, file) != taskCount) goto write_error;

    int queueSize = assemblyQueue.size;
    if (fwrite(&queueSize, sizeof(int), 1, file) != 1) goto write_error;
    
    QueueNode* current = assemblyQueue.front;
    while (current != NULL) {
        if (fwrite(&current->task, sizeof(Task), 1, file) != 1) goto write_error;
        current = current->next;
    }

    int stackSize = undoStack.size;
    if (fwrite(&stackSize, sizeof(int), 1, file) != 1) goto write_error;
    
    StackNode* stackCurrent = undoStack.top;
    while (stackCurrent != NULL) {
        if (fwrite(&stackCurrent->task, sizeof(Task), 1, file) != 1) goto write_error;
        stackCurrent = stackCurrent->next;
    }

    fclose(file);
    return 0;

write_error:
    perror("Error writing to file");
    fclose(file);
    return -1;
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

    if (fread(&robotCount, sizeof(int), 1, file) != 1) goto read_error;
    if (fread(robots, sizeof(Robot), robotCount, file) != robotCount) goto read_error;
    if (fread(&taskCount, sizeof(int), 1, file) != 1) goto read_error;
    if (fread(tasks, sizeof(Task), taskCount, file) != taskCount) goto read_error;
    int queueSize;
    if (fread(&queueSize, sizeof(int), 1, file) != 1) goto read_error;
    
    for (int i = 0; i < queueSize; i++) {
        Task task;
        if (fread(&task, sizeof(Task), 1, file) != 1) goto read_error;
        enqueue(task);
    }
    int stackSize;
    if (fread(&stackSize, sizeof(int), 1, file) != 1) goto read_error;
    
    for (int i = 0; i < stackSize; i++) {
        Task task;
        if (fread(&task, sizeof(Task), 1, file) != 1) goto read_error;
        pushUndo(task);
    }

    fclose(file);
    return 0;

read_error:
    perror("Error reading from file");
    fclose(file);
    return -1;
}