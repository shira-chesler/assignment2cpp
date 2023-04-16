#include <stdexcept>
#include "log.hpp"
#include "player.hpp"
using namespace ariel;

const std::array<std::string,13> Log::cards = {"Ace","2","3","4","5","6","7","8","9","10","Prince","Queen","King"};
const std::array<std::string,5> Log::types = {"EMPTY","Hearts", "Diamonds", "Clubs", "Spades"};

/// @brief construcor to first log
Log::Log(){
    this->the_log="------THE GAME STARTED------";
    this->next=NULL;
}

/// @brief creates a new game log
/// @param ply1 first player
/// @param crd1 card that first player drew
/// @param ply2 second player
/// @param crd2 card that second player drew
Log::Log(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2){
    if(crd1.getType()== EMPTY || crd2.getType()==EMPTY){
        std::cerr<<"card type is empty! error!!!"<<std::endl;
    }
    this->the_log=ply1.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd1.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd1.getType()))
    +" "+ ply2.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd2.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd2.getType()))+"."+isDraw(crd1.getValue(),crd2.getValue());
    this->next=NULL;
}

/// @brief adds the string that closes this game's log
/// @param end_of_game the end of game string (winner).
Log::Log(std::string end_of_game){
    this->the_log=end_of_game;
    this->can_have_next=false;
    this->next=NULL;
}

/// @brief adds turn details to an existing current log
/// @param ply1 first player
/// @param crd1 card that first player drew
/// @param ply2 second player
/// @param crd2 card that second player drew
void Log::addToLog(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2){
    this->the_log=this->the_log+" "+ply1.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd1.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd1.getType()))
    + " "+ply2.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd2.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd2.getType()))+"."+isDraw(crd1.getValue(),crd2.getValue());
}

/// @brief prints the current log details
void Log::printLog() const{
    std::cout<<this->the_log<<std::endl;
}

/// @brief gets next log in list
/// @return the next log in list
Log* Log::getNext() const{
    return this->next;
}

/// @brief checks if 2 numbers given are equal
/// @param first number
/// @param second number
/// @return if 2 numbers given are equal
std::string Log::isDraw(int first, int second){
    if(first==second){
        return " Draw.";
    }
    else{
        return "";
    }
}

/// @brief sets next log in list
/// @param next log to be next in list
void Log::setNext(Log* next){
    if(!can_have_next){
        throw std::logic_error("Can't add log after game is over");
    }
    this->next=next;
}

/// @brief adds the winner of current turn's log
/// @param turnwin the string of game winner
void Log::addTurnWinner(std::string turnwin){
    this->the_log=this->the_log+" "+turnwin;
}
