#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskmanager.h"

Task tasks[MAX_TASKS];
int task_count = 0;

// Function to add a new task
void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task description: ");
    fgets(tasks[task_count].description, MAX_DESC, stdin);
    tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0; // Remove newline
    tasks[task_count].id = task_count + 1;
    task_count++;
    printf("Task added successfully!\n");
}

// Function to delete a task
void deleteTask() {
    int id, i, found = 0;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            task_count--;
            printf("Task deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Task not found!\n");
}

// Function to update an existing task
void updateTask() {
    int id, i;
    printf("Enter task ID to update: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Enter new task description: ");
            fgets(tasks[i].description, MAX_DESC, stdin);
            tasks[i].description[strcspn(tasks[i].description, "\n")] = 0;
            printf("Task updated successfully!\n");
            return;
        }
    }
    printf("Task not found!\n");
}

// Function to display a single task
void displayTask() {
    int id, i;
    printf("Enter task ID to display: ");
    scanf("%d", &id);

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
            return;
        }
    }
    printf("Task not found!\n");
}

