#include "readfromfile.h"
#include "writetofile.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "debugmalloc.h"

// The function calls the readfromfile function and than starts a game
// if the user gives the right answer it progresses to the next question
extern void game (char *sName,char cDifficulty)
{
    dynamicArray questionsarray;
    // calling the readFromFile function based on the choosen difficulty
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
    // temporary variable resetted for each question
    QuestionDataModel model;

    clock_t t;
    t = clock();
    // timer starts
    // running until the last question (15), or wrong answer
    char cHalfHelper;
    char cAudienceHelper;
    bool bDidUseHalf=false;
    bool bDidUseAudience=false;

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
        // printf("%c",model.correctAnswer);
        printf("A valasz betujele:");
        if(bDidUseHalf==false)
        {
            printf("\nSzeretne felhasznalni a felezo segitseget?\n(i)(n)");
            getchar();
            scanf("%c",&cHalfHelper);

            if(cHalfHelper=='i'&& bDidUseHalf==false)
            {
                bDiduseHelp=true;
                bool printA=false;
                bool printB=false;
                bool printC=false;
                bool printD=false;
                bool didChoseAnother=false;

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
                bDidUseHalf=true;
            }
        }
        if(bDidUseAudience==false && bDiduseHelp==false)
        {
            printf("\nSzeretne felhasznalni a kozonseg segitseget?\n(i)(n)");
            getchar();
            scanf("%c",&cAudienceHelper);
            if(cAudienceHelper=='i'&& bDidUseAudience==false)
            {



                int iNumberofA = 0;
                int iNumberofB = 0;
                int iNumberofC = 0;
                int iNumberofD = 0;
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

    t = clock() - t;
    double time = ((double)t)/CLOCKS_PER_SEC;
    // calculate the elapsed time


    // freeing the received pointer from readFromFile function
    free(questionsarray.questions);


    // write the records to the file when a game ends
    writetofile(sName,aiRewards[iRewardIndex],time);

    if(iRewardIndex!=15){
        printf("Gratulalunk nyeremenye %d ft!",aiRewards[iRewardIndex-1]);
    }
    else
        printf("Megnyerete a fonyeremenyt 50000000 forintot!");

}

