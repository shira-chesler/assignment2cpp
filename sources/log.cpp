#include "log.hpp"
#include "player.hpp"
using namespace ariel;

const std::string Log::cards[] = {"Ace","2","3","4","5","6","7","8","9","10","Prince","Queen","King"};
const std::string Log::types[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

Log::Log(std::string log){

}
Log::~Log(){

}
void Log::addToLog(Log* tail, Player p1, Card c1, Player p2, Card c2){

}
void Log::CloseLog(std::string winnerName){

}
void Log::printLog(){

}
Log* Log::getNext(){
    return &(Log("---GAME STARTED---"));
}
void Log::printLog(){

}
