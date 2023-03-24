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

public:
    Log(Log* tail, Player ply1, Card crd1, Player ply2, Card crd2);
    ~Log();
    void setNext(Log* next);
    Log* getNext();
    void printLog();
    void addToLog(Player ply1, Card crd1, Player ply2, Card crd2);
    void CloseLog(std::string winnerName);

};
}
#endif
