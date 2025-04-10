#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include “taskmanager.h”

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf(“\n==== To - Do List Manager ====\n”);
        printf(“1.Add Task\n2.Delete Task\n3.Update Task\n”);
        printf(“4.Display a Single Task\n5.Display a Range of Tasks\n”);
        printf(“6.Display All Tasks\n7.Search for a Task\n”);
        printf(“8.Save & Exit\n”);
        printf(“Enter choice : “);
        scanf(“ % d”, &choice);
        getchar();  // Clear input buffer

        switch (choice) {
        case 1: addTask(); break;
        case 2: deleteTask(); break;
        case 3: updateTask(); break;
        case 4: displayTask(); break;
        case 5: displayRange(); break;
        case 6: displayAll(); break;
        case 7: searchTask(); break;
        case 8: saveToFile(); printf(“Tasks saved.Exiting...\n”); return 0;
        default: printf(“Invalid choice!Try again.\n”);
        }
    }
}