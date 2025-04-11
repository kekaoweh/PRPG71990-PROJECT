#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "taskmanager.h"

// Programming principles (prog71990) group project - winter 2025
// Kekachukwu Oweh, Heba Tufail, Leslie Lontsi

int main() {

    int choice;
    loadFromFile();

    do {
        // display the menu for the user
        printf("\n=== Task Manager ===\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Update Task\n");
        printf("4. Display Task\n");
        printf("5. Display All Tasks\n");
        printf("6. Display Task Range\n");
        printf("7. Search Task\n");
        printf("8. Save Tasks\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please try again.\n");
            flushInput();
            continue;
        }
        flushInput();

        // handle menu option choices
        switch (choice) {
        case 1: addTask();
            break;
        case 2: deleteTask();
            break;
        case 3: updateTask(); 
            break;
        case 4: displayTask();
            break;
        case 5: displayAll(); 
            break;
        case 6: displayRange(); 
            break;
        case 7: searchTask();
            break;
        case 8: saveToFile();
            break;
        case 9: printf("Exiting...\n");
            break;
        default: printf("Invalid option, try again.\n");
        }
    } while (choice != 9); 

    return 0;
}
