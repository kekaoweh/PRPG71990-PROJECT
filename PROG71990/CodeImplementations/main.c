#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "taskmanager.h"

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf("\n==== Task Manager ====\n");
        printf("1. Add Task\n2. Delete Task\n3. Update Task\n4. Display Task\n5. Display All\n");
        printf("6. Search Task\n7. Display Range\n8. Save and Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            flushInput();
            continue;
        }
        flushInput();

        switch (choice) {
        case 1: addTask(); break;
        case 2: deleteTask(); break;
        case 3: updateTask(); break;
        case 4: displayTask(); break;
        case 5: displayAll(); break;
        case 6: searchTask(); break;
        case 7: displayRange(); break;
        case 8: saveToFile(); printf("Tasks saved. Exiting...\n"); exit(0);
        default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
