#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace ariel;

int main() {
    // Create two players
    Player p1("May");
    Player p2("Lev");

    std::cout << "The players who are about to play: " << p1.getName() << ", " << p2.getName() << endl;

    Game game(p1, p2);
    for (int i = 0; i < 3; i++) {
        game.playTurn();
    }
    game.playAll();
    game.printLog();
    
    //Play another game after the game ended
    sleep(1);
    Game game2(p1, p2);
    game2.playAll();

    //shows that both statistics are different according to the turns in the game
    std::cout << "---------FIRST GAME STATS START---------" << endl;
    game.printStats();
    std::cout << "---------FIRST GAME STATS END---------" << endl;
    std::cout << "---------SECOND GAME STATS START---------" << endl;
    game2.printStats();
    std::cout << "---------SECOND GAME STATS END---------" << endl;

    std::cout << endl;

    std::cout << "First game winner:" << endl;
    game.printWiner();
    std::cout << "Second game winner:" << endl;
    game2.printWiner();
}