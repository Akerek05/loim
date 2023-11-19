#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readfromfile.h"
#include "debugmalloc.h"


//gets a filename,
//it has an output of the questions inside a dynamicArray type pointer
// Maximum memory usage is 1 185 078 bytes,
//I modified debugmalloc's maximum allocatable memory limit in order to make this happen.
//freeing is up to the user!!!
extern void readFromFile(char *filename, dynamicArray *arrayofquestions) {
    FILE *fp;
    fp = fopen(filename, "r");
    int size=0;
    char line[550];

    arrayofquestions->numberofQuestions = 0;
    arrayofquestions->questions = NULL;
    //counting number of lines
    while (fgets(line, sizeof(line),fp)!=NULL){
        size++;


    }
    printf("%d\n",size);
    fclose(fp);

    //to start again from the top of the file
    FILE *fp2;
    fp2 = fopen(filename, "r");
    //index to the questions
    int i=0;

    //allocating memory based on the previous line counting
    arrayofquestions->questions = (QuestionDataModel*) malloc(sizeof(QuestionDataModel) * (size));
    if(arrayofquestions->questions==NULL){
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp) && i<size) {

        //reads from the "line" string to the questions array inside array of questions struct
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
        // incrasing the index of the question
        i++;

    }

    fclose(fp2);
}

