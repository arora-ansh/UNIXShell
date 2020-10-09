//date command
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc,char **args)
{
    time_t t = time(NULL);
    struct tm tm;
    if(argc==1 || (strcmp(*(args+1),"-R")==0)){
        tm = *localtime(&t);
    }
    else{
        if(strcmp(*(args+1),"-u")==0){
            tm = *gmtime(&t);
        }
        else{
            printf("Invalid Command, argument required\n");
            exit(0);
        }
    }

    char month[5];
    char weekday[5];
    if(tm.tm_mon+1==1){
        strcpy(month,"Jan");
    }
    if(tm.tm_mon+1==2){
        strcpy(month,"Feb");
    }
    if(tm.tm_mon+1==3){
        strcpy(month,"Mar");
    }
    if(tm.tm_mon+1==4){
        strcpy(month,"Apr");
    }
    if(tm.tm_mon+1==5){
        strcpy(month,"May");
    }
    if(tm.tm_mon+1==6){
        strcpy(month,"Jun");
    }
    if(tm.tm_mon+1==7){
        strcpy(month,"Jul");
    }
    if(tm.tm_mon+1==8){
        strcpy(month,"Aug");
    }
    if(tm.tm_mon+1==9){
        strcpy(month,"Sep");
    }
    if(tm.tm_mon+1==10){
        strcpy(month,"Oct");
    }
    if(tm.tm_mon+1==11){
        strcpy(month,"Nov");
    }
    if(tm.tm_mon+1==12){
        strcpy(month,"Dec");
    }
    if(tm.tm_wday+1==2){
        strcpy(weekday,"Mon");
    }
    if(tm.tm_wday+1==3){
        strcpy(weekday,"Tue");
    }
    if(tm.tm_wday+1==4){
        strcpy(weekday,"Wed");
    }
    if(tm.tm_wday+1==5){
        strcpy(weekday,"Thu");
    }
    if(tm.tm_wday+1==6){
        strcpy(weekday,"Fri");
    }
    if(tm.tm_wday+1==7){
        strcpy(weekday,"Sat");
    }
    if(tm.tm_wday+1==1){
        strcpy(weekday,"Sun");
    }

    if(argc==1 || (argc==2 && (strcmp(*(args+1),"-R")==0))) {
        if(argc==1){
            printf("%s %s %d %02d:%02d:%02d IST %d\n", weekday, month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
               tm.tm_year + 1900);
        }
        else{
            printf("%s, %d %s %d %02d:%02d:%02d +0530 \n", weekday, tm.tm_mday, month, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
    }
    else{
        printf("%s %s %d %02d:%02d:%02d UTC %d\n", weekday, month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
               tm.tm_year + 1900);
    }
    exit(0);
}
