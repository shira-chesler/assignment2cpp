#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include "card.hpp"
#include "player.hpp"

namespace ariel{
class Log
{
private:
    Log* next;
    std::string the_log;
    const static std::array<std::string,13> cards;
    const static std::array<std::string,5> types;
    bool can_have_next=true;

    std::string isDraw(int a, int b);

public:
    Log();//new beggining game log
    Log(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2);//new mid game log
    Log(std::string end_of_game);//new end of game log
    ~Log();
    void setNext(Log* next);
    Log* getNext() const;
    void printLog() const;
    void addToLog(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2);
    void addTurnWinner(std::string turnwin);//end of cur_log
};
}
#endif
