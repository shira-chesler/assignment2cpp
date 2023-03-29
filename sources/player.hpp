#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <array>
#include "card.hpp"

constexpr int MAX_CARDS_FOR_PLAYER = 26;

namespace ariel{
class Player
{
private:
    std::string name;
    int cards_won;
    int stack_size;
    std::array<Card, MAX_CARDS_FOR_PLAYER> cards;
    int winNums;
    double winRate;
    bool registerdToGame;

public:
    Player();
    Player(std::string name);
    Player(Player &plr);
    ~Player();
    int stacksize();
    int cardesTaken();
    void updateCardsTaken(int num);
    std::string getName();
    void setstacksize(int num);
    Card draw();
    std::string getStats();
    void updateCard(Card crd, int idx);
    int getWinNums();
    void incWinNums();
    double getWinRate();
    void setWinRate(int totalRounds);
    void setRegisteredToGame();
    bool getRegisteredToGame();
    
};
}
#endif
