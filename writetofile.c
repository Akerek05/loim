#include <stdio.h>
#include "leaderboard.h"
#include "writetofile.h"
#include "debugmalloc.h"
extern void writetofile (char *sName,int prize,double time){
    dynamicLeaderboard leader;
    // gets the records already in the file to the leader struct
    leaderboard(&leader);


    FILE* fp;
    fp = fopen("Leaderboard.csv","w");
    // printing the previous records back in order not to overwrite data
    for (int i = 0; i < leader.iNumberOfLines; i++) {
        fprintf(fp,"%s;%d;%g;\n",leader.leaders[i].Sname,
            leader.leaders[i].iReward, leader.leaders[i].dTimeplayed);
        free(leader.leaders[i].Sname);  // Free memory for each Sname
    }
    free(leader.leaders);  // Free memory for Leaderboard array
    // printing the record of the current game's data to the end
    fprintf(fp,"%s;%d;%g",sName,prize,time);
    fclose(fp);
}
