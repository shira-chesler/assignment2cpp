#include <ctime>
#include <stdexcept>
#include "game.hpp"
using namespace ariel;

/// @brief Constructor
/// @param ply1 player 1
/// @param ply2 player 2
Game::Game(Player &ply1,Player &ply2):p1(ply1),p2(ply2){
    this->ptail = &this->head;
    std::srand(std::time(0));
    if (this->p1.getRegisteredToGame()==false) this->p1.initialstats();
    if (this->p2.getRegisteredToGame()==false) this->p2.initialstats();
    this->createGame();
}

/// @brief Destructor - frees the log of game object
Game::~Game(){
    Log* cur= this->head.getNext();
    Log* tmp;
    while(cur){
        tmp=cur->getNext();
        delete cur;
        cur=tmp;
    }
}

/// @brief copy constructor
/// @param gme game to copy from
Game::Game(const Game &gme):p1(gme.p1), p2(gme.p2){
    this->isGameOver=gme.isGameOver;
    this->totalRounds=gme.totalRounds;
    this->DrawsNum=gme.DrawsNum;
    this->NumCardsForEachPlayerOnDesk=gme.NumCardsForEachPlayerOnDesk;
    this->num_of_turns_had_tie=gme.num_of_turns_had_tie;
    this->had_first_turn=gme.had_first_turn;
}

/// @brief function to get a player
/// @param one_or_two which one of the two players to return
/// @return pointer to player
Player* Game::getPlayer(int one_or_two) const{ 
    if (one_or_two==1){
        return &(this->p1);
    }
    else if (one_or_two==2){
        return &(this->p2);
    }
    else{
        std::invalid_argument("number of player to get can be only 1 or 2");
        return NULL;
    }
}

/// @brief adding pointer to last turn's log
/// @param new_tail last turn's log
void Game::setTail(Log* new_tail){
    this->ptail->setNext(new_tail);
    this->ptail=new_tail;
}

void Game::registerPlayers(){
    this->had_first_turn=true;
        if (this->p1.getRegisteredToGame())
        {
            throw std::invalid_argument("A player cannot be registered to 2 games");
        }
        this->p1.setRegisteredToGame();
        if(this->p2.getRegisteredToGame())
        {
            throw std::invalid_argument("A player cannot be registered to 2 games");
        }
        this->p2.setRegisteredToGame();
}

