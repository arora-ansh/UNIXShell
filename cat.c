//cat command
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <zconf.h>

int main(int argc, char **args){
    if(argc==3) {
        chdir("/");
        chdir(*(args+2));
        char *line = NULL;
        FILE *fptr;
        size_t len = 0;
        if ((fptr = fopen(*(args + 1), "r")) == NULL) {
            printf("No such file or directory\n");
            // Program exits if file pointer returns NULL.
            exit(1);
        }

        // reads text until newline is encountered
        while (getline(&line, &len, fptr) != -1) {
            printf("%s", line);
        }
        fclose(fptr);
    }
    else if(argc==4){
        if(strcmp(*(args+1),"-n")==0){
            chdir("/");
            chdir(*(args+3));
            char *line = NULL;
            FILE *fptr;
            size_t len = 0;
            if ((fptr = fopen(*(args + 2), "r")) == NULL) {
                printf("No such file or directory\n");
                // Program exits if file pointer returns NULL.
                exit(1);
            }

            // reads text until newline is encountered
            int i = 1;
            while (getline(&line, &len, fptr) != -1) {
                printf("%d %s", i, line);
                i++;
            }
            fclose(fptr);
        }
        else if(strcmp(*(args+1),"-e")==0){
            chdir("/");
            chdir(*(args+3));
            char *line = NULL;
            FILE *fptr;
            size_t len = 0;
            if ((fptr = fopen(*(args + 2), "r")) == NULL) {
                printf("No such file or directory\n");
                // Program exits if file pointer returns NULL.
                exit(1);
            }

            // reads text until newline is encountered
            while (getline(&line, &len, fptr) != -1) {
                printf("%s$", line);
            }
            fclose(fptr);

        }
        else{
            printf("Invalid Command, argument required\n");
        }
    }
    exit(0);
}

