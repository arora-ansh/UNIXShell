/*
UNIX SHELL
Name : Ansh Arora
Roll No. : 2019022
Branch : CSE
Section : B

LINUX SHELL CODED IN C
Commands to handle-
 1) Internal -
        cd - Change Directory
        echo - Prints out what's written (-n flag)
        history - Shows last 500 executed commands
        pwd - Shows current working folder
        exit - Exits the program

 2) External -
        ls - Shows all the files present in current folder
        cat - Prints out the selected file in given format (-n and -b flags)
        date - Prints out current date and time in Sat Sep 26 04:42:48 IST 2020 format.  (-u and -r seconds flags)
        rm - Removes selected file from current folder (-v prints name of deleted file and -r flags)
        mkdir - Makes a directory in given folder with specified name (-v (mkdir: created directory 'hi') and -p creates
        the whole path of directories given)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main() {
    int historySize = 0;
    char historyArray[100][500];
    char rootLocation[200];
    getcwd(rootLocation,sizeof(rootLocation));
    char presentLocationPrint[200];
    while(1){
        getcwd(presentLocationPrint,sizeof(presentLocationPrint));
        printf("Shell-Simulator: %s$ ",presentLocationPrint);
        char command[100];
        //scanf("%[^\n]%*c", command);
        fgets(command,100,stdin);
        if(command[0]=='\0'|| command[0]=='\n'){
            continue;
        }
        //printf("%s\n",command);
        char* command2 = strtok(command,"\n");
        char curPosition[200];
        getcwd(curPosition,sizeof(curPosition));
        chdir("/");
        chdir(rootLocation);
        FILE *fptr;
        fptr = fopen("history.txt","a");
        fprintf(fptr,"%s\n",command);
        fclose(fptr);
        chdir("/");
        chdir(curPosition);

        //History Array built for history command
        //historyArray[historySize] = command;

        //strcpy(historyArray[historySize],command);
        //++historySize;

        //printf("%s",command);
        //Function to split command string and store it into array elements
        char *commandArr[100];//Stores the divided strings of entered command
        int commandN = 0;//Stores the number of strings in command arr
        char *tokenCommand = strtok(command2," ");
        while(tokenCommand!=NULL){
            commandArr[commandN] = tokenCommand;
            tokenCommand = strtok(NULL," ");
            ++commandN;
        }
        /*for(int i=0;i<commandN;i++){
            printf("%d %s\n",i+1,commandArr[i]);
        }
        */
        //-----------------------------------------

        //echo command with -n flag
        //Handles multiple words case 
        if(strcmp(commandArr[0], "echo") == 0){
            if(commandN==2) {
                printf("%s\n", commandArr[1]);
            }
            else if(commandN>2){
                if(strcmp(commandArr[1],"-n")==0){
                    for(int i=2;i<commandN;i++){
                        printf("%s ",commandArr[i]);
                    }
                }
                else if(strcmp(commandArr[1],"--help")==0){
                    char curPosition[200];
                    getcwd(curPosition,sizeof(curPosition));
                    chdir("/");
                    chdir(rootLocation);
                    chdir("docs");
                    char *line = NULL;
                    FILE *fptr;
                    size_t len = 0;
                    fptr = fopen("echo.txt","r");
                    while (getline(&line, &len, fptr) != -1) {
                        printf("%s", line);
                    }
                    printf("\n");
                    fclose(fptr);
                    chdir("/");
                    chdir(curPosition);
                }
                else{
                    for(int i=1;i<commandN;i++){
                        printf("%s ",commandArr[i]);
                    }
                    printf("\n");
                }
            }
        }
        //-----------------------------------------

        //history command - flags -c (clears history list) (CHANGE THIS TO PERMANENT)

        else if(strcmp(commandArr[0],"history")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==1) {
                /*
                for (int i = 0; i < historySize; i++) {
                    printf("%d %s\n", i + 1, historyArray[i]);
                }
                */
                char *fileLine = NULL;
                size_t lineLen = 0;
                fptr = fopen("history.txt","r");
                int i = 1;
                while(getline(&fileLine,&lineLen,fptr)!=-1){
                    printf("%d %s",i,fileLine);
                    i++;
                }
                fclose(fptr);
            }
            //-c and -d flag functionality
            else {
                if (strcmp(commandArr[1], "-c") == 0) {
                    //historySize = 0;
                    fptr = fopen("history.txt","w");
                    fprintf(fptr,"%s\n",command);
                    fclose(fptr);
                    char *fileLine = NULL;
                    size_t lineLen = 0;
                    fptr = fopen("history.txt","r");
                    int i = 1;
                    while(getline(&fileLine,&lineLen,fptr)!=-1){
                        printf("%d %s",i,fileLine);
                        i++;
                    }
                    fclose(fptr);
                }
                else if (strcmp(commandArr[1],"-d")==0) {
                    int x = atoi(commandArr[2]);//Line number to be deleted
                    int i = 1;
                    /*
                    for(int i=x;i<historySize;i++){
                        strcpy(historyArray[i-1],historyArray[i]);
                    }
                    historySize = historySize-1;
                    */
                    FILE *fptr2;
                    fptr = fopen("history.txt","r");
                    fptr2 = fopen("temp.txt","w");
                    char *lines = NULL;
                    size_t lenLine= 0;
                    while(getline(&lines, &lenLine, fptr) != -1){
                        if(i==x){
                            i++;
                            continue;
                        }
                        else{
                            fprintf(fptr2,"%s",lines);
                        }
                        i++;
                    }
                    fclose(fptr);
                    fclose(fptr2);
                    remove("history.txt");
                    rename("temp.txt","history.txt");
                    fptr = fopen("history.txt","a");
                    fprintf(fptr,"%s\n",command);
                    fclose(fptr);
                    char *fileLine = NULL;
                    size_t lineLen = 0;
                    fptr = fopen("history.txt","r");
                    i = 1;
                    while(getline(&fileLine,&lineLen,fptr)!=-1){
                        printf("%d %s",i,fileLine);
                        i++;
                    }
                    fclose(fptr);
                }
                else{
                    printf("Invalid Command, argument required\n");
                }
            }
            chdir("/");
            chdir(curPosition);
        }

        //-----------------------------------------

        //pwd command
        else if(strcmp(commandArr[0], "pwd") == 0){
            if(commandN==1) {
                char currentLocation[500];
                getcwd(currentLocation, sizeof(currentLocation));
                printf("%s\n", currentLocation);
            }
            else{
                if(strcmp(commandArr[1], "-L")==0){
                    printf("%s\n", getenv("PWD"));
                }
                else if(strcmp(commandArr[1], "-P")==0){ 
                    char currentLocation[200];
                    getcwd(currentLocation, sizeof(currentLocation));
                    printf("%s\n", currentLocation);
                }
                else if(strcmp(commandArr[1],"--help")==0){
                    char curPosition[200];
                    getcwd(curPosition,sizeof(curPosition));
                    chdir("/");
                    chdir(rootLocation);
                    chdir("docs");
                    char *line = NULL;
                    FILE *fptr;
                    size_t len = 0;
                    fptr = fopen("pwd.txt","r");
                    while (getline(&line, &len, fptr) != -1) {
                        printf("%s", line);
                    }
                    printf("\n");
                    fclose(fptr);
                    chdir("/");
                    chdir(curPosition);
                }
                else{
                    printf("Invalid Command, argument required\n");
                }
            }
        }

        //-----------------------------------------

        //cd command & arguments / , ~ and .. & options -P and --help

        else if(strcmp(commandArr[0], "cd") == 0){
            if(commandN==2 && (strcmp(commandArr[1],"..")!=0 || strcmp(commandArr[1],"/")!=0 || strcmp(commandArr[1],"-P")!=0 || strcmp(commandArr[1],"~")!=0 || strcmp(commandArr[1],"--help")!=0)){
                char currentLocation[200];
                getcwd(currentLocation, sizeof(currentLocation));
                strcat(currentLocation,"/");
                strcat(currentLocation,commandArr[1]);
                int result = chdir(currentLocation);
                if(result!=0 && strcmp(commandArr[1],"~")!=0){
                    printf("No such directory found\n");
                }
                if(strcmp(commandArr[1],"~")==0){
                    chdir(getenv("HOME"));
                }
            }
            else if(commandN==2 && strcmp(commandArr[1],"..")==0){
                printf("HERE WE ARE\n");
                char currentLocation[200];
                getcwd(currentLocation, sizeof(currentLocation));
                char newLocation[200] = "";
                int localCount = 0;
                char *localArray[100];
                char *tokenLocal = strtok(currentLocation," ");
                while(tokenLocal!=NULL){
                    localArray[commandN] = tokenLocal;
                    tokenLocal = strtok(NULL," ");
                    ++localCount;
                }
                for(int i=0;i<localCount-1;i++){
                    strcat(newLocation,"/");
                    strcat(newLocation,localArray[i]);
                }
                chdir(newLocation);
            }
            else if(commandN==2 && strcmp(commandArr[1],"/")==0){
                chdir("/");
            }
            else if(commandN==2 && strcmp(commandArr[1],"~")==0){
                chdir(getenv("HOME"));
            }
            else if(commandN==3 && strcmp(commandArr[1],"-P")==0){
                char currentLocation[200];
                getcwd(currentLocation, sizeof(currentLocation));
                strcat(currentLocation,"/");
                strcat(currentLocation,commandArr[2]);
                int result = chdir(currentLocation);
                if(result!=0){
                    printf("No such directory found\n");
                }
            }
            else if(commandN==2 && strcmp(commandArr[1],"--help")==0){
                char curPosition[200];
                getcwd(curPosition,sizeof(curPosition));
                chdir("/");
                chdir(rootLocation);
                chdir("docs");
                char *line = NULL;
                FILE *fptr;
                size_t len = 0;
                fptr = fopen("cd.txt","r");
                while (getline(&line, &len, fptr) != -1) {
                    printf("%s", line);                    
                }
                printf("\n");
                fclose(fptr);
                chdir("/");
                chdir(curPosition);
            }
            else{
                printf("Invalid Command, argument required\n");
            }

        }
        //-----------------------------------------

        //NOTE IN EXTERNAL COMMANDS PASS THE CURRENT LOCATION of shell
        // For this we can store the current location as x, then change our current location to / and from there go to the starting
        // of the path(where commands are held). Now, in execvp pass the new stored location. The external command will change
        // directory to /, and then to the passed location, where it will perform its operation. After that, it will exit back to
        // main, where we will chane the path from the main folder to wherever we were (x).
        // Need to do the double change of path for ls, cat, rm and mkdir. For date can simply go the folder where files are kept
        // and run the date file and then come back to folder we were on.

        //ls command call -A flag, -m flag

        else if(strcmp(commandArr[0],"ls")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==1){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./ls",curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            else if(commandN==2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./ls",commandArr[1],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            chdir("/");
            chdir(curPosition);
            /*LOCALE TEST
            char x[100];
            getcwd(x,sizeof(x));
            printf("%s\n",x);
            */
        }

        //-----------------------------------------

        //date command call with -u flag for UTC timings
        else if(strcmp(commandArr[0],"date")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==1){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./date",NULL};
                    execvp(args[0],args);
                }
            }
            else if(commandN==2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./date",commandArr[1],NULL};
                    execvp(args[0],args);
                }
            }
            wait(NULL);
            chdir("/");
            chdir(curPosition);
        }

        //-----------------------------------------

        //cat command call with flags -n (for numbering) and -e (for $sign at end of line)
        else if(strcmp(commandArr[0],"cat")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./cat",commandArr[1],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            else if(commandN>2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./cat",commandArr[1],commandArr[2],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            chdir("/");
            chdir(curPosition);
        }

        //-----------------------------------------

        //rm command call
        else if(strcmp(commandArr[0],"rm")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./rm",commandArr[1],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            else if(commandN>2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./rm",commandArr[1],commandArr[2],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            chdir("/");
            chdir(curPosition);
        }

        //-----------------------------------------

        //mkdir command call with -v and -p flags
        else if(strcmp(commandArr[0],"mkdir")==0){
            char curPosition[200];
            getcwd(curPosition,sizeof(curPosition));
            chdir("/");
            chdir(rootLocation);
            if(commandN==2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./mkdir",commandArr[1],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            else if(commandN>2){
                int pid_id = fork();
                if(pid_id==0){
                    char *args[] = {"./mkdir",commandArr[1],commandArr[2],curPosition,NULL};
                    execvp(args[0],args);
                }
                wait(NULL);
            }
            chdir("/");
            chdir(curPosition);

        }

        //-----------------------------------------
        
        // help command to show docs of specific commands
        if(strcmp(command,"help")==0){
            if(commandN==2){
                char curPosition[200];
                getcwd(curPosition,sizeof(curPosition));
                chdir("/");
                chdir(rootLocation);
                chdir("docs");
                char fileName[200];
                strcpy(fileName,commandArr[1]);
                strcat(fileName,".txt");
                if(strcmp(fileName,"history.txt")!=0){
                    char *line = NULL;
                    FILE *fptr;
                    size_t len = 0;
                    fptr = fopen(fileName,"r");
                    while (getline(&line, &len, fptr) != -1) {
                        printf("%s", line);
                    }
                    printf("\n");
                    fclose(fptr);
                }
                else{
                    char *line = NULL;
                    FILE *fptr;
                    size_t len = 0;
                    fptr = fopen("historyhelp.txt","r");
                    while (getline(&line, &len, fptr) != -1) {
                        printf("%s", line);
                    }
                    printf("\n");
                    fclose(fptr);
                }
                chdir("/");
                chdir(curPosition);
            }
            else{
                printf("Enter a valid command for help\n");
            }
        }

        //-----------------------------------------

        //exit command

        if(strcmp(command2,"exit")==0){
            //break;
            exit(0);
        }
        //-----------------------------------------
    }
    return 0;
}
