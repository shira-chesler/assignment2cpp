#include "log.hpp"
#include "player.hpp"
using namespace ariel;

const std::array<std::string,13> Log::cards = {"Ace","2","3","4","5","6","7","8","9","10","Prince","Queen","King"};
const std::array<std::string,5> Log::types = {"EMPTY","Hearts", "Diamonds", "Clubs", "Spades"};

Log::Log(Log* tail, Player ply1, Card crd1, Player ply2, Card crd2){

}
Log::~Log(){

}
void Log::addToLog(Player ply1, Card crd1, Player ply2, Card crd2){

}
void Log::CloseLog(std::string winnerName){

}
void Log::printLog(){

}
Log* Log::getNext(){
    return this->next;
}
void Log::setNext(Log* next){

}
