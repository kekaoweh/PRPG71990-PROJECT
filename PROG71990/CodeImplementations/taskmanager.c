#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskmanager.h"

Task tasks[MAX_TASKS];
int task_count = 0;

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task description: ");
    if (!fgets(tasks[task_count].description, MAX_DESC, stdin)) {
        printf("Error reading input.\n");
        return;
    }

    tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0;
    tasks[task_count].id = task_count + 1;
    task_count++;
    printf("Task added successfully!\n");
}

void deleteTask() {
    int id, found = 0;
    printf("Enter task ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
                tasks[j].id = j + 1;
            }
            task_count--;
            printf("Task deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Task not found!\n");
}

void updateTask() {
    int id;
    printf("Enter task ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Enter new task description: ");
            if (!fgets(tasks[i].description, MAX_DESC, stdin)) {
                printf("Error reading input.\n");
                return;
            }
            tasks[i].description[strcspn(tasks[i].description, "\n")] = 0;
            printf("Task updated successfully!\n");
            return;
        }
    }
    printf("Task not found!\n");
}

void displayTask() {
    int id;
    printf("Enter task ID to display: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
            return;
        }
    }
    printf("Task not found!\n");
}

void displayRange() {
    int start, end;
    printf("Enter start ID: ");
    if (scanf("%d", &start) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    printf("Enter end ID: ");
    if (scanf("%d", &end) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id >= start && tasks[i].id <= end) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
        }
    }
}

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

void searchTask() {
    char keyword[MAX_DESC];
    int found = 0;

    printf("Enter keyword to search: ");
    if (!fgets(keyword, MAX_DESC, stdin)) {
        printf("Error reading input.\n");
        return;
    }
    keyword[strcspn(keyword, "\n")] = 0;

    for (int i = 0; i < task_count; i++) {
        if (strstr(tasks[i].description, keyword)) {
            printf("Task ID: %d | Description: %s\n", tasks[i].id, tasks[i].description);
            found = 1;
        }
    }
    if (!found) printf("No matching tasks found!\n");
}

void saveToFile() {
    FILE* file = fopen(FILENAME, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }
    if (fwrite(&task_count, sizeof(int), 1, file) != 1 ||
        fwrite(tasks, sizeof(Task), task_count, file) != (size_t)task_count) {
        printf("Error writing data to file!\n");
    }
    fclose(file);
}

void loadFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) return;

    int temp_count;
    if (fread(&temp_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return;
    }

    if (temp_count < 0 || temp_count > MAX_TASKS) {
        printf("Corrupt or invalid task file.\n");
        fclose(file);
        return;
    }

    if (fread(tasks, sizeof(Task), temp_count, file) != (size_t)temp_count) {
        printf("Error reading task data.\n");
        fclose(file);
        return;
    }

    task_count = temp_count;
    fclose(file);
}
