#include <stdio.h>
#include "leaderboard.h"
#include "debugmalloc.h"
// Swaps to two leaderboard type pointers, to be used in bubble sort function
static void swap(Leaderboard *a, Leaderboard *b) {
    Leaderboard temp = *a;
    *a = *b;
    *b = temp;
}

// A sorting algorithm minimizing cpu usage
static void bubbleSort(dynamicLeaderboard *leader)
{

    int n = leader->iNumberOfLines;
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (leader->leaders[j].iReward < leader->leaders[j+1].iReward) {
                swap(&leader->leaders[j], &leader->leaders[j+1]);
                swapped = true;
            }
        }

        // If no elements were swapped by inner loop, break
        if (swapped == false)
            break;
    }
}
// gets the records that are already in the file and stores them in the
// leader (dynamicLeaderboard type struct)
// allocates memory, freeing is in the writeleaderboard function
// exits when leaderboard.csv can't be opened, and if it can't allocate memory for sName
// maximum memory usage 1250 bytes the limit is set uppon ending a game
extern void leaderboard(dynamicLeaderboard *leader) {
    FILE *fp;
    fp = fopen("Leaderboard.csv", "r");
    if (fp == NULL) {
        printf("error opening file");
        exit(EXIT_FAILURE);
    }

    int size = 0;
    // a string representing a line of the file
    char sLine[50];

    // Counting number of lines
    while (fgets(sLine, sizeof(sLine), fp) != NULL) {
        size++;
    }
    fclose(fp);
    // setting the int iNumberOfLines (inside the dynamicLeaderboard struct leader)
    // variable to the counted size


    leader->iNumberOfLines = size;
    // Allocating memory for Leaderboard array
    leader->leaders = (Leaderboard *)malloc(sizeof(Leaderboard) * size);
    // NULL is needed when the leaderboard is empty

    FILE *fp1;
    fp1 = fopen("Leaderboard.csv", "r");
    if (fp1 == NULL) {
        printf("error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fgets(sLine, sizeof(sLine), fp1) && i < size) {
        // Allocating memory for Sname
        leader->leaders[i].Sname = (char *)malloc(25);
        if (leader->leaders[i].Sname == NULL) {
            printf ("memory allocation failed for sName");
            exit(EXIT_FAILURE);
        }
        // scaning data into each leader from each line
        const char *format = "%24[^;];%d;%lf";
        sscanf(sLine, format,
               leader->leaders[i].Sname,
               &leader->leaders[i].iReward,
               &leader->leaders[i].dTimeplayed
        );
        i++;
    }

    bubbleSort(leader);

    fclose(fp1);
}
// need to sort before this
// this function in called from the main,
// it displays the leaderboard in order
extern void leaderboardprinter(dynamicLeaderboard *leader) {
    for (int i = 0; i < leader->iNumberOfLines; i++) {
        printf("[%d.]place %s won %d ft in %gs \n", i + 1, leader->leaders[i].Sname,
            leader->leaders[i].iReward, leader->leaders[i].dTimeplayed);
        free(leader->leaders[i].Sname);  // Free memory for each Sname
    }
    free(leader->leaders);  // Free memory for Leaderboard array
}


