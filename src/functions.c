#include <headers.h>

void argument_error(char* arg){
    printf("Unknown command \"%s\". Use: \"todo help\".\n", arg);
}

void help_menu(){
    printf("todo commands:\n");
    printf("    todo list                   list all task\n");
    printf("    todo add <description>      add a new task\n");
    printf("    todo delete <index>         delete task with index\n");
    printf("    todo done <index>           mark task with index as done\n");
    printf("    todo clear                  delete all done task\n");
    printf("    todo reset                  delete all task\n");
}

int list_task(int argc, char** argv){
    TASK task;
    FILE* file = open_file(FILE_NAME, 'r');
    if(file == NULL){
        return 1;
    }
    bool list_date = false;
    if(argc == 3 && strcmp(argv[2], "date") == 0){
        list_date = true;
    }
    int index = 0;
    while(fread(&task, sizeof(TASK), 1, file) == 1){
        printf("%2d. ", ++index);
        print_task(task, list_date);
    }
    if(index == 0){
        printf("You do not have any task yet.\n");
        return 1;
    }
    fclose(file);
    return 0;
}

void print_task(TASK task, bool list_date){
    if(list_date){
        print_date(task.date);
        printf(": ");
    }
    if(task.status == DONE){
        printf("\033[9m%s\033[0m\n", task.description);
    }else{
        printf("%s\n", task.description);
    }
}


int add_task(int argc, char** argv){
    if(argc < 3){
        printf("Use: todo add \"task description.\"\n");
        return 1;
    }
    int i = 2;
    while(i < argc){
        char* description = argv[i];
        if(strlen(description) > DES_LEN){
            printf("Description is too long.\n");
            return 1;
        }
        TASK task = new_task(description);
        if(add_task_to_file(task)){
            printf("Task \"%s\" was added succesfully.\n", description);
        }else{
            printf("Could not add \"%s\" task.", description);
            return 1;
        }
        i++;
    }
    return 0;
}

TASK new_task(char* description){
    TASK task;
    task.date = get_date();
    strncpy(task.description, description, DES_LEN);
    task.status = PENDING;
    return task;
}

int delete_task(int argc, char** argv){
    if(argc < 3){
        printf("Use: todo delete \"task index.\"\n");
        return 1;
    }
    int i = 2;
    while(i < argc){
        if(!is_valid_num(argv[i])){
            printf("Invalid index \"%s\".\n", argv[i]);
            return 1;
        }else{
            int index = atoi(argv[i]);
            if(delete_task_from_file(index)){
                printf("Task %d was deleted succesfully.\n", index);
            }else{
                printf("Task %d could not be deleted.\n", index);
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int mark_as_done(int argc, char** argv){
    if(argc < 3){
        printf("Use: todo delete \"task index.\"\n");
        return 1;
    }
    int i = 2;
    while(i < argc){
        if(!is_valid_num(argv[i])){
            printf("Invalid index \"%s\".\n", argv[i]);
            return 1;
        }else{
            int index = atoi(argv[i]);
            if(done_task_from_file(index)){
                printf("Task %d was marked as done succesfully.\n", index);
            }else{
                printf("Task %d could not be marked as done.\n", index);
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int clear_done(){
    int cleared = clear_done_from_file();
    if(cleared){
        printf("Cleared %d task.\n", cleared);
        return 0;
    }else{
        printf("Could not clear any task.\n");
        return 1;
    }
}

bool is_valid_num(char* arg){
    for(int i = 0; arg[i] != '\0'; i++){
        if(!isdigit(arg[i])){
            return false;
        }
    }
    return true;
}

DATE get_date(){
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    DATE out;
    out.day = date.tm_mday;
    out.month = date.tm_mon + 1;
    out.year = date.tm_year + 1900;
    return out;
}

void print_date(DATE date){
    printf("%d-%d-%d", date.day, date.month, date.year % 100);
}
