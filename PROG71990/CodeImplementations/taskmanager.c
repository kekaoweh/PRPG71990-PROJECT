#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskmanager.h"

// Programming principles (prog71990) group project - winter 2025
// Kekachukwu Oweh, Heba Tufail, Leslie Lontsi

Task tasks[MAX_TASKS];
int task_count = 0;

// function to flush input buffer 
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// function to validate date format YYYY-MM-DD
int validateDate(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-') {
            return 0;
        }
        if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9')) {
            return 0;
        }
    }

    return 1;  // Valid date format
}

// function to add a new task to the task list
void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    // get task description
    printf("Enter task description: ");
    if (!fgets(tasks[task_count].description, MAX_DESC, stdin)) {
        printf("Error reading input.\n");
        return;
    }
    tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0; // remove newline character

    tasks[task_count].id = task_count + 1; // assign task ID based on the current task count

    // Get task date and validate format
    char date_input[MAX_DATE];
    printf("Enter task date (YYYY-MM-DD): ");
    if (!fgets(date_input, MAX_DATE, stdin)) {
        printf("Error reading input.\n");
        return;
    }
    date_input[strcspn(date_input, "\n")] = 0; // Remove newline

    // Validate date format
    if (!validateDate(date_input)) {
        printf("Invalid date format! Task date set to default (2025-01-01).\n");
        strcpy(tasks[task_count].date, "2025-01-01");
    }
    else {
        strcpy(tasks[task_count].date, date_input);
    }

    // set task priority
    printf("Enter task priority (L: Low, M: Medium, H: High): ");
    char priority_input;
    if (scanf(" %c", &priority_input) != 1 || (priority_input != 'L' && priority_input != 'M' && priority_input != 'H')) {
        printf("Invalid priority input! Setting default priority to Low.\n");
        tasks[task_count].p = L; // default to Low priority
    }
    else {
        // assign priority based on user input
        switch (priority_input) {
        case 'L': tasks[task_count].p = L; break;
        case 'M': tasks[task_count].p = M; break;
        case 'H': tasks[task_count].p = H; break;
        }
    }

    // set task status
    printf("Enter task status (N: Not Started, I: In Progress, C: Completed): ");
    char status_input;
    if (scanf(" %c", &status_input) != 1 || (status_input != 'N' && status_input != 'I' && status_input != 'C')) {
        printf("Invalid status input! Setting default status to Not Started.\n");
        tasks[task_count].s = N; // default to Not Started status
    }
    else {
        // assign status based on user input
        switch (status_input) {
        case 'N': tasks[task_count].s = N; break;
        case 'I': tasks[task_count].s = I; break;
        case 'C': tasks[task_count].s = C; break;
        }
    }

    task_count++;
    printf("Task added successfully!\n");
}

// function to delete a task by its ID
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

            // show task details before confirmation, including date
            printf("Task ID: %d | Description: %s | Priority: %c | Status: %c | Date: %s\n",
                tasks[i].id, tasks[i].description,
                (tasks[i].p == L ? 'L' : (tasks[i].p == M ? 'M' : 'H')),
                (tasks[i].s == N ? 'N' : (tasks[i].s == I ? 'I' : 'C')),
                tasks[i].date);

            // ask for confirmation
            char confirm;
            printf("Are you sure you want to delete this task? (y/n): ");
            if (scanf(" %c", &confirm) != 1 || (confirm != 'y' && confirm != 'Y')) {
                printf("Deletion cancelled.\n");
                flushInput();
                return;
            }
            flushInput();

            // perform deletion
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1]; // move next task to current position
                tasks[j].id = j + 1;
            }
            task_count--;
            printf("Task deleted successfully!\n");
            return;
        }
    }
    if (!found) {
        printf("Task not found!\n");
    }
}