/// @brief order of playing a turn. deals with all the different variations of ties.
void Game::playTurn(){
    // in first turn of game, determines that the players registered to the game
    if(!had_first_turn){
        registerPlayers();
    }

    //can't play a turn after game is over
    if(this->isGameOver){
        throw std::logic_error("Can't continue playing when game is over!");
    }
    
    Card crd1 = this->p1.draw();
    Card crd2 = this->p2.draw();
    this->NumCardsForEachPlayerOnDesk++;
    Log *new_tail = new Log(this->p1, crd1,this->p2,crd2);//creates new log to the turn
    this->setTail(new_tail);
    int num_of_draws=0;

    //draw case
    while(crd1.getValue()==crd2.getValue()){
        num_of_draws++;

        //there isn't enough cards in order to play war
        if(this->p1.stacksize()<=1||this->p2.stacksize()<=1){
            if(num_of_draws==1){ //this was the first draw
                if(this->p1.stacksize()==1){
                    this->p1.draw();
                    this->p2.draw();
                    this->p1.updateCardsTaken(this->p1.cardesTaken()+this->NumCardsForEachPlayerOnDesk+1);
                    this->p2.updateCardsTaken(this->p2.cardesTaken()+this->NumCardsForEachPlayerOnDesk+1);
                }

                else{ //player have 0 cards at hand
                    this->p1.updateCardsTaken(this->p1.cardesTaken()+this->NumCardsForEachPlayerOnDesk);
                    this->p2.updateCardsTaken(this->p2.cardesTaken()+this->NumCardsForEachPlayerOnDesk);
                }

                this->incTotalRounds();
                this->NumCardsForEachPlayerOnDesk=0;
                this->ptail->addTurnWinner("Turn ended in a draw.");
                break;
            }
            
            else{ //There was wars in this turn. need to reshuffle and play again.
                this->deck.at(static_cast<std::array<Card,52>::size_type>(P1_BOUNDARY+2*(num_of_draws-1)))=crd1;
                this->deck.at(static_cast<std::array<Card,52>::size_type>(P2_BOUNDARY+2*(num_of_draws-1)))=crd2;
                if(this->p1.stacksize()==1){
                    this->deck.at(static_cast<std::array<Card,52>::size_type>(P1_BOUNDARY+2*(num_of_draws-1)+1)) = this->p1.draw();
                    this->deck.at(static_cast<std::array<Card,52>::size_type>(P2_BOUNDARY+2*(num_of_draws-1)+1)) = this->p2.draw();
                }
                this->foldAndDeal(P1_BOUNDARY,P1_BOUNDARY+this->NumCardsForEachPlayerOnDesk,false);
                this->foldAndDeal(P2_BOUNDARY,P2_BOUNDARY+this->NumCardsForEachPlayerOnDesk,false);
                crd1 = this->p1.draw();
                crd2 = this->p2.draw();
                this->ptail->addToLog(this->p1,crd1,this->p2,crd2);
                this->NumCardsForEachPlayerOnDesk=1;
            }
        }
        
        else
        {
        //assigns cards at main desk deck and plays war
        this->deck.at(static_cast<std::array<Card,52>::size_type>(P1_BOUNDARY+2*(num_of_draws-1)))=crd1;
        this->deck.at(static_cast<std::array<Card,52>::size_type>(P1_BOUNDARY+2*(num_of_draws-1)+1)) = this->p1.draw();
        crd1 = this->p1.draw();
        this->deck.at(static_cast<std::array<Card,52>::size_type>(P2_BOUNDARY+2*(num_of_draws-1)))=crd2;
        this->deck.at(static_cast<std::array<Card,52>::size_type>(P2_BOUNDARY+2*(num_of_draws-1)+1)) = this->p2.draw();
        crd2 = this->p2.draw();
        NumCardsForEachPlayerOnDesk+=2;
        this->ptail->addToLog(this->p1,crd1,this->p2,crd2);
        }
    }

    //cleans desk and adds ties stats
    if(num_of_draws>0){
        this->num_of_turns_had_tie++;
        this->incNumOfDrawsBy(num_of_draws);
        this->cleanDeck(P1_BOUNDARY,P1_BOUNDARY+this->NumCardsForEachPlayerOnDesk);
        this->cleanDeck(P2_BOUNDARY,P2_BOUNDARY+this->NumCardsForEachPlayerOnDesk);
    }
    
    //isn't end of game
    if((!(this->p1.stacksize()==0) && !(this->p2.stacksize()==0))||(this->NumCardsForEachPlayerOnDesk>0)){
        if((crd1.getValue()==1 && crd2.getValue()!=2) ||crd1.getValue()>crd2.getValue()){ // Ace loses only against 2
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
    
    //end of game
    if(this->p1.stacksize()==0||this->p2.stacksize()==0){//supposed to happen together
        this->endGame();
    }
}

/// @brief closes the current turn and sets turn player.
/// @param plyr player who won the current turn
void Game::closeTurn(Player &plyr){
    plyr.updateCardsTaken(plyr.cardesTaken()+2*this->NumCardsForEachPlayerOnDesk);
    plyr.incWinNums();
    this->ptail->addTurnWinner(plyr.getName()+" wins.");
}

/// @brief ends the game at final turn
void Game::endGame(){
    this->isGameOver=true;
    // p1 wins the game
    if(this->p1.cardesTaken()>this->p2.cardesTaken()){
    Log *new_tail = new Log("The winner is player p1 - "+this->p1.getName());
        this->setTail(new_tail);
    }
    //p2 wins the game
    else if(this->p1.cardesTaken()<this->p2.cardesTaken()){
        Log *new_tail = new Log("The winner is player p2 - "+this->p2.getName());
        this->setTail(new_tail);
    }
    //game ends in a tie
    else{
        Log *new_tail = new Log("There is no winner, the game ended with a tie");
        this->setTail(new_tail);
    }
    this->p1_final_stats = p1.getStats();
    this->p2_final_stats = p2.getStats();
    this->p1.setUnRegisteredToGame();
    this->p2.setUnRegisteredToGame();
}

/// @brief [lays all left turns 'till end
void Game::playAll(){
    if(this->isGameOver){
        throw std::logic_error("Can't continue playing when game is over!");
    }
    while (!this->isGameOver)
    {
        this->playTurn();
    }
    
}

/// @brief prints the game winner
void Game::printWiner(){
    if(!this->isGameOver){
        std::cout << "Game is not over yet, hence - there is no winner";
    }
    else{
        this->ptail->printLog();
    }
}

/// @brief prints the whole log since beginning of game
void Game::printLog(){
    Log cur = this->head;
    while(cur.getNext()){
        cur.printLog();
        cur=(*(cur.getNext()));
    }
    cur.printLog();
}

/// @brief prints the status of the game
void Game::printStats(){
    if (!this->isGameOver)
    {
        std::cout<<"P1: "<<this->p1.getStats()<<std::endl;
        std::cout<<"P2: "<<this->p2.getStats()<<std::endl;
    }
    else
    {
        std::cout<<"P1: "<<this->p1_final_stats<<std::endl;
        std::cout<<"P2: "<<this->p2_final_stats<<std::endl;
    }
    std::cout<<"Total turns played in game: "<<this->totalRounds<<std::endl;
    std::cout<<"No' of draws in game: "<<this->DrawsNum<<std::endl;
    double draw_rate = (((double)this->num_of_turns_had_tie)/this->totalRounds)*100;
    draw_rate==draw_rate? std::cout<<"Draw rate in game: "<<draw_rate<<"%"<<std::endl:
    std::cout<<"Draw rate in game: "<<0<<"%"<<std::endl;
    std::cout<<"Game status:"<<std::endl;
    if(this->isGameOver){
        this->printWiner();
    }
    else{
        std::cout<<"The game is not over yet"<<std::endl;
    }
}

/// @brief prints the log of the last turn
void Game::printLastTurn(){
    this->ptail->printLog();
}

/// @brief arranges the creation of a game
void Game::createGame(){
    this->createDeck();
    this->foldAndDeal(0,52,true);
}

/// @brief creates the full deck for the game
void Game::createDeck(){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            int index = i*13+j;
            this->deck.at(static_cast<std::array<Card,52>::size_type>(index)).setType(static_cast<type>(i+1));
            this->deck.at(static_cast<std::array<Card,52>::size_type>(index)).setValue(j+1);
        }
        
    }
    
}

