#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day;
    int ampm;
    int period;
} CoursePeriod;

typedef struct {
    char code[10];
    char name[50];
    CoursePeriod startPeriod;
    CoursePeriod endPeriod;
    int weeks[100];
    char room[50];
} Course;

int readPeriod(char *inputString, CoursePeriod *tempCoursePeriod){
    if(strlen(inputString)!=3){
        return 0;
    }
    char tempStringNum[2];
    tempStringNum[1] = '\0';
    tempStringNum[0] = inputString[0];
    tempCoursePeriod->day = atoi(tempStringNum);

    tempStringNum[1] = '\0';
    tempStringNum[0] = inputString[1];
    tempCoursePeriod->ampm = atoi(tempStringNum);

    tempStringNum[1] = '\0';
    tempStringNum[0] = inputString[2];
    tempCoursePeriod->period = atoi(tempStringNum);
    return 1;
}

void readWeekAndRoom(char *inputString, Course *tempCourse){
    char tempStringNum[2];
    char tempString[1000];
    tempStringNum[1] = '\0';
    int k = strlen(inputString);
    while(inputString[k]!=','){
        k--;            
    }
    strcpy(tempCourse->room,inputString+k+1);
}

char *weekToString(int week){
    char *outputString;
    outputString = malloc(20);
    switch(week){
        case 1: strcpy(outputString,"Monday"); break;
    }
}

int readSchedule(FILE *file, Course *tempCourse){
    char c;
    char tempString[1000];
    
    fscanf(file,"%[^\t]s",tempCourse->code);
    fgetc(file);
    fscanf(file,"%[^\t]s",tempCourse->name);
    fgetc(file);

    fscanf(file,"%[^,]s",tempString);
    fgetc(file);

    if(readPeriod(tempString,&(tempCourse->startPeriod))==0){
        return 0;
    }

    fscanf(file,"%[^,]s",tempString);
    fgetc(file);

    if(readPeriod(tempString,&(tempCourse->endPeriod))==0){
        return 0;
    }

    fscanf(file,"%[^;]s",tempString);
    fgetc(file);

    readWeekAndRoom(tempString,tempCourse);
    return 1;
}

void printInfoCourse(Course* tempCourse){
    printf("%s\t|%s\t|%d\t|%d\t|%d-%d\t|%s\t|%s\t|",
    tempCourse->code,
    tempCourse->name,
    tempCourse->startPeriod.day,
    tempCourse->startPeriod.ampm,
    tempCourse->startPeriod.period,
    tempCourse->endPeriod.period,
    "alo",
    tempCourse->room
    );
    puts("\n");
}

int main(int argc, char **argv){
    char *fileName;
    Course tempCourse;
    fileName = argv[1];
    FILE *schedule;
    schedule = fopen(fileName,"r");
    readSchedule(schedule,&tempCourse);
    printInfoCourse(&tempCourse);
    fclose(schedule);
    return 0;
}