#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUF_SIZE 80
#define NAME_SIZE 20
#define SEMESTER_SIZE 3
#define GROUP_SIZE 10

enum FileType {
    CSV,
    JSON,
    XML
}input, output;

enum FileType getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".csv") == 0)
        {
            return CSV;
        }
        else if (strcmp(ext, ".json") == 0)
        {
            return JSON;
        }
        else if (strcmp(ext, ".xml") == 0)
        {
            return XML;
        }
        else
        {
            printf("wrong format!\n");
            printf("-i input.file -o output.file\n");
            printf("or\n");
            printf("-o output.file -i input.file\n");
            exit(0);
        }
    }
    return JSON;
}

typedef struct {
    char lastname[NAME_SIZE];
    char name[NAME_SIZE];
    unsigned number;
    char semester[SEMESTER_SIZE];
    char group[GROUP_SIZE];
    float grade;
} Student;

Student list[100];
int count_objects_input = 0;

bool readCSV(const char *file_name){
    char puffer[BUF_SIZE];
    char *ptr_lastname, *ptr_name, *ptr_number, *ptr_semester, *ptr_group, *ptr_note;

    FILE *csv;
    csv = fopen(file_name, "r");
    if (csv == NULL) {
        return false;
    }

    while (fgets(puffer, BUF_SIZE, csv)) {
        ptr_lastname = strtok(puffer, ";");
        strcpy(list[count_objects_input].lastname, ptr_lastname);

        ptr_name = strtok(NULL, ";");
        strcpy(list[count_objects_input].name, ptr_name);

        ptr_number = strtok(NULL, ";");
        list[count_objects_input].number = atoi(ptr_number);

        ptr_semester = strtok(NULL, ";");
        strcpy(list[count_objects_input].semester, ptr_semester);

        ptr_group = strtok(NULL, ";");
        strcpy(list[count_objects_input].group, ptr_group);

        ptr_note = strtok(NULL, ";");
        list[count_objects_input].grade = (float) atof(ptr_note);

        count_objects_input++;
    }
    fclose(csv);
    return true;
}

bool readJSON(const char *file_name){
    return true;
}

bool readXML(const char *file_name){
    return true;
}

bool writeJSON(const char *file_name){
    FILE *json;
    json = fopen(file_name, "r");
    if (json == NULL) {
        return false;
    }
    fclose(json);

    json = fopen(file_name, "w");


    fprintf(json, "[\n");

    for (int i = 0; i < count_objects_input; i++) {
        if(i == count_objects_input - 1){
            fprintf(json, "{    \n");
            fprintf(json, "        \"lastname\": \"%s\",\n", list[i].lastname);
            fprintf(json, "        \"name\": \"%s\",\n", list[i].name);
            fprintf(json, "        \"number\": \"%d\",\n", list[i].number);
            fprintf(json, "        \"semester\": \"%s\",\n", list[i].semester);
            fprintf(json, "        \"group\": \"%s\",\n", list[i].group);
            fprintf(json, "        \"grade\": \"%f\"\n", list[i].grade);
            fprintf(json, "    }\n");
        }
        else{
            fprintf(json, "{\n");
            fprintf(json, "    \"lastname\": \"%s\",\n", list[i].lastname);
            fprintf(json, "    \"name\": \"%s\",\n", list[i].name);
            fprintf(json, "    \"number\": \"%d\",\n", list[i].number);
            fprintf(json, "    \"semester\": \"%s\",\n", list[i].semester);
            fprintf(json, "    \"group\": \"%s\",\n", list[i].group);
            fprintf(json, "    \"grade\": \"%f\"\n", list[i].grade);
            fprintf(json, "},\n");
        }
    }

    fprintf(json, "]");

    fclose(json);
    return true;
}

bool writeCSV(const char *file_name){
    return true;
}

bool writeXML(const char *file_name){
    FILE *xml;
    xml = fopen(file_name, "r");
    if (xml == NULL) {
        return false;
    }
    fclose(xml);

    xml = fopen(file_name, "w");


    fprintf(xml, "<student_list>\n");

    for (int i = 0; i < count_objects_input; i++) {
        fprintf(xml, "    <student>\n");
        fprintf(xml, "        <lastname>%s</lastname>\n", list[i].lastname);
        fprintf(xml, "        <name>%s</name>\n", list[i].name);
        fprintf(xml, "        <number>%d</number>\n", list[i].number);
        fprintf(xml, "        <semester>%s</semester>\n", list[i].semester);
        fprintf(xml, "        <group>%s</group>\n", list[i].group);
        fprintf(xml, "        <grade>%f</grade>\n", list[i].grade);
        fprintf(xml, "    </student>\n");
    }

    fprintf(xml, "</student_list>\n");

    fclose(xml);
    return true;
}

int main(int argc, char *argv[]) {

    char inputArg[] = "-i";
    char outputArg[] = "-o";
    char* inputFile;
    char* outputFile;

    if(strcmp(argv[1], inputArg) == 0)
    {
        inputFile = argv[2];
    }
    else if(strcmp(argv[3], inputArg) == 0)
    {
        inputFile = argv[4];
    }
    else
    {
        printf("wrong format!\n");
        printf("-i input.file -o output.file\n");
        printf("or\n");
        printf("-o output.file -i input.file\n");
        exit(0);
    }

    if(strcmp(argv[1], outputArg) == 0)
    {
        outputFile = argv[2];
    }
    else if(strcmp(argv[3], outputArg) == 0)
    {
        outputFile = argv[4];
    }
    else
    {
        printf("wrong format!\n");
        printf("-i input.file -o output.file\n");
        printf("or\n");
        printf("-o output.file -i input.file\n");
        exit(0);
    }
    bool (*readerFuncs[])(const char*) = {readCSV, readJSON, readXML};
    bool (*writerFuncs[])(const char*) = {writeCSV, writeJSON, writeXML};

    enum FileType input_type = getFileType(inputFile);
    enum FileType output_type = getFileType(outputFile);

    if((*readerFuncs[input_type])(inputFile))
    {
        printf("reading done...\n");
        if((*writerFuncs[output_type])(outputFile))
            printf("writing done...\n");
        else
        {
            printf("wrong format!\n");
            printf("-i input.file -o output.file\n");
            printf("or\n");
            printf("-o output.file -i input.file\n");
            exit(0);
        }
    }

    else
    {
        printf("wrong format!\n");
        printf("-i input.file -o output.file\n");
        printf("or\n");
        printf("-o output.file -i input.file\n");
        exit(0);
    }
    return 0;
}

