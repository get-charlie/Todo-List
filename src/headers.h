#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define FILE_NAME ".todo_data.bin"
#define TEMP_NAME ".todo_temp-bin"
#define DES_LEN 120

typedef enum{
    PENDING,
    DONE
}STATUS;

typedef struct{
    unsigned day;
    unsigned month;
    unsigned year;
}DATE;

typedef struct{
    DATE date;
    char description[DES_LEN];
    STATUS status;
}TASK;

void argument_error(char* arg);
void help_menu();

FILE* open_file(char* file_name, char mode); // opens data file in a specific mode 'r' read 'a' append 'w' write
char* get_path(); // returns home path + file name


TASK new_task(char* description); // creates new task with a description an a date
int add_task(int argc, char** argv); 
bool add_task_to_file(TASK task);


int list_task(int argc, char** argv);
void print_task(TASK task, bool list_date);

int delete_task(int argc, char** argv);
bool delete_task_from_file(int index);

int mark_as_done(int argc, char** argv);
bool done_task_from_file(int index);

int clear_done();
int clear_done_from_file();

int delete_file_content();

bool is_valid_num(char* arg);

DATE get_date();
void print_date(DATE date);

#endif
