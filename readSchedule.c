#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day;
    int ampm;
    int period;
} CoursePeriod;

typedef struct
{
    char *code;
    char *name;
    CoursePeriod startPeriod;
    CoursePeriod endPeriod;
    unsigned long weeks;
    char *room;
} Course;

Course *createCourse()
{
    Course *tempCourse = malloc(sizeof(Course));
    tempCourse->code = malloc(sizeof(char) * 10);
    tempCourse->name = malloc(sizeof(char) * 30);
    tempCourse->room = malloc(sizeof(char) * 10);
    tempCourse->weeks = 0;
    return tempCourse;
}

void deleteCourse(Course *tempCourse)
{
    free(tempCourse->code);
    free(tempCourse->name);
    free(tempCourse->room);
    free(tempCourse);
}

int readPeriod(char *inputString, CoursePeriod *tempCoursePeriod)
{
    if (strlen(inputString) != 3)
    {
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

void setWeek(int week, Course *tempCourse)
{
    if (week >= 64 || week <= 0)
    {
        return;
    }
    else
    {
        tempCourse->weeks |= (1UL << (week - 1));
    }
}

void clearWeek(int week, Course *tempCourse)
{
    if (week >= 64 || week <= 0)
    {
        return;
    }
    else
    {
        tempCourse->weeks &= (~(1UL << (week - 1)));
    }
}

unsigned long setallbitgivenrange(unsigned long n, unsigned long l, unsigned long r) 
{ 
    // calculating a number 'range' having set 
    // bits in the range from l to r and all other 
    // bits as 0 (or unset). 
    
    unsigned long range = (((1UL << (l - 1)) - 1UL) ^     
                ((1UL << (r)) - 1UL)); 
  
    return (n | range); 
} 

void weekRangetoWeek(char *inputString, Course *tempCourse)
{
    char tempString[10];
    int i = 0;
    int startWeek;
    int endWeek;
    int k = 0;
    while (inputString[k] != '-')
    {
        tempString[i] = inputString[k];
        i++;
        k++;
    }
    tempString[i] = '\0';
    startWeek = atoi(tempString);
    i = 0;
    k++;

    while (inputString[k] != '\0')
    {
        tempString[i] = inputString[k];
        i++;
        k++;
    }
    tempString[i] = '\0';
    endWeek = atoi(tempString);

    if(startWeek > endWeek)
        return;
    else if(startWeek <= 0){
        return;
    }
    else if(endWeek >= 64){
        return;
    }
    else if(endWeek==startWeek){
        setWeek(startWeek, tempCourse);
    }
    else{
        tempCourse->weeks = setallbitgivenrange(tempCourse->weeks,startWeek-1,endWeek-1);
    }
}

void readWeek(char *inputString, Course *tempCourse)
{
    char tempString[1000];
    int flag = 0;
    int i = 0;
    int k = 0;
 
    while (inputString[k] != '\0')
    {
        while (inputString[k] != ',')
        {
            tempString[i] = inputString[k];
            if (tempString[i] == '-')
                flag = 1;
            i++;
            k++;
        }
        tempString[i] = '\0';
        if (flag != 1)
        {
            setWeek(atoi(tempString), tempCourse);
        }
        else
        {
            //puts(tempString);
            weekRangetoWeek(tempString, tempCourse);
        }
        i = 0;
        flag = 0;
        k++;
    }
}

void readWeekAndRoom(char *inputString, Course *tempCourse)
{
    char tempStringNum[2];
    char tempString[1000];
    tempStringNum[1] = '\0';
    int k = strlen(inputString);
    while (inputString[k] != ',')
    {
        k--;
    }
    strcpy(tempCourse->room, inputString + k + 1);
    strcpy(tempString, inputString);
    tempString[k + 1] = '\0';
    readWeek(tempString, tempCourse);
}

char *weekToString(int week)
{
    char *outputString;
    outputString = malloc(20);
    switch (week)
    {
    case 2:
        strcpy(outputString, "Monday");
        break;
    case 3:
        strcpy(outputString, "Tuesday");
        break;
    case 4:
        strcpy(outputString, "Wednesday");
        break;
    case 5:
        strcpy(outputString, "Thursday");
        break;
    case 6:
        strcpy(outputString, "Friday");
        break;
    case 7:
        strcpy(outputString, "Saturday");
        break;
    case 8:
        strcpy(outputString, "Sunday");
        break;
    default:
        outputString[0] = '\0';
    }
    return outputString;
}

char *ampmToString(int ampm)
{
    char *outputString;
    outputString = malloc(20);
    switch (ampm)
    {
    case 1:
        strcpy(outputString, "Morning");
        break;
    case 2:
        strcpy(outputString, "Afternoon");
        break;
    default:
        outputString[0] = '\0';
    }
    return outputString;
}

char *periodArrayToString(int ampm)
{
    char *outputString;
    outputString = malloc(20);

    return outputString;
}

int readSchedule(FILE *file, Course *tempCourse)
{
    char c;
    char tempString[1000];

    fscanf(file, "%[^\t]s", tempCourse->code);
    fgetc(file);

    fscanf(file, "%[^\t]s", tempCourse->name);
    fgetc(file);

    fscanf(file, "%[^,]s", tempString);
    fgetc(file);

    if (readPeriod(tempString, &(tempCourse->startPeriod)) == 0)
    {
        return 0;
    }

    fscanf(file, "%[^,]s", tempString);
    fgetc(file);

    if (readPeriod(tempString, &(tempCourse->endPeriod)) == 0)
    {
        return 0;
    }

    fscanf(file, "%[^;]s", tempString);
    fgetc(file);

    readWeekAndRoom(tempString, tempCourse);
    return 1;
}

void printInfoCourse(Course *tempCourse)
{
    char *weekString = weekToString(tempCourse->startPeriod.day);
    char *ampmString = ampmToString(tempCourse->startPeriod.ampm);

    printf("%s\t|%s\t|%s\t|%s\t|%d-%d\t|%x\t|%s\t|",
           tempCourse->code,
           tempCourse->name,
           weekString,
           ampmString,
           tempCourse->startPeriod.period,
           tempCourse->endPeriod.period,
           tempCourse->weeks,
           tempCourse->room);
    puts("\n");

    free(weekString);
    free(ampmString);
}

int main(int argc, char **argv)
{
    char *fileName;
    Course *tempCourse = createCourse();
    if(argc < 2)
    {
        printf("Too few agruments\n");
        return 0;
    }

    fileName = argv[1];
    FILE *schedule;

    schedule = fopen(fileName, "r");
    readSchedule(schedule, tempCourse);

    printInfoCourse(tempCourse);
    fclose(schedule);
    return 0;
}