#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "log.hpp"
#include "card.hpp"

#include <array>

constexpr int P1_BOUNDARY = 0;
constexpr int P2_BOUNDARY = 26;
constexpr int NUM_OF_CARDS_AT_DECK = 52;

namespace ariel{
class Game
{
private:
    Player &p1;
    Player &p2;
    Log head;
    Log tail;
    std::array<Card, NUM_OF_CARDS_AT_DECK> deck;
    bool isGameOver=false;
    int totalRounds=0;
    int DrawsNum=0;
    int NumCardsForEachPlayerOnDesk=0;
    int num_of_turns_had_tie=0;

    void createGame();
    void createDeck();
    void cleanDeck(int low_boundary, int high_boundary);
    void foldAndDeal(int low_boundary, int high_boundary, bool isContinious);
    void endGame();
    void incTotalRounds();
    void incNumOfDrawsBy(int n);
    void setTail(Log* new_tail);
    void closeTurn(Player &plyr);

public:
    Game(Player &ply1,Player &ply2);
    ~Game();
    Player* getPlayer(int one_or_two) const;
    void playTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    void printLastTurn();
    //int getnumdraws() const;
    int getTotalRounds() const;
    //int getNumCardsForEachPlayerOnDesk() const;
};
}
#endif
