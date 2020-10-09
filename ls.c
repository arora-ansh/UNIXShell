//ls command
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **args) {
    if(argc == 2) {
        chdir("/");
        chdir(*(args+1));
        struct dirent *entry;
        DIR *directory = opendir(".");

        if (directory == NULL) {
            printf("Directory doesn't exists\n");
        }

        entry = readdir(directory);
        while (entry != NULL) {
            printf("%s\n", entry->d_name);
            entry = readdir(directory);
        }
        closedir(directory);
    }
    else if(argc == 3){
        if(strcmp(*(args+1),"-A")==0){
            chdir("/");
            chdir(*(args+2));
            struct dirent *entry;
            DIR *directory = opendir(".");

            if (directory == NULL) {
                printf("Directory doesn't exists\n");
            }

            entry = readdir(directory);
            int i = 0;
            while (entry != NULL) {
                if(i>=2) {
                    printf("%s\n", entry->d_name);
                }
                entry = readdir(directory);
                i++;
            }
            closedir(directory);
        }
        else if(strcmp(*(args+1),"-m")==0){
            chdir("/");
            chdir(*(args+2));
            struct dirent *entry;
            DIR *directory = opendir(".");

            if (directory == NULL) {
                printf("Directory doesn't exists\n");
            }

            entry = readdir(directory);
            while (entry != NULL) {
                printf("%s, ", entry->d_name);
                entry = readdir(directory);
            }
            closedir(directory);
            printf("\n");
        }
        else{
            printf("Invalid Command, argument required\n");
        }
    }
    exit(0);
}

