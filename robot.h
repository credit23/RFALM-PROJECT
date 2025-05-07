#ifndef ROBOT_H
#define ROBOT_H

#include <time.h>

#define MAX_ROBOTS 1000  

typedef enum { IDLE, WORKING, ERROR } RobotStatus;

typedef struct Robot {
    int id;
    char name[50];
    RobotStatus status;
    int tasksCompleted;
    time_t lastMaintenance;
    char tools[100];
} Robot;

extern Robot robots[MAX_ROBOTS];
extern int robotCount;

void addRobot(void);
void editRobot(int id);
void deleteRobot(int id);
void printRobotDetails(const Robot *robot);
void listAllRobots(void);
void searchRobotsByStatus(RobotStatus status);
void resetRobotStatus(int id);
void showWorkHistory(const Robot *robot);
Robot* viewRobotById(int id);

#endif 


