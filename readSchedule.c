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
    int weekCount;
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

void weekRangetoWeek(char inputString, int *week, int *weekCount){

}

void readWeek(char *inputString, int *weeks){
    char tempString[1000];
    int weekCount = 0;
    int flag = 0;
    int i = 0;
    int k = 0;
    while(inputString[k]!='\0')
    {
        while(inputString[k]!=','){
            tempString[i] = inputString[i];
            if(tempString[i]='-');
                flag = 1;
            i++;
            k++;
        }
        tempString[i] = '\0';
        if(flag!=1){
            weeks[weekCount] = atoi(tempString);
            weekCount++;
        }
        else{
            weekRangetoWeek(tempString,weeks,&weekCount);
        } 
        i = 0;
    }
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
    strcpy(tempString,inputString);
    tempString[k+1] = '\0';
    readWeek(tempString,tempCourse->weeks);
}

char *weekToString(int week){
    char *outputString;
    outputString = malloc(20);
    switch(week){
        case 2: strcpy(outputString,"Monday"); break;
        case 3: strcpy(outputString,"Tuesday"); break;
        case 4: strcpy(outputString,"Wednesday"); break;
        case 5: strcpy(outputString,"Thursday"); break;
        case 6: strcpy(outputString,"Friday"); break;
        case 7: strcpy(outputString,"Saturday"); break;
        case 8: strcpy(outputString, "Sunday"); break;
        default: outputString[0] = '\0';
    }
    return outputString;
}

char *ampmToString(int ampm){
    char *outputString;
    outputString = malloc(20);
    switch(ampm){
        case 1: strcpy(outputString,"Morning"); break;
        case 2: strcpy(outputString,"Afternoon"); break;
        default: outputString[0] = '\0';
    }
    return outputString;
}

char *periodArrayToString(int ampm){
    char *outputString;
    outputString = malloc(20);
    
    return outputString;
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
    printf("%s\t|%s\t|%s\t|%s\t|%d-%d\t|%s\t|%s\t|",
    tempCourse->code,
    tempCourse->name,
    weekToString(tempCourse->startPeriod.day),
    ampmToString(tempCourse->startPeriod.ampm),
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