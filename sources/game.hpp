#ifndef _GAME_HPP
#define _GAME_HPP

#include "player.hpp"
#include "log.hpp"
#include "card.hpp"

#define P1_BOUNDARY 0
#define P2_BOUNDARY 26

namespace ariel{
class Game
{
private:
    Player &p1;
    Player &p2;
    Log* head;
    Log* tail;
    Card onDesk[52];
    bool isGameOver=false;
    int totalGames;
    int DrawsNum;
    int NumCardsForEachPlayerOnDesk;

public:
    Game(Player &p1,Player &p2);
    ~Game();
    void setTail(Log* new_tail);
    void playTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    void printLastTurn();
    void createGame();
    void createDesk();
    void foldAndDeal(int low_boundary, int high_boundary, bool isContinious);
    int getnumdraws();
    void setNumOfDraws();
    int getTotalGames();
    void incTotalgames();
    int getNumCardsForEachPlayerOnDesk();
};
}
#endif
