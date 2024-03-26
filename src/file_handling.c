#include <headers.h>

FILE* open_file(char* file_name, char mode){
    FILE* file;
    char* filePath = get_path(file_name);
    if(mode == 'r'){
        file = fopen(filePath, "rb");
    }else if(mode == 'a'){
        file = fopen(filePath, "ab");
    }else if(mode == 'w'){
        file = fopen(filePath, "wb");
    }else{
        fprintf(stderr, "Error: invalid argument for open_file()\n");
    }
    if(file == NULL){
        fprintf(stderr, "Error: could not open %s file.\n", file_name);
    }
    return file;
}

char* get_path(char* file_name){
    char* filePath = malloc(strlen(getenv("HOME")) + strlen("/") + strlen(FILE_NAME) + 1);
    strcpy(filePath, getenv("HOME"));
    strcat(filePath, "/");
    strcat(filePath, file_name);
    return filePath;
}

bool add_task_to_file(TASK task){
    FILE* file = open_file(FILE_NAME, 'a');
    if(file == NULL){
        return false;
    }
    if(fwrite(&task, sizeof(TASK), 1, file) != 1){
        fprintf(stderr, "Error: could not write new task.\n");
        return false;
    }
    fclose(file);
    return true;
}

bool delete_task_from_file(int index){

    FILE* file = open_file(FILE_NAME, 'r');
    FILE* temp = open_file(TEMP_NAME, 'w');

    if(file == NULL || temp == NULL){
        return false;
    }

    TASK task;
    int i = 1;
    bool deleted = false;
    while(fread(&task, sizeof(TASK), 1, file) == 1){
        if(i == index){
            deleted = true;
        }else{
            fwrite(&task, sizeof(TASK), 1, temp);
        }
        i++;
    }

    fclose(file);
    fclose(temp);

    if (rename(get_path(TEMP_NAME), get_path(FILE_NAME)) != 0) {
        fprintf(stderr, "Error: could not rename file.\n");
        return false;
    }

    return deleted;
}

bool done_task_from_file(int index){
    FILE* file = open_file(FILE_NAME, 'r');
    FILE* temp = open_file(TEMP_NAME, 'w');

    if(file == NULL || temp == NULL){
        return false;
    }

    TASK task;
    int i = 1;
    bool done = false;
    while(fread(&task, sizeof(TASK), 1, file) == 1){
        if(i == index){
            task.status = DONE;
            done = true;
        }
        fwrite(&task, sizeof(TASK), 1, temp);
        i++;
    }

    fclose(file);
    fclose(temp);

    if (rename(get_path(TEMP_NAME), get_path(FILE_NAME)) != 0) {
        fprintf(stderr, "Error: could not rename file.\n");
        return false;
    }

    return done;
}

int clear_done_from_file(){
    FILE* file = open_file(FILE_NAME, 'r');
    FILE* temp = open_file(TEMP_NAME, 'w');

    if(file == NULL || temp == NULL){
        return 0;
    }

    TASK task;
    int cleared = 0;
    while(fread(&task, sizeof(TASK), 1, file) == 1){
        if(task.status != DONE){
            fwrite(&task, sizeof(TASK), 1, temp);
        }else{
            cleared++;
        }
    }

    fclose(file);
    fclose(temp);

    if (rename(get_path(TEMP_NAME), get_path(FILE_NAME)) != 0) {
        fprintf(stderr, "Error: could not rename file.\n");
        return 0;
    }
    return cleared;
}

int delete_file_content(){
    FILE* file = open_file(FILE_NAME, 'w');
    if(file == NULL){
        return 1;
    }
    fclose(file);
    printf("All task deleted.\n");
    return 0;
}
