#include <stdio.h>
int main(int argc, char **argv){
    char *fileName;
    fileName = argv[1];
    FILE *schedule;
    schedule = fopen(fileName,"w+");
    fprintf(schedule,"IT3080\tComputer Network\t523,526,22,25-31,33-40,TC-502;");
    fclose(schedule);
}