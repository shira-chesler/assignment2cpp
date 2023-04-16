#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "log.hpp"
#include "card.hpp"
#include <stdexcept>

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
    Log* ptail;
    std::array<Card, NUM_OF_CARDS_AT_DECK> deck;
    bool isGameOver=false;
    int totalRounds=0;
    int DrawsNum=0;
    int NumCardsForEachPlayerOnDesk=0;
    int num_of_turns_had_tie=0;
    bool had_first_turn=false;
    std::string p1_final_stats;
    std::string p2_final_stats;

    void createGame();
    void createDeck();
    void cleanDeck(int low_boundary, int high_boundary);
    void foldAndDeal(int low_boundary, int high_boundary, bool isContinious);
    void endGame();
    void incTotalRounds();
    void incNumOfDrawsBy(int n);
    void setTail(Log* new_tail);
    void closeTurn(Player &plyr);
    void registerPlayers();

public:
    Game(Player &ply1,Player &ply2);
    ~Game();
    Game(Game&&) noexcept;
    Game(const Game&);
    Game& operator=(const Game&);
    Game& operator=(Game&&) noexcept;
    Player* getPlayer(int one_or_two) const;
    void playTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    void printLastTurn();
    int getTotalRounds() const;
};
}
#endif
