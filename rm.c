//rm command
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **args){
    if(argc==3){
        chdir("/");
        chdir(*(args+2));
        int x = remove(*(args+1));
        if(x!=0){
            printf("Unable to delete\n");
        }
    }
    if(argc==4){
        if(strcmp(*(args+1),"-v")==0){
            chdir("/");
            chdir(*(args+3));
            printf("%s\n",*(args+2));
            int x = remove(*(args+2));
            if(x!=0){
                printf("Unable to delete\n");
            }
        }
        else if(strcmp(*(args+1),"-i")==0){
            chdir("/");
            chdir(*(args+3));
            printf("remove %s?",*(args+2));
            char choice;
            scanf("%c",&choice);
            if(choice=='Y'){
                int x = remove(*(args+2));
                if(x!=0){
                    printf("Unable to delete\n");
                }
            }
        }
        else{
            printf("Invalid Command, argument required\n");
        }
    }
    exit(0);
}
