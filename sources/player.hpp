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
    int cards_won=0;
    int stack_size;
    std::array<Card, MAX_CARDS_FOR_PLAYER> cards;
    int winNums=0;
    double winRate=0;
    bool registerdToGame=false;

public:
    Player();
    Player(std::string name);
    ~Player();
    int stacksize();
    int cardesTaken();
    void updateCardsTaken(int num);
    std::string getName() const;
    void setstacksize(int num);
    Card draw();
    std::string getStats() const;
    void updateCard(const Card &crd, int idx);
    int getWinNums() const;
    void incWinNums();
    double getWinRate() const;
    void setWinRate(int totalRounds);
    void setRegisteredToGame();
    bool getRegisteredToGame() const;
    
};
}
#endif