/// @brief folds and deal cards between given placements in main desk to players
/// @param low_boundary where to start folding from
/// @param high_boundary 'till where to fold
/// @param isContinious does the main desk id full and needed to be dealing fully
void Game::foldAndDeal(int low_boundary, int high_boundary, bool isContinious){
    int placement;
        //fold cards randomly
        for (int i = 0; i < 4; i++)
        {
            for(int j=low_boundary; j<high_boundary; j++){ 
                placement = std::rand()%(52);
                Card tmp(this->deck.at(static_cast<std::array<Card,52>::size_type>(j)));
                this->deck.at(static_cast<std::array<Card,52>::size_type>(j)).copyFrom(deck.at(static_cast<std::array<Card,52>::size_type>(placement)));
                this->deck.at(static_cast<std::array<Card,52>::size_type>(placement)).copyFrom(tmp);
            }
        }
    if(isContinious){ //the deck is full and needs to be dealed to both p1 and p2
        for(int i=0; i<2; i++){
            for(int j=0; j<26; j++){
                placement=i*26+j;
                if (i==0)
                {
                    this->p1.updateCard(this->deck.at(static_cast<std::array<Card,52>::size_type>(placement)),j);
                }
                else
                {
                    this->p2.updateCard(this->deck.at(static_cast<std::array<Card,52>::size_type>(placement)),j);
                }
                
            }
        }
        this->p1.setstacksize(26);
        this->p2.setstacksize(26);  
    }

    else{
        if(high_boundary<=26){ //folds p1 cards
            for(int j=low_boundary; j<high_boundary; j++){
                this->p1.updateCard(this->deck.at(static_cast<std::array<Card,52>::size_type>(j)),j);
            }
            this->p1.setstacksize(high_boundary-low_boundary);
        }
        else{ //folds p2 cards
            for(int j=low_boundary; j<high_boundary; j++){
                this->p2.updateCard(this->deck.at(static_cast<std::array<Card,52>::size_type>(j)),j-26);
            }
            this->p2.setstacksize(high_boundary-low_boundary);
        }
    }
    this->cleanDeck(low_boundary,high_boundary); //cleans the main desk
}

