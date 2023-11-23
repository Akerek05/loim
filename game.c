#include "readfromfile.h"
#include "writetofile.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "debugmalloc.h"

// The function calls the readFromFile function and than starts a game
// if the user gives the right answer it progresses to the next question
// accepts lower and uppercase letters as answers, other letters are treated as wrong answers
// receives the users name as a character array, difficulty as a char
// frees up questionsarray received from readFromFile
extern void game (char *sName,char cDifficulty)
{
    dynamicArray questionsarray;
    // calling the readFromFile function based on the chosen difficulty
    if(cDifficulty=='k'){
    readFromFile("kezdo.csv",&questionsarray);
    }
    if(cDifficulty=='h'){
    readFromFile("halado.csv",&questionsarray);
    }
    if(cDifficulty=='p'){
    readFromFile("profi.csv",&questionsarray);
    }

    system("cls");//wiping the screen
    // array of rewards for each number of question
    int aiRewards[]={0,10000,20000,50000,100000,250000,500000,750000,1000000,1500000,2000000,5000000,10000000,15000000,25000000,50000000};
    // randomising question number based on the number of questions in each file
    srand(time(0));
    int iQuestionindex = (rand()%questionsarray.numberofQuestions)+1;
    // left in test if the functions work properly
    // printf("number of questions %d , random number %d\n",questionsarray.numberofQuestions,iQuestionindex);
    // number of the question 1-15
    int iRewardIndex=0;
    char cAnswer;
    // temporary variable reseted for each question
    QuestionDataModel model;

    char cHalfHelper;
    char cAudienceHelper;
    bool bDidUseHalf=false;
    bool bDidUseAudience=false;

    clock_t temp;
    temp = clock();
    // timer starts

    do{
        bool bDiduseHelp=false;
        system("cls");
        // increasing index for each question
        iRewardIndex++;
        // the main line of the game updating the user about the question number
        // and reward for answeing
        printf("----Question[%d] for %d ft \n\n",iRewardIndex,aiRewards[iRewardIndex]);

        model = questionsarray.questions[((iQuestionindex+iRewardIndex)%questionsarray.numberofQuestions)+1];
        printf("%s\n", model.category);
        printf("%s\n", model.question);
        printf("[A]:%s\n", model.answerA);
        printf("[B]:%s\n", model.answerB);
        printf("[C]:%s\n", model.answerC);
        printf("[D]:%s\n", model.answerD);

        printf("A valasz betujele:");
        // Halving answer options can only be used once
        if(bDidUseHalf==false)
        {
            printf("\nSzeretne felhasznalni a felezo segitseget?\n(i)(n)");
            getchar();
            scanf("%c",&cHalfHelper);
            // if anything other than i is received nothing happens counts as no
            if(cHalfHelper=='i'&& bDidUseHalf==false)
            {
                bDiduseHelp=true;
                // helping bools for each answer
                bool printA=false;
                bool printB=false;
                bool printC=false;
                bool printD=false;
                bool didChoseAnother=false;
                // determining which is the answer and setting it's print true
                switch(model.correctAnswer){

                case 'A':
                    printA=true;
                    break;
                case 'B':
                    printB=true;
                    break;
                case 'C':
                    printC=true;
                    break;
                case 'D':
                    printD=true;
                    break;
                }
                do {
                    // choosing an another letter to write, randomised
                    char randomletter = 'A' + (rand() % 4);
                    if (randomletter!=model.correctAnswer)
                    {
                        switch(randomletter){

                            case 'A':
                                printA=true;
                                didChoseAnother=true;
                                break;

                            case 'B':
                                printB=true;
                                didChoseAnother=true;
                                break;

                            case 'C':
                                printC=true;
                                didChoseAnother=true;
                                break;

                            case 'D':
                                printD=true;
                                didChoseAnother=true;
                                break;
                        }
                    }
                }
                while(!didChoseAnother);
                // printing the options again this time only the correct and a wrong answer
                system("cls");
                printf("%s\n", model.category);
                printf("%s\n", model.question);
                if(printA){
                    printf("[A]:%s\n", model.answerA);
                }
                if(printB){
                    printf("[B]:%s\n", model.answerB);
                }
                if(printC) {
                    printf("[C]:%s\n", model.answerC);
                }
                if(printD) {
                    printf("[D]:%s\n", model.answerD);
                }
                    printf("A valasz betujele:");
                // In order not to use two helps in a single question
                bDidUseHalf=true;
            }
        }
        // Audience help, basically random, but double chance of the correct answer, can also only used once
        if(bDidUseAudience==false && bDiduseHelp==false)
        {
            printf("\nSzeretne felhasznalni a kozonseg segitseget?\n(i)(n)");
            getchar();
            scanf("%c",&cAudienceHelper);
            // if anything other than i is received nothing happens counts as no
            if(cAudienceHelper=='i'&& bDidUseAudience==false)
            {
                // counters for each answer option
                int iNumberofA = 0;
                int iNumberofB = 0;
                int iNumberofC = 0;
                int iNumberofD = 0;
                // simulating 100 answers
                for(int i=0; i<100;i++)
                {

                    int iRandomNumber = (rand() % 5)+1;
                    switch (iRandomNumber)
                    {
                        case 1:
                            iNumberofA++;
                            break;
                        case 2:
                            iNumberofB++;
                            break;
                        case 3:
                            iNumberofC++;
                            break;
                        case 4:
                            iNumberofD++;
                            break;
                        // extra chance for the correct answer
                        case 5:
                            switch(model.correctAnswer)
                            {

                                case 'A':
                                    iNumberofA++;
                                    break;
                                case 'B':
                                    iNumberofB++;
                                    break;
                                case 'C':
                                    iNumberofC++;
                                    break;
                                case 'D':
                                    iNumberofD++;
                                    break;
                            }
                            break;
                    }
                }
                // displaying the question with percentages added
                system("cls");
                printf("%s\n", model.category);
                printf("%s\n", model.question);
                printf("[A]:%s %d%c\n", model.answerA, iNumberofA,'%');
                printf("[B]:%s %d%c\n", model.answerB, iNumberofB,'%');
                printf("[C]:%s %d%c\n", model.answerC, iNumberofC,'%');
                printf("[D]:%s %d%c\n", model.answerD, iNumberofD,'%');

                bDidUseAudience=true;
            }

        }
        getchar();
        scanf("%c",&cAnswer);
        printf("\nCorrect answer:[%c].\n",model.correctAnswer);

    }while(toupper(cAnswer)==model.correctAnswer &&iRewardIndex<15);
    // running until the last question (15), or wrong answer

    temp = clock() - temp;
    double time = ((double)temp)/CLOCKS_PER_SEC;
    // calculate the elapsed time


    // freeing the received pointer from readFromFile function
    free(questionsarray.questions);


    // write the records to the file when a game ends
    writetofile(sName,aiRewards[iRewardIndex-1],time);

    if(iRewardIndex!=15){
        printf("Gratulalunk nyeremenye %d ft!",aiRewards[iRewardIndex-1]);
    }
    else
        printf("Megnyerete a fonyeremenyt 50000000 forintot!");

}

