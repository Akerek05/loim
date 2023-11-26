#ifndef READFROMFILE_H_INCLUDED
#define READFROMFILE_H_INCLUDED

typedef struct QuestionDataModel
{

    char question[100];
    char answerA[100];
    char answerB[100];
    char answerC[100];
    char answerD[100];
    char correctAnswer;
    char category[25];
}QuestionDataModel;
typedef struct dynamicArray{
    QuestionDataModel *questions;
    int numberofQuestions;
}dynamicArray;
void readFromFile(const char *szFilename,dynamicArray *arrayofquestions);

#endif
