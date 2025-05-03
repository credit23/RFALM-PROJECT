#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//-------ENUMS & STRUCTS


typedef enum { IDLE, WORKING, ERROR } RobotStatus;

typedef struct {
    int id;
    char name[50];
    RobotStatus status;
    int tasksCompleted;
    time_t lastMaintenance;
    
} Robot;

typedef struct {
    int taskId;
    char description[100];
    int componentIds[10]; 
    int duration; 
    int assignedRobotId;
} Task;

typedef struct QueueNode {
    Task task;
    struct QueueNode* next;
} QueueNode; 

typedef struct StackNode {
    Task task;
    struct StackNode* next;
} StackNode; 

// N-ary tree for factory zones
typedef struct TreeNode {
    char zoneName[50];
    struct TreeNode** children;
    int childCount;
} TreeNode;


//-----FUNCTIONS
void manageRobotsSubmenu();
void addRobot() { printf("Adding robot...\n"); }
void editRobot() { printf("Editing robot...\n"); }
void deleteRobot() { printf("Deleting robot...\n"); }


int main(){
    int choice;
    do{
        printf("\033[36m\n===============\033[33m RFALM Menu\033[36m ===============\n");
        printf("\033[36m1.\033[97m 🤖  Manage Robots \n");
        printf("\033[36m2.\033[97m 📋  Manage Tasks \n");
        printf("\033[36m3.\033[97m 🚦  View & Control Task Queue \n");
        printf("\033[36m4.\033[97m ➡️   Assign Task to Robot \n");
        printf("\033[36m5.\033[97m ↩️   Undo Last Task (Stack) \n");
        printf("\033[36m6.\033[97m 🌳  Display Factory Structure Tree \n");
        printf("\033[36m7.\033[97m 📊  View Production Summary \n");
        printf("\033[36m8.\033[97m 💾  Save Session to File \n");
        printf("\033[36m9.\033[97m 📂  Load Session from File \n");
        printf("\033[36m10.\033[97m🚪  Exit \n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: manageRobotsSubmenu();break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    while(choice!=10);

    return 0;
            
}


void manageRobotsSubmenu() {
    int choice;
    do {
        // Display submenu
        printf("\n\033[36m===\033[33m 🤖 Manage Robots\033[36m ===\n");
        printf("\033[36m1.\033[97m ➕  Add New Robot\n");
        printf("\033[36m2.\033[97m ✏️   Edit Robot Information\n");
        printf("\033[36m3.\033[97m 🗑️   Delete Robot\n");
        printf("\033[36m4.\033[97m 🔍  View Robot by ID\n");
        printf("\033[36m5.\033[97m 📜  List All Robots\n");
        printf("\033[36m6.\033[97m 🚦  Search by Status (Idle/Working/Error)\n");
        printf("\033[36m7.\033[97m 📅  Show Work History\n");
        printf("\033[36m8.\033[97m 🔄  Reset Robot Status\n");
        printf("\033[36m9.\033[97m ↩️   Return to Main Menu\n");
        printf("Choose an option: ");
        
        scanf("%d", &choice);

        // Handle user choice
        switch(choice) {
            case 1:
                addRobot();
                break;
            case 2:
                editRobot();
                break;
            case 3:
                deleteRobot();
                break;
            case 4:
                printf("Viewing robot by ID...\n");
                break;
            case 5:
                printf("Listing all robots...\n");
                break;
            case 6:
                printf("Searching robots by status...\n");
                break;
            case 7:
                printf("Showing work history...\n");
                break;
            case 8:
                printf("Resetting robot status...\n");
                break;
            case 9:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Try 1-9.\n");
                break;
        }
    } while(choice != 9);
}

void addrobot(){
    
}