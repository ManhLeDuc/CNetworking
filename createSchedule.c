#include <stdio.h>
int main(int argc, char **argv){
    char *fileName;
    fileName = argv[1];
    FILE *schedule;
    schedule = fopen(fileName,"w+");
    fprintf(schedule,"IT3080\tComputer Network\t523,526,22,25-31,33-40,TC-502;\n");
    fprintf(schedule,"IT4560\tComputer Literacy\t221,224,22,25-31,33-40,TC-211;\n");
    fprintf(schedule,"IT4590\tDatabase\t524,526,22,25-31,33-40,D6-101;\n");
    fprintf(schedule,"IT4935\tDatabase Lab\t615,616,22,25-31,D6-303;");
    fclose(schedule);
}