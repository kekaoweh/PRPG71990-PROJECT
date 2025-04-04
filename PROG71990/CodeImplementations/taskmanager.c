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
// Function to display a range of tasks
void displayRange() {
    int start, end, i;
    printf("Enter start ID: ");
    scanf("%d", &start);
    printf("Enter end ID: ");
    scanf("%d", &end);

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id >= start && tasks[i].id <= end) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
        }
    }
}

// Function to display all tasks
void displayAll() {
    if (task_count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n=== Task List ===\n");
    for (int i = 0; i < task_count; i++) {
        printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
    }
}

// Function to search for a task by description
void searchTask() {
    char keyword[MAX_DESC];
    int found = 0;
    printf("Enter keyword to search: ");
    getchar();
    fgets(keyword, MAX_DESC, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for (int i = 0; i < task_count; i++) {
        if (strstr(tasks[i].description, keyword)) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
            found = 1;
        }
    }
    if (!found) printf("No matching tasks found!\n");
}

// Function to save tasks to a file
void saveToFile() {
    FILE* file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Error saving tasks!\n");
        return;
    }
    fwrite(&task_count, sizeof(int), 1, file);
    fwrite(tasks, sizeof(Task), task_count, file);
    fclose(file);
}

// Function to load tasks from a file
void loadFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) return;
    fread(&task_count, sizeof(int), 1, file);
    fread(tasks, sizeof(Task), task_count, file);
    fclose(file);
}



