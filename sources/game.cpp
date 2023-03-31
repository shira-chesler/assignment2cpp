#include <stdexcept>
#include "game.hpp"
using namespace ariel;

Game::Game(Player &ply1,Player &ply2):p1(ply1),p2(ply2), head(Log()), tail(head){
    if (ply1.getRegisteredToGame()||ply2.getRegisteredToGame())
    {
        throw std::invalid_argument("A player cannot be registered to 2 games");
    }
    this->createGame();
}

Game::~Game(){
    Log* cur= this->head.getNext();
    Log* tmp;
    while(cur){
        tmp=cur->getNext();
        delete cur;
        cur=tmp;
    }
}

Player* Game::getPlayer(int one_or_two) const{ //is it right to return pointer or reference
    if (one_or_two==1){
        return &(this->p1);
    }
    else if (one_or_two==2){
        return &(this->p2);
    }
    else{
        return NULL;
    }
}

void Game::setTail(Log* new_tail){
    this->tail.setNext(new_tail);
    this->tail=(*new_tail);
}

void Game::playTurn(){
    if(this->isGameOver){
        throw std::logic_error("Can't continue playing when game is over!");
    }
    Card crd1 = this->p1.draw();
    Card crd2 = this->p2.draw();
    this->NumCardsForEachPlayerOnDesk++;
    Log *new_tail = new Log(this->p1, crd1,this->p2,crd2);
    this->setTail(new_tail);
    int num_of_draws=0;
    while(crd1.getValue()==crd2.getValue()){
        num_of_draws++;
        if(this->p1.stacksize()<=1||this->p2.stacksize()<=1){
            if(num_of_draws==1){
                if(this->p1.stacksize()==1){
                    this->p1.draw();
                    this->p2.draw();
                    this->p1.updateCardsTaken(this->p1.cardesTaken()+this->NumCardsForEachPlayerOnDesk+1);
                    this->p2.updateCardsTaken(this->p2.cardesTaken()+this->NumCardsForEachPlayerOnDesk+1);
                }
                else{
                    this->p1.updateCardsTaken(this->p1.cardesTaken()+this->NumCardsForEachPlayerOnDesk);
                    this->p2.updateCardsTaken(this->p2.cardesTaken()+this->NumCardsForEachPlayerOnDesk);
                }
                this->incTotalRounds();
                this->NumCardsForEachPlayerOnDesk=0;
                this->tail.addTurnWinner("Turn ended in a draw.");
                break;
            }
            else{
                this->deck[P1_BOUNDARY+2*(num_of_draws-1)]=crd1;
                this->deck[P2_BOUNDARY+2*(num_of_draws-1)]=crd2;
                if(this->p1.stacksize()==1){
                    this->deck[P1_BOUNDARY+2*(num_of_draws-1)+1] = this->p1.draw();
                    this->deck[P2_BOUNDARY+2*(num_of_draws-1)+1] = this->p2.draw();
                }
                this->foldAndDeal(P1_BOUNDARY,P1_BOUNDARY+this->NumCardsForEachPlayerOnDesk,false);
                this->foldAndDeal(P2_BOUNDARY,P2_BOUNDARY+this->NumCardsForEachPlayerOnDesk,false);
                crd1 = this->p1.draw();
                crd2 = this->p2.draw();
                this->tail.addToLog(this->p1,crd1,this->p2,crd2);
                this->NumCardsForEachPlayerOnDesk=1;
            }
        }
        else
        {
        this->deck[P1_BOUNDARY+2*(num_of_draws-1)]=crd1;
        this->deck[P1_BOUNDARY+2*(num_of_draws-1)+1] = this->p1.draw();
        crd1 = this->p1.draw();
        this->deck[P2_BOUNDARY+2*(num_of_draws-1)]=crd2;
        this->deck[P2_BOUNDARY+2*(num_of_draws-1)+1] = this->p2.draw();
        crd2 = this->p2.draw();
        NumCardsForEachPlayerOnDesk+=2;
        this->tail.addToLog(this->p1,crd1,this->p2,crd2);
        }
    }
    if(num_of_draws>0){
        this->num_of_turns_had_tie++;
        this->incNumOfDrawsBy(num_of_draws);
        this->cleanDeck(P1_BOUNDARY,P1_BOUNDARY+this->NumCardsForEachPlayerOnDesk);
        this->cleanDeck(P2_BOUNDARY,P2_BOUNDARY+this->NumCardsForEachPlayerOnDesk);
    }
    if((!this->p1.stacksize()==0 && !this->p2.stacksize()==0)||this->NumCardsForEachPlayerOnDesk>0){
        if(crd1.getValue()>crd2.getValue()){
            this->closeTurn(this->p1);
        }
        else{
            this->closeTurn(this->p2);
        }
        this->NumCardsForEachPlayerOnDesk=0;
        this->incTotalRounds();
        this->p1.setWinRate(this->totalRounds);
        this->p2.setWinRate(this->totalRounds);
    }
    if(this->p1.stacksize()==0||this->p2.stacksize()==0){//supposed to happen together
        this->endGame();
    }
}

