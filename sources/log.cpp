#include <stdexcept>
#include "log.hpp"
#include "player.hpp"
using namespace ariel;

const std::array<std::string,13> Log::cards = {"Ace","2","3","4","5","6","7","8","9","10","Prince","Queen","King"};
const std::array<std::string,5> Log::types = {"EMPTY","Hearts", "Diamonds", "Clubs", "Spades"};

Log::Log(){
    this->the_log="------THE GAME STARTED------";
    this->next=NULL;
}

Log::Log(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2){
    if(crd1.getType()== EMPTY || crd2.getType()==EMPTY){
        std::cerr<<"card type is empty! error!!!"<<std::endl;
    }
    this->the_log=ply1.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd1.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd1.getType()))
    +" "+ ply2.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd2.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd2.getType()))+"."+isDraw(crd1.getValue(),crd2.getValue());
    this->next=NULL;
}

Log::Log(std::string end_of_game){
    this->the_log=end_of_game;
    this->can_have_next=false;
    this->next=NULL;
}


void Log::addToLog(const Player &ply1, const Card &crd1, const Player &ply2, const Card &crd2){
    this->the_log=this->the_log+" "+ply1.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd1.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd1.getType()))
    + " "+ply2.getName()+" played "+cards.at(static_cast<std::array<Card,13>::size_type>(crd2.getValue()-1))+" of "+types.at(static_cast<std::array<Card,5>::size_type>(crd2.getType()))+"."+isDraw(crd1.getValue(),crd2.getValue());
}

void Log::printLog() const{
    std::cout<<this->the_log<<std::endl;
}

Log* Log::getNext() const{
    return this->next;
}

std::string Log::isDraw(int first, int second){
    if(first==second){
        return " Draw.";
    }
    else{
        return "";
    }
}

void Log::setNext(Log* next){
    if(!can_have_next){
        throw std::logic_error("Can't add log after game is over");
    }
    this->next=next;
}

void Log::addTurnWinner(std::string turnwin){
    this->the_log=this->the_log+" "+turnwin;
}
