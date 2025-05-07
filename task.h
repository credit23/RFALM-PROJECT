#ifndef TASK_H
#define TASK_H

#include <time.h>

#define MAX_TASKS 1000 

typedef enum { PENDING, ACTIVE, COMPLETED } StageStatus;

typedef struct Task {
    int id;
    char description[200];
    StageStatus stage;
    int components[10];
    int robotAssigned;
    time_t startTime;
    time_t endTime;
} Task;

extern Task tasks[MAX_TASKS];
extern int taskCount;

void createTask(void);
void updateTask(int id);
void deleteTask(int id);
Task* getTaskById(int id);
void listAllTasks(void);
void searchTasksByStage(StageStatus status);
void printTaskDetails(const Task *task);
void assignTaskToRobot(void);

#endif

