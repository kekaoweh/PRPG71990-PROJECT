#pragma once

#define MAX_TASKS 100
#define MAX_DESC 500
#define FILENAME "tasks.dat"

typedef struct {
    int id;
    char description[MAX_DESC];
} Task;

extern Task tasks[MAX_TASKS];
extern int task_count;

// Function prototypes
void addTask();
void deleteTask();
void updateTask();
void displayTask();
void displayRange();
void displayAll();
void searchTask();
void saveToFile();
void loadFromFile();
void flushInput();
