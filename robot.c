#include "robot.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

Robot robots[MAX_ROBOTS];
int robotCount = 0;

void addRobot(void) {
    if (robotCount >= MAX_ROBOTS) {
        printf("Maximum robots reached!\n");
        return;
    }
    Robot newRobot;
    newRobot.id = robotCount + 1;

    printf("Enter robot name: ");
    fgets(newRobot.name, sizeof(newRobot.name), stdin);
    newRobot.name[strcspn(newRobot.name, "\n")] = '\0';

    printf("Enter tools (comma-separated): ");
    fgets(newRobot.tools, sizeof(newRobot.tools), stdin);
    newRobot.tools[strcspn(newRobot.tools, "\n")] = '\0';

    newRobot.status = IDLE;
    newRobot.tasksCompleted = 0;
    newRobot.lastMaintenance = time(NULL);

    robots[robotCount++] = newRobot;
    printf("Robot added! ID: %d\n", newRobot.id);
}

void editRobot(int id) {
    int foundIndex = -1;
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].id == id) { foundIndex = i; break; }
    }
    if (foundIndex < 0) {
        printf("\n Error: Robot with ID %d not found!\n", id);
        return;
    }
    int choice;
    char buffer[100];
    do {
        printf("\n=== Editing Robot ID %d ===\n", id);
        printf("1. Edit Name\n");
        printf("2. Edit Tools\n");
        printf("3. Edit Status\n");
        printf("4. Return\n");
        printf("Choose: ");
        scanf("%d",&choice);
        while (getchar()!='\n');
        switch (choice) {
            case 1:
                printf("Current name: %s\nEnter new name: ", robots[foundIndex].name);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                strncpy(robots[foundIndex].name, buffer, sizeof(robots[foundIndex].name)-1);
                printf(" Name updated.\n");
                break;
            case 2:
                printf("Current tools: %s\nEnter new tools: ", robots[foundIndex].tools);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                strncpy(robots[foundIndex].tools, buffer, sizeof(robots[foundIndex].tools)-1);
                printf(" Tools updated.\n");
                break;
                case 3: {
                    printf("New status (0=IDLE,1=WORKING,2=ERROR): ");
                    int s; scanf("%d", &s); while(getchar()!='\n');
                    if (s>IDLE&&s<=ERROR) robots[foundIndex].status = s;
                    if(s==IDLE){
                        robots[foundIndex].status=s;
                        robots[foundIndex].lastMaintenance=time(NULL);
                    }
                    printf("\nStatue Edited Successfully.\n");
                    break;
                }
            case 4:
                return;
            default:
                printf(" Invalid choice!\n");
        }
    } while (choice != 3);
}

void deleteRobot(int id) {
    if (robotCount <= 0) {
        printf("Error: No robots to delete!\n");
        return;
    }
    int idx = -1;
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].id == id) { idx = i; break; }
    }
    if (idx < 0) {
        printf("\n Error: Robot with ID %d not found!\n", id);
        return;
    }
    for (int i = idx; i < robotCount-1; i++) robots[i] = robots[i+1];
    robotCount--;
    printf("Robot ID %d deleted.\n", id);
}

void printRobotDetails(const Robot *robot) {
    if (!robot) return;
    printf("\n=== Robot Details ===\n");
    printf("ID: %d\nName: %s\n", robot->id, robot->name);

const char *statusStr;
    if (robot->status == IDLE) {
        statusStr = "IDLE";
    }
    else if (robot->status == WORKING) {
      statusStr = "WORKING";
    }
    else {
    statusStr = "ERROR";
    }
    printf("Status: %s\nTasks Completed: %d\n", statusStr, robot->tasksCompleted);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&robot->lastMaintenance));
    printf("Last Maintenance: %s\nTools: %s\n", timeStr, robot->tools);
    printf("======================\n");
}

Robot* viewRobotById(int id) {
    for (int i = 0; i < robotCount; i++)
        if (robots[i].id == id) return &robots[i];
    return NULL;
}

void listAllRobots(void) {
    if (robotCount == 0) {
        printf("\nNo robots in the system!\n");
        return;
    }
    printf("\n=== All Robots (%d) ===\n", robotCount);
    for (int i = 0; i < robotCount; i++) printRobotDetails(&robots[i]);
}

void searchRobotsByStatus(RobotStatus status) {
    if (status < IDLE || status > ERROR) {
        printf("\nInvalid status code!\n");
        return;
    }
    printf("\n=== Robots in ");
    if (status == IDLE) {
        printf("IDLE");
    } else if (status == WORKING) {
        printf("WORKING");
    } else {
        printf("ERROR");
    }
    printf(" Status ===\n");

    int found = 0;
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].status == status) {
            printRobotDetails(&robots[i]);
            found++;
        }
    }
    if (!found) printf("No robots found in that status!\n");
}

void resetRobotStatus(int id) {
    Robot *r = viewRobotById(id);
    if (!r) {
        printf("\n Error: Robot %d not found!\n", id);
        return;
    }
    r->status = IDLE;
    r->lastMaintenance = time(NULL);
    printf("\n Robot %d reset to IDLE\n", id);
}

void showWorkHistory(const Robot *robot) {
    if (!robot) return;
    printf("\nWork history for Robot ID %d:\n", robot->id);
    printf("we dont know what to do in this function :c\n");
}
