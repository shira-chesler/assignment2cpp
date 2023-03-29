#include "player.hpp"
using namespace ariel;
Player::Player(){
    
}

Player::Player(std::string name){
    
}
Player::Player(Player &plr){
    
}
Player::~Player(){

}
int Player::stacksize(){
    return 0;
}
int Player::cardesTaken(){
    return 0;
}
void Player::updateCardsTaken(int num){
    
}

std::string Player::getName(){
    return NULL;
}

void Player::setstacksize(int num){
    
}

Card Player::draw(){
    return Card();
}
std::string Player::getStats(){
    return "No current stats";
}
void Player::updateCard(Card crd, int idx){
    
}
// int Player::getWinNums(){
//     return 0;
// }
void Player::incWinNums(){

}
// double Player::getWinRate(){
//     return 0;
// }
void Player::setWinRate(int totalRounds){

}
void setRegisteredToGame(){

}
bool getRegisteredToGame(){
    return false;
}