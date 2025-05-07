#include "task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "robot.h"

Task tasks[MAX_TASKS];
int taskCount = 0;

static int countComponents(const int components[10]) {
    int count = 0;
    for (int i = 0; i < 10; i++) if (components[i] != 0) count++;
    return count;
}

void createTask(void) {
    if (taskCount >= MAX_TASKS) {
        printf("Error: Maximum tasks reached!\n");
        return;
    }
    Task newTask;
    newTask.id = taskCount + 1;
    int choice,top;
    int i=0;
    printf("Enter task description: ");
    fgets(newTask.description, sizeof(newTask.description), stdin);

    newTask.description[strcspn(newTask.description, "\n")] = '\0';

    printf("Component IDs Menu : \n");
do{

    printf("1. Component ID.\n");
    printf("2. Return To Task SubMenu.\n");
    scanf("%d",&choice);
    
    switch(choice){
        case 1:{
            while(i!=10){ printf("Enter the ID of the Component number %d :",i+1);
                scanf("%d",&newTask.components[i]);
                 i++; top=i;
                 if(top!=10){
                    for(int j=top+1;j<=10;j++){
                        newTask.components[j]=0;
                    }
                }if(i==10) printf("The Components are full.\n");
                 break;}
                    
            } break;
            
        case 2: printf("Returning to Task SubMenu... \n");break;}
        }while(choice!=2);


    newTask.stage = PENDING;
    newTask.robotAssigned = -1;
    newTask.startTime = time(NULL);
    newTask.endTime = 0;
    tasks[taskCount++] = newTask;
    printf("Task created! ID: %d | Components: %d | Status: PENDING\n", newTask.id, countComponents(newTask.components));
}

void updateTask(int id) {
    Task *task = getTaskById(id);
    if (!task) {
        printf("Error: Task %d not found!\n", id);
        return;
    }
    int choice,khyar,i,top;
    do {
        printf("Editing Task %d:\n");
        printf("1. Description\n");
        printf("2. Components\n");
        printf("3. Status\n");
        printf("4. Mark Completed\n");
        printf("5. Return\n");
        printf("Choose: ");
        scanf("%d",&choice);
        while(getchar()!='\n');
        switch (choice) {
            case 1:
                printf("Current: %s\nNew description: ", task->description);
                fgets(task->description, sizeof(task->description), stdin);
                task->description[strcspn(task->description, "\n")] = '\0';
                printf("\nDescription Edited Successfully.\n");
                break;
            case 2: {
                printf("Editing Component IDs Menu : \n");
                do{
                
                    printf("1. Edit Component ID.\n");
                    printf("2. Return To Task SubMenu.\n");
                    scanf("%d",&khyar);
                    
                    switch(khyar){
                        case 1:{
                            while(i!=10){ printf("Enter the ID of the Component number %d :",i+1);
                                scanf("%d",&task->components[i]);
                                 i++; top=i;
                                 if(top!=10){
                                    for(int j=top+1;j<=10;j++){
                                        task->components[j]=0;
                                    }
                                }if(i==10) printf("The Components are full.\n");
                                 break;}
                                    
                            } break;
                            
                        case 2: printf("Returning to Task SubMenu... \n");break;}
                        }while(khyar!=2);
                break;
            }
            case 3: {
                printf("New status (0=PENDING,1=ACTIVE,2=COMPLETED): ");
                int s; scanf("%d", &s); while(getchar()!='\n');
                if (s>=PENDING&&s<=COMPLETED) task->stage = s;
                if (task->stage==COMPLETED) task->endTime = time(NULL);
                printf("\nStatue Edited Successfully.\n");
                break;
            }
            case 4:
                task->stage = COMPLETED;
                task->endTime = time(NULL);
                if (task->robotAssigned != -1) {
                    Robot *r = viewRobotById(task->robotAssigned);
                    if (r) { r->tasksCompleted++; r->status = IDLE; }
                    printf("\nStatue Edited Successfully.\n");
                }
                break;
        }
    } while (choice != 5);
}

void deleteTask(int id) {
    int idx=-1;
    for(int i=0;i<taskCount;i++) if(tasks[i].id==id) {idx=i; break;}
    if (idx<0) { printf("Error: Task not found!\n"); return; }
    for(int i=idx;i<taskCount-1;i++) tasks[i]=tasks[i+1];
    taskCount--;
}

Task* getTaskById(int id) {
    for(int i=0;i<taskCount;i++) if(tasks[i].id==id) return &tasks[i];
    return NULL;
}

void listAllTasks(void) {
    if (!taskCount) { printf("No tasks available.\n"); return; }
    for(int i=0;i<taskCount;i++) printTaskDetails(&tasks[i]);
}

void searchTasksByStage(StageStatus status) {
    for(int i=0;i<taskCount;i++) if(tasks[i].stage==status) printTaskDetails(&tasks[i]);
}

void printTaskDetails(const Task *t) {
    if (!t) return;
    char buf[20];
    printf("\n=================================\n");
    printf("ID: %d\nDesc: %s\nStatus: %d\n",
           t->id, t->description, t->stage);
    strftime(buf,20,"%Y-%m-%d %H:%M:%S", localtime(&t->startTime));
    printf("Start: %s\n", buf);
    if (t->stage==COMPLETED) { strftime(buf,20,"%Y-%m-%d %H:%M:%S", localtime(&t->endTime)); printf("End: %s\n", buf); }
    printf("Components: ");
    for(int i=0;i<10;i++) if(t->components[i]) printf("%d ", t->components[i]);
    printf("\nRobot: %d\n", t->robotAssigned);
}

void assignTaskToRobot(void) {
    int tid, rid;
    printf("Task ID: ");
     if(scanf("%d",&tid)!=1){
        while(getchar()!='\n');return;}

    Task *t = getTaskById(tid);
     if(!t){printf("Task not found.\n");return;}

    printf("Robot ID: ");
     if(scanf("%d",&rid)!=1){
        while(getchar()!='\n');return;}

    Robot *r = viewRobotById(rid);
     if(!r){printf("Robot not found.\n");return;}

    t->robotAssigned = rid;
    r->status = WORKING;
    t->stage = ACTIVE;
    t->startTime = time(NULL);
    printf("Assigned Task %d to Robot %d.\n", tid, rid);
}