void Game::closeTurn(Player &plyr){
    plyr.updateCardsTaken(plyr.cardesTaken()+2*this->NumCardsForEachPlayerOnDesk);
    plyr.incWinNums();
    this->tail.addTurnWinner(plyr.getName()+" wins.");
}

void Game::endGame(){
    this->isGameOver=true;
    if(this->p1.cardesTaken()>this->p2.cardesTaken()){
    Log *new_tail = new Log("The winner is player p1 - "+this->p1.getName());
        this->setTail(new_tail);
    }
    else if(this->p1.cardesTaken()<this->p2.cardesTaken()){
        Log *new_tail = new Log("The winner is player p2 - "+this->p2.getName());
        this->setTail(new_tail);
    }
    else{
        Log *new_tail = new Log("There is no winner, the game ended with a tie");
        this->setTail(new_tail);
    }
}

void Game::playAll(){
    while (!this->isGameOver)
    {
        this->playTurn();
    }
    
}

void Game::printWiner(){
    if(!this->isGameOver){
        throw std::logic_error("Can't have winner when game isn't over yet");
    }
    else{
        this->tail.printLog();
    }
}

void Game::printLog(){
    Log cur = this->head;
    while(cur.getNext()){
        cur.printLog();
        cur=(*(cur.getNext()));
    }
    cur.printLog();
}

void Game::printStats(){
    std::cout<<"P1: "<<this->p1.getStats()<<std::endl;
    std::cout<<"P2: "<<this->p2.getStats()<<std::endl;
    std::cout<<"Total turns played in game: "<<this->totalRounds<<std::endl;
    std::cout<<"No' of draws in game: "<<this->DrawsNum<<std::endl;
    std::cout<<"Draw rate in game: "<<(this->num_of_turns_had_tie/this->totalRounds)*100<<"%"<<std::endl;
    std::cout<<"Game status:"<<std::endl;
    if(this->isGameOver){
        this->printWiner();
    }
    else{
        std::cout<<"The game is not over yet"<<std::endl;
    }
}

void Game::printLastTurn(){
    this->tail.printLog();
}

void Game::createGame(){
    this->createDeck();
    this->foldAndDeal(0,52,true);
}

void Game::createDeck(){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; i++)
        {
            int index = i*13+j;
            this->deck[index].setType(static_cast<type>(i+1));
            this->deck[index].setValue(j+1);
        }
        
    }
    
}

void Game::foldAndDeal(int low_boundary, int high_boundary, bool isContinious){
    int placement;
        for (int i = 0; i < 4; i++)
        {
            for(int j=low_boundary; j<high_boundary; j++){
                placement = std::rand()%(52);
                Card tmp(this->deck[j]);
                this->deck[j].copyFrom(deck[placement]);
                this->deck[placement].copyFrom(tmp);
            }
        }
    if(isContinious){
        for(int i=0; i<2; i++){
            for(int j=0; j<26; j++){
                placement=i*26+j;
                if (i==0)
                {
                    this->p1.updateCard(this->deck[placement],j);
                }
                else
                {
                    this->p2.updateCard(this->deck[placement],j);
                }
                
            }
        }
        this->p1.setstacksize(26);
        this->p2.setstacksize(26);
        
    }
    else{
        if(high_boundary<=26){
            for(int j=low_boundary; j<high_boundary; j++){
                this->p1.updateCard(this->deck[j],j);
            }
            this->p1.setstacksize(high_boundary-low_boundary);
        }
        else{
            for(int j=low_boundary; j<high_boundary; j++){
                this->p2.updateCard(this->deck[j],j-26);
            }
            this->p2.setstacksize(high_boundary-low_boundary);
        }
    }
    this->cleanDeck(low_boundary,high_boundary);
}

void Game::cleanDeck(int low_boundary, int high_boundary){
    for (int i = low_boundary; i < high_boundary; i++)
    {
        this->deck[i].setType(EMPTY);
    }
}

// int Game::getnumdraws(){
//     return 0;
// }

void Game::incNumOfDrawsBy(int n){
    this->DrawsNum+=n;
}

int Game::getTotalRounds() const{
    return this->totalRounds;
}

void Game::incTotalRounds(){
    this->totalRounds++;
}

// int Game::getNumCardsForEachPlayerOnDesk(){
//     return 0;
// }