/// @brief cleand main desk from low boundary to high boundary
/// @param low_boundary where to start cleaning from
/// @param high_boundary 'till where to clean
void Game::cleanDeck(int low_boundary, int high_boundary){
    for (int i = low_boundary; i < high_boundary; i++)
    {
        this->deck.at(static_cast<std::array<Card,52>::size_type>(i)).setType(EMPTY);
    }
}

/// @brief increment the num of draws in game by a given number
/// @param n number to increment number of draws in the game by
void Game::incNumOfDrawsBy(int n){
    this->DrawsNum+=n;
}

/// @brief get total rounds occured in game
/// @return number of total rounds occured in game
int Game::getTotalRounds() const{
    return this->totalRounds;
}

/// @brief increments the total rounds played at game
void Game::incTotalRounds(){
    this->totalRounds++;
}

/// @brief move constructor
/// @param gme game to move values from
Game::Game(Game&& gme) noexcept:p1(gme.p1), p2(gme.p2){
    this->isGameOver=gme.isGameOver;
    this->totalRounds=gme.totalRounds;
    this->DrawsNum=gme.DrawsNum;
    this->NumCardsForEachPlayerOnDesk=gme.NumCardsForEachPlayerOnDesk;
    this->num_of_turns_had_tie=gme.num_of_turns_had_tie;
    this->had_first_turn=gme.had_first_turn;

}

/// @brief copy assignment operator
/// @param gme game to assign values from
/// @return reference to current game
Game& Game::operator=(const Game& gme){
    this->~Game();
    this->p1=gme.p1;
    this->p2=gme.p2;
    this->isGameOver=gme.isGameOver;
    this->totalRounds=gme.totalRounds;
    this->DrawsNum=gme.DrawsNum;
    this->NumCardsForEachPlayerOnDesk=gme.NumCardsForEachPlayerOnDesk;
    this->num_of_turns_had_tie=gme.num_of_turns_had_tie;
    this->had_first_turn=gme.had_first_turn;
    return *this;
}

/// @brief move assignment operator 
/// @param gme game to assign values from
/// @return reference to current game
Game& Game::operator=(Game&& gme) noexcept{
    this->~Game();
    this->p1=gme.p1;
    this->p2=gme.p2;
    this->isGameOver=gme.isGameOver;
    this->totalRounds=gme.totalRounds;
    this->DrawsNum=gme.DrawsNum;
    this->NumCardsForEachPlayerOnDesk=gme.NumCardsForEachPlayerOnDesk;
    this->num_of_turns_had_tie=gme.num_of_turns_had_tie;
    this->had_first_turn=gme.had_first_turn;
    return *this;
}