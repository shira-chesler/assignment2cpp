#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <iostream>
#include "card.hpp";

namespace ariel{
class Player
{
private:
    std::string name;
    int cards_won;
    int stack_size;
    Card cards[26];
    int winNums;
    double winRate;

public:
    Player(std::string name);
    ~Player();
    int stacksize();
    int cardesTaken();
    void updateCardsTaken(int num);
    std::string getName();
    void setstacksize(int num);
    Card draw();
    std::string getStats();
    void updateCards();
    int getWinNums();
    void setWinNums(int num);
    double getWinRate();
    void setWinRate(int num);
    
};
}
#endif
