#ifndef _LOG_HPP
#define _LOG_HPP

#include <string>
#include "card.hpp"

namespace ariel{
class Log
{
private:
    Log* next;
    std::string the_log;
    const std::string static cards[];
    const std::string static types[];

public:
    Log(std::string log);
    ~Log();
    void setNext(Log* next);
    Log* getNext();
    void printLog();
    void addToLog(Log* tail, Player p1, Card c1, Player p2, Card c2);
    void CloseLog(std::string winnerName);

};
}
#endif
