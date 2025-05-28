#include "nav.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"
#include "task.h"
#include "queue.h"

extern TaskQueue assemblyQueue;
extern Robot robots[MAX_ROBOTS];
extern Task tasks[MAX_TASKS];
extern int robotCount;
extern int taskCount;

void managerobotssubmenu(void) {
    int choice = 0;
    do {
        printf("\n\033[36m=== \033[33m Manage Robots\033[36m ===\033[0m\n");
        printf("\033[36m1.\033[97m   Add New Robot\n");
        printf("\033[36m2.\033[97m   Edit Robot Information\n");
        printf("\033[36m3.\033[97m   Delete Robot\n");
        printf("\033[36m4.\033[97m   View Robot by ID\n");
        printf("\033[36m5.\033[97m   List All Robots\n");
        printf("\033[36m6.\033[97m   Search by Status (0-IDLE,1-WORKING,2-ERROR)\n");
        printf("\033[36m7.\033[97m   Show Work History\n");
        printf("\033[36m8.\033[97m   Reset Robot Status\n");
        printf("\033[36m9.\033[97m   Return to Main Menu\033[0m\n");
        printf("Choose an option: ");
        scanf("%d",&choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addRobot();
                break;
            case 2: {
                int id;
                int found=0;
                printf("Enter Robot ID to edit: ");
                scanf("%d",&id);
                for(int i=0;i<MAX_ROBOTS;i++){
                    if(robots[i].id==id){
                        editRobot(id);
                        found= 1 ;
                    }
                }if(!found) printf("Robot not found.\n");
                break;
            }
            case 3: {
                int id;
                int found=0;
                printf("Enter Robot ID to edit: ");
                scanf("%d",&id);
                for(int i=0;i<MAX_ROBOTS;i++){
                    if(robots[i].id==id){
                        deleteRobot(id);
                        found= 1 ;
                    }
                }if(!found) printf("Robot not found.\n");
                break;
            }
            case 4: {
                     int id;
                     printf("Enter Robot ID to view: ");
                     scanf("%d", &id);
                     Robot *robot = viewRobotById(id);
                        if (robot != NULL) {
                             printRobotDetails(robot);
                         } else {
                             printf("Robot not found.\n");
                         }
                     break;
            }
            case 5:
                listAllRobots();
                break;
            case 6: searchRobotsByStatus();
                break;
            
            case 7: {
                int id;
                int found=0;
                printf("Enter Robot ID: ");
                scanf("%d", &id);
                for(int i=0;i<MAX_ROBOTS;i++){
                    if(robots[i].id==i){
                        Robot *r =viewRobotById(id);
                        found=1;
                    }
                }if(!found) printf("Robot not found.");
                break;
            }
            case 8: 
            int id;
            int found=0;
            printf("Enter Robot ID to edit: ");
            scanf("%d",&id);
            for(int i=0;i<MAX_ROBOTS;i++){
                if(robots[i].id==id){
                    resetRobotStatus(id);
                    found++ ;
                }
       
            }if(!found) printf("Robot not found.\n");
            break;
            case 9:
                return;
            default:
                printf("Invalid choice! Please select 1-9.\n");
        }
    } while(choice!=9);
}

void managetaskssubmenu(void) {
    int choice = 0;
    do {
        printf("\n\033[36m=== \033[33m Manage Tasks\033[36m ===\033[0m\n");
        printf("\033[36m1.\033[97m   Create New Task\n");
        printf("\033[36m2.\033[97m   Update Task\n");
        printf("\033[36m3.\033[97m   Delete Task\n");
        printf("\033[36m4.\033[97m   View Task Details\n");
        printf("\033[36m5.\033[97m   List All Tasks\n");
        printf("\033[36m6.\033[97m   Search by Stage (0-PENDING,1-ACTIVE,2-COMPLETED)\n");
        printf("\033[36m7.\033[97m   Return to Main Menu\033[0m\n");
        printf("Choose an option: ");
        scanf("%d",&choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                createTask();
                break;
            case 2: {
                int id;
                int found = 0;
                printf("Enter Task ID to update: ");
                scanf("%d", &id); 
                    for (int i = 0; i < MAX_TASKS; i++) {
                        if (tasks[i].id == id) {
                            updateTask(id);
                            found = 1;
                            break;
                        }
                    }if (!found) printf("Task not found.\n");
                    break;
            }
            case 3: {
                int id;
                int found = 0;
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                    for (int i = 0; i < MAX_TASKS; i++) {
                        if (tasks[i].id == id) {
                            deleteTask(id);
                            found = 1;
                            break;
                        }
                    }if (!found) printf("Task not found.\n");
                break;
            }
            case 4: {
                int id;
                int found = 0;
                printf("Enter Task ID to view: ");
                scanf("%d", &id);
                    for (int i = 0; i < MAX_TASKS; i++) {
                        if (tasks[i].id == id) {
                            Task *t = getTaskById(id);
                                printTaskDetails(t);
                                found = 1;
                            break;
                        }
                    }if (!found) printf("Task not found.\n");
                break;
            }
            case 5:
                listAllTasks();
                break;
            case 6: {
                int stage;
                int found = 0;
                printf("Enter stage (0=PENDING,1=ACTIVE,2=COMPLETED): ");
                scanf("%d", &stage);
                    for (int i = 0; i < MAX_TASKS; i++) {
                        if (tasks[i].stage == stage) {
                            searchTasksByStage(stage);
                            found = 1;
                            break;
                        }
                    }if (!found) printf("Task not found.\n");
                break;
            }
            case 7:
                return;
            default:
                printf("Invalid choice! Please select 1-7.\n");
        }
    } while (choice != 7);
}

void controlQueueSubmenu(void) {
    int choice = 0;
    do {
        printf("\n\033[36m=== \033[33m Task Queue Control\033[36m ===\033[0m\n");
        printf("\033[36m1.\033[97m  View Queue\n");
        printf("\033[36m2.\033[97m  Add Task to Queue\n");
        printf("\033[36m3.\033[97m  Process Next Task\n");
        printf("\033[36m4.\033[97m  Clear Queue\n");
        printf("\033[36m5.\033[97m  Return to Main Menu\033[0m\n");
        printf("Choose an option: ");
        scanf("%d",&choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                displayQueue();
                break;
            case 2: {
                int id;
                int found = 0;
                printf("Enter Task ID to queue: ");
                scanf("%d", &id);
                    for (int i = 0; i < MAX_TASKS; i++) {
                        if (tasks[i].id == id) {
                            Task *t = getTaskById(id);
                                enqueue(*t);
                                found = 1;
                            }
                            break;
                        }if (!found) printf("Task not found.\n");
                break;
            }
            case 3: {
                Task processed = dequeue();
                if (processed.id != -1) {
                    printf("\nProcessing task %d:\n", processed.id);
                    printTaskDetails(&processed);
                } else {
                    printf("Queue is empty!\n");
                }
                break;
            }
            case 4:
                freeQueue(&assemblyQueue);
                printf("Queue cleared successfully!\n");
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please select 1-5.\n");
        }
    } while (choice != 5);
}