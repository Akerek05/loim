#include <stdio.h>
#include "game.h"
#include <string.h>
#include "debugmalloc.h"
#include "leaderboard.h"


//The function gets a name,and a difficulty from the user and returns difficulty,
// and name as a pointer.
static char getNameDifficulty (char *sName){
    printf("Mi a neve? ");
    char cDifficulty;
    char n[25];


    fgets(n,20,stdin);
    n[strcspn(n,"\n")] = '\0';
    strcpy(sName,n);

    difficutyagain:

    printf("Milyen nehezsegen szeretne jatszani?\nKezdo (k)\nHalado (h)\nProfi (p)\n");
    scanf("%c",&cDifficulty);
    system("cls");
    if(cDifficulty != 'k' && cDifficulty != 'h' && cDifficulty != 'p')
    {
        printf("nem sikerult a valasztas, ujra probalkozas.\n");
        goto difficutyagain;
    }
    return cDifficulty;
}
//This is the main function which first asks the user if they want to play or view the leaderboard.
//If the user chooses to play than it first call the getNameDifficulty
//and than with this data it calls game function;
int main (void){
    menu:

    printf("Legyen on is milliomos!\n\n");
    char cMenuOption;
    printf("Jatek  (j)\n");
    printf("Dicsosegtabla (d)\n");
    printf("Kilepes (k)\n");

    scanf("%c",&cMenuOption);
    getchar();

    char sName[20];
    char cDifficulty;
    dynamicLeaderboard currentleaders;

    switch (cMenuOption){

        case 'j':
            //getting name and difficulty from the user
            cDifficulty=getNameDifficulty(sName);
            game(sName, cDifficulty);
            getchar();
            // returning to menu on any button

            getchar();
            system("cls");

            goto menu;

        case 'd':
            // gets the written record from the file and puts it into currentleaders
            // also sorts the members of currentleaders in increasing order by their won reward
            leaderboard(&currentleaders);
            // displays the members of the currentleaders in order
            leaderboardprinter(&currentleaders);
            // returning to menu on any button
            getchar();
            system("cls");
            goto menu;

        case 'k':
            // leaving the game
            return 0;
        default:
            // returns to menu when choosing option is failed
            system("cls");
            printf("Nem valasztottal letezo lehetoseget\n");
            goto menu;
    }

    return 0;
}



