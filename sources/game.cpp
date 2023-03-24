#include "game.hpp"
using namespace ariel;

Game::Game(Player &ply1,Player &ply2):p1(ply1),p2(ply2){
    
}
Game::~Game(){

}
Player* Game::getPlayer(int one_or_two){
    return NULL;
}
void Game::setTail(Log* new_tail){

}
void Game::playTurn(){
    

}
void Game::playAll(){
    
}
void Game::printWiner(){

}
void Game::printLog(){

}
void Game::printStats(){

}
void Game::printLastTurn(){

}
void Game::createGame(){

}
void Game::createDeck(){

}
void Game::foldAndDeal(int low_boundary, int high_boundary, bool isContinious){

}
void Game::cleanDeck(int low_boundary, int high_boundary){

}
// int Game::getnumdraws(){
//     return 0;
// }
void Game::incNumOfDraws(){

}
int Game::getTotalRounds(){
    return 0;
}
void Game::incTotalRounds(){

}
// int Game::getNumCardsForEachPlayerOnDesk(){
//     return 0;
// }