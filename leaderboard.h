#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED
//112 bytes
typedef struct Leaderboard{
char *Sname;//25*4
int iReward; //4
double dTimeplayed;//8
}Leaderboard;

typedef struct dynamicLeaderboard{
Leaderboard *leaders;
int iNumberOfLines;
}dynamicLeaderboard;

void leaderboard(dynamicLeaderboard *leader);

void leaderboardprinter(dynamicLeaderboard* leader);



#endif // LEADERBOARD_H_INCLUDED