// function to update task details
void updateTask() {
    int id;
    printf("Enter task ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    // search for the task to update
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            // update task description
            printf("Enter new task description: ");
            if (!fgets(tasks[i].description, MAX_DESC, stdin)) {
                printf("Error reading input.\n");
                return;
            }
            tasks[i].description[strcspn(tasks[i].description, "\n")] = 0; // remove newline character

            // update task priority
            printf("Enter new task priority (L: Low, M: Medium, H: High): ");
            char priority_input;
            if (scanf(" %c", &priority_input) != 1 || (priority_input != 'L' && priority_input != 'M' && priority_input != 'H')) {
                printf("Invalid priority input! Keeping previous priority.\n");
            }
            else {
                // update priority based on user input
                switch (priority_input) {
                case 'L': tasks[i].p = L; break;
                case 'M': tasks[i].p = M; break;
                case 'H': tasks[i].p = H; break;
                }
            }

            // update task status
            printf("Enter new task status (N: Not Started, I: In Progress, C: Completed): ");
            char status_input;
            if (scanf(" %c", &status_input) != 1 || (status_input != 'N' && status_input != 'I' && status_input != 'C')) {
                printf("Invalid status input! Keeping previous status.\n");
            }
            else {
                // update status based on user input
                switch (status_input) {
                case 'N': tasks[i].s = N; break;
                case 'I': tasks[i].s = I; break;
                case 'C': tasks[i].s = C; break;
                }
            }

            printf("Task updated successfully!\n");
            return;
        }
    }
    printf("Task not found!\n");
}

// function to display a specific task by ID
void displayTask() {
    int id;
    printf("Enter task ID to display: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    flushInput();

    // search for and display task details by ID
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Task ID: %d | Description: %s | Priority: %c | Status: %c | Date: %s\n",
                tasks[i].id, tasks[i].description,
                (tasks[i].p == L ? 'L' : (tasks[i].p == M ? 'M' : 'H')),
                (tasks[i].s == N ? 'N' : (tasks[i].s == I ? 'I' : 'C')),
                tasks[i].date);
            return;
        }
    }
    printf("Task not found!\n");
}

// function to display a range of tasks based on ID
void displayRange() {
    int start, end;
    printf("Enter start ID: ");
    if (scanf("%d", &start) != 1) {
        printf("Invalid input!\n");
        flushInput();
        return;
    }
    printf("Enter end ID: ");
    if (scanf("%d", &end) != 1 || end < start) {
        printf("Invalid range!\n");
        flushInput();
        return;
    }

    // loop through and display tasks within the given range
    printf("Displaying tasks in range %d to %d:\n", start, end);
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id >= start && tasks[i].id <= end) {
            printf("Task ID: %d | Description: %s | Priority: %c | Status: %c | Date: %s\n",
                tasks[i].id, tasks[i].description,
                (tasks[i].p == L ? 'L' : (tasks[i].p == M ? 'M' : 'H')),
                (tasks[i].s == N ? 'N' : (tasks[i].s == I ? 'I' : 'C')),
                tasks[i].date);
        }
    }
}


// function to display all tasks
void displayAll() {
    if (task_count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n=== Task List ===\n");
    for (int i = 0; i < task_count; i++) {
        printf("Task ID: %d | Description: %s | Priority: %c | Status: %c\n",
            tasks[i].id, tasks[i].description,
            (tasks[i].p == L ? 'L' : (tasks[i].p == M ? 'M' : 'H')),
            (tasks[i].s == N ? 'N' : (tasks[i].s == I ? 'I' : 'C')));
    }
}

// function to search for tasks by keyword in the description
void searchTask() {
    char keyword[MAX_DESC];
    int found = 0;

    printf("Enter keyword to search: ");
    if (!fgets(keyword, MAX_DESC, stdin)) {
        printf("Error reading input.\n");
        return;
    }
    keyword[strcspn(keyword, "\n")] = 0;

    // search tasks by description for the given keyword
    for (int i = 0; i < task_count; i++) {
        if (strstr(tasks[i].description, keyword)) {
            printf("Task ID: %d | Description: %s | Priority: %c | Status: %c\n",
                tasks[i].id, tasks[i].description,
                (tasks[i].p == L ? 'L' : (tasks[i].p == M ? 'M' : 'H')),
                (tasks[i].s == N ? 'N' : (tasks[i].s == I ? 'I' : 'C')));
            found = 1;
        }
    }
    if (!found) printf("No matching tasks found!\n");
}

// function to save tasks to a file
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
    else {
        printf("%d tasks saved successfully.\n", task_count);
    }

    fclose(file);
}

// function to load tasks from a file
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
        printf("Error reading data from file!\n");
    }

    task_count = temp_count; 
    fclose(file);
}
