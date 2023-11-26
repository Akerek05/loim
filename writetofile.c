#include <stdio.h>
#include "leaderboard.h"
#include "writetofile.h"
#include "debugmalloc.h"
// doesn't have file opening test because if the file can't be open it exits in the leaderboard function
// gets the name the prize and the time from the caller (game)
// first gets an dynamicleaderboard type pointer from leaderboard (gets record from file and sorts)
// than places them back but only a limited number and the one from the current game's stats
extern void writetofile (char *sName,const int prize,const double time){
    dynamicLeaderboard leader;
    // gets the records already in the file to the leader struct
    leaderboard(&leader);
    // limiting number of lines in order to limit memory usage and file size
    // the lost ones have the lowest scores
    int iMaxDataLength=leader.iNumberOfLines;
    if(leader.iNumberOfLines>50){
        leader.iNumberOfLines=49;
    }

    FILE* fp;
    fp = fopen("Leaderboard.csv","w");
    // printing the previous records back in order not to overwrite data
    for (int i = 0; i < leader.iNumberOfLines; i++) {
        fprintf(fp,"%s;%d;%g;\n",leader.leaders[i].Sname,
            leader.leaders[i].iReward, leader.leaders[i].dTimeplayed);

    }
    for (int i = 0; i < iMaxDataLength; i++){
        free(leader.leaders[i].Sname);  // Free memory for each Sname
    }
    free(leader.leaders);  // Free memory for Leaderboard array
    // printing the record of the current game's data to the end
    fprintf(fp,"%s;%d;%g",sName,prize,time);
    fclose(fp);
}
