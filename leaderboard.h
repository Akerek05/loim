#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

typedef struct Leaderboard{
char *Sname;
int iReward;
double dTimeplayed;
}Leaderboard;

typedef struct dynamicLeaderboard{
Leaderboard *leaders;
int iNumberOfLines;
}dynamicLeaderboard;

void leaderboard(dynamicLeaderboard *leader);

void leaderboardprinter(dynamicLeaderboard* leader);



#endif // LEADERBOARD_H_INCLUDED
