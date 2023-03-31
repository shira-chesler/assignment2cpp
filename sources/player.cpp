#include "player.hpp"
using namespace ariel;
Player::Player(){
    this->name="Anonymous";
}

Player::Player(std::string name){
    this->name=name;
}

Player::~Player(){

}

int Player::stacksize(){
    return this->stack_size;
}

int Player::cardesTaken(){
    return this->cards_won;
}

void Player::updateCardsTaken(int num){
    this->cards_won=num;
}

std::string Player::getName() const{
    return this->name;
}

void Player::setstacksize(int num){
    this->stack_size=num;
}

Card Player::draw(){
    Card drawn = Card(this->cards.at(static_cast<std::array<Card,26>::size_type>(stack_size-1)));
    cards.at(static_cast<std::array<Card,26>::size_type>(stack_size-1)).setType(EMPTY);
    this->stack_size--;
    return drawn;
}

std::string Player::getStats() const{
    return "\nName: "+this->name+"\nWin Rate: "+std::to_string(this->winRate)+
    "%\nNumber Of Cards Won: "+std::to_string(this->cards_won)+"\n";
}

void Player::updateCard(const Card &crd, int idx){
    this->cards.at(static_cast<std::array<Card,26>::size_type>(idx)).setType(crd.getType());
    this->cards.at(static_cast<std::array<Card,26>::size_type>(idx)).setValue(crd.getValue());
}

// int Player::getWinNums(){
//     return 0;
// }

void Player::incWinNums(){
    this->winNums++;
}

// double Player::getWinRate(){
//     return 0;
// }

void Player::setWinRate(int totalRounds){
    this->winRate = 100*(((double)this->winNums)/totalRounds);
}

void Player::setRegisteredToGame(){
    this->registerdToGame=true;
}

bool Player::getRegisteredToGame() const{
    return this->registerdToGame;
}