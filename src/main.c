#include <headers.h>

int main (int argc, char **argv){

    if(argc < 2){
        printf("Not enought arguments. Use: \"todo help\".\n");
        return 1;
    }

    char* command = argv[1];
    if(strcmp(command, "help") == 0){
        help_menu();
    }else if(strcmp(command, "list") == 0){
        return list_task(argc, argv);
    }else if(strcmp(command, "add") == 0){
        return add_task(argc, argv);
    }else if(strcmp(command, "delete") == 0){
        return delete_task(argc, argv);
    }else if(strcmp(command, "done") == 0){
        return mark_as_done(argc, argv);
    }else if(strcmp(command, "clear") == 0){
        return clear_done();
    }else if(strcmp(command, "reset") == 0){
        return delete_file_content();
    }else{
        argument_error(command);
        return 1;
    }

    return 0;
}
