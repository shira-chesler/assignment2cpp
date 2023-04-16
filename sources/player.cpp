#include "player.hpp"
using namespace ariel;

/// @brief empty constructor
Player::Player(){
    this->name="Anonymous";
}

/// @brief constructor
/// @param name of player
Player::Player(std::string name){
    this->name=name;
}

/// @brief returns the number of cards at player's stack
/// @return number of cards at player's stack
int Player::stacksize(){
    return this->stack_size;
}

/// @brief returns number of cards player won
/// @return number of cards player won by now
int Player::cardesTaken(){
    return this->cards_won;
}

/// @brief updates the number of cards player won
/// @param num new num of cards player won
void Player::updateCardsTaken(int num){
    this->cards_won=num;
}

/// @brief returns name of player
/// @return name of player
std::string Player::getName() const{
    return this->name;
}

/// @brief 
/// @param num 
void Player::setstacksize(int num){
    this->stack_size=num;
}

/// @brief draws a card from player's deck
/// @return a card from top player card
Card Player::draw(){
    Card drawn = Card(this->cards.at(static_cast<std::array<Card,26>::size_type>(stack_size-1)));
    cards.at(static_cast<std::array<Card,26>::size_type>(stack_size-1)).setType(EMPTY);
    this->stack_size--;
    return drawn;
}

/// @brief returns stats of player
/// @return stats of player
std::string Player::getStats() const{
    return "\nName: "+this->name+"\nWin Rate: "+std::to_string(this->winRate)+
    "%\nNumber Of Cards Won: "+std::to_string(this->cards_won)+"\n";
}

/// @brief update a card in player deck
/// @param crd card to copy values from
/// @param idx to which card in player deck to apply the change
void Player::updateCard(const Card &crd, int idx){
    this->cards.at(static_cast<std::array<Card,26>::size_type>(idx)).setType(crd.getType());
    this->cards.at(static_cast<std::array<Card,26>::size_type>(idx)).setValue(crd.getValue());
}

/// @brief increment the number of wins to player
void Player::incWinNums(){
    this->winNums++;
}

/// @brief sets the win rate of player in current game
/// @param totalRounds total rounds played in game
void Player::setWinRate(int totalRounds){
    this->winRate = 100*(((double)this->winNums)/totalRounds);
}

/// @brief player is registered to a certain game
void Player::setRegisteredToGame(){
    this->registerdToGame=true;
}

/// @brief player is no longer registered to any game
void Player::setUnRegisteredToGame(){
    this->registerdToGame=false;
}

/// @brief returns if player registered to a game
/// @return if player registered to a game
bool Player::getRegisteredToGame() const{
    return this->registerdToGame;
}

/// @brief sets all stats of player back to 0
void Player::initialstats(){
    cards_won=0;
    stack_size=0;
    winNums=0;
    winRate=0;
}