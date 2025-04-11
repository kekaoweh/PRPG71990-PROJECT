#pragma once

#define MAX_TASKS 100           
#define MAX_DESC 500   
#define MAX_DATE 12
#define FILENAME "tasks.dat"    

// Programming principles (prog71990) group project - winter 2025
// Kekachukwu Oweh, Heba Tufail, Leslie Lontsi

// enum for task priority
typedef enum {
    L = 1,  
    M,      
    H       
} Priority;

// enum for task status
typedef enum {
    N = 1, 
    I,      
    C       
} Status;

// task struct
typedef struct {
    int id;                   
    char description[MAX_DESC]; 
    char date[MAX_DATE];
    Priority p;              //(Low/Medium/High)
    Status s;                //(Not Started/In Progress/Completed)
} Task;


extern Task tasks[MAX_TASKS];
extern int task_count;

// functions
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
