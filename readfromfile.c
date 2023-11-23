#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readfromfile.h"
#include "debugmalloc.h"


// Gets a filename,
// it has an output of the questions inside a dynamicArray type pointer
// Maximum memory usage is 1 315 000 bytes, by hard cap.
// I modified debugmalloc's maximum allocatable memory limit in order to make this happen.
// freeing is up to the user!!!
extern void readFromFile(const char *szFilename, dynamicArray *arrayofquestions) {
    FILE *fp;
    fp = fopen(szFilename, "r");
    if (fp == NULL) {
        printf("error opening question file\n");
        exit(EXIT_FAILURE);
    }


    int size=0;
    char line[550];

    arrayofquestions->numberofQuestions = 0;
    arrayofquestions->questions = NULL;
    //counting number of lines
    while (fgets(line, sizeof(line),fp)!=NULL){
        size++;
    }
    // limted memory usage of the database
    if(size>2501)
    {
        // need to indicate if this activates
        size=2500;
    }
    fclose(fp);

    //to start again from the top of the file
    FILE *fp2;
    fp2 = fopen(szFilename, "r");
    //index to the questions
    int i=0;

    //allocating memory based on the previous line counting
    arrayofquestions->questions = (QuestionDataModel*) malloc(sizeof(QuestionDataModel) * (size));
    if(arrayofquestions->questions==NULL){
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp) && i<size) {

        // reads from the "line" string to the questions array inside array of questions struct
        const char *format = "%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%1[^;];%24[^\n]";
        sscanf(line, format,
               arrayofquestions->questions[i].question,
               arrayofquestions->questions[i].answerA,
               arrayofquestions->questions[i].answerB,
               arrayofquestions->questions[i].answerC,
               arrayofquestions->questions[i].answerD,
               &arrayofquestions->questions[i].correctAnswer,
               arrayofquestions->questions[i].category);
        arrayofquestions->numberofQuestions++;
        // increasing the index of the question
        i++;

    }

    fclose(fp2);
}

