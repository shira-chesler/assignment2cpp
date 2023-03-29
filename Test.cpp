#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"


TEST_CASE("Player can only be registered to one game"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Player p3("Chen");
    ariel::Game game(p1, p2);
    CHECK_THROWS(ariel::Game(p1, p2));
    CHECK_THROWS(ariel::Game(p1, p3));
}

TEST_CASE("Player cannot play with himself"){
    ariel::Player p1("Moshe");
    CHECK_THROWS(ariel::Game(p1, p1));
}

TEST_CASE("Trying to play Turn after game is over"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1, p2);
    game.playAll();
    CHECK_THROWS(game.playTurn());
    CHECK_THROWS(game.playAll());
}

TEST_CASE("Stats of the game at different points"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1, p2);
    CHECK_NOTHROW(game.printStats());
    for(int i=0; i<5; i++){
        game.playTurn();
    }
    CHECK_NOTHROW(game.printStats());
    game.playAll();
    CHECK_NOTHROW(game.printStats());
}


TEST_CASE("Checking a deck of a Player before and after creating game"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    CHECK(p1.stacksize()==0);
    ariel::Game game(p1, p2);
    CHECK(p1.stacksize() == 26);
}

TEST_CASE("A player won after one round"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    CHECK((p1.cardesTaken()==0 && p2.cardesTaken()==0));
    game.playTurn();
    CHECK((p1.cardesTaken()>0 || p2.cardesTaken()>0));
}

TEST_CASE("Get winner before game is done"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    game.playTurn();
    game.playTurn();
    CHECK_THROWS(game.printWiner());
    game.playAll();
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("Log not throwing exception if trying to print before playing"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    CHECK_NOTHROW(game.printLog());
}

TEST_CASE("Checking that at end of game both players have same number of cards"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    game.playAll();
    CHECK(p1.stacksize()==p2.stacksize());//won't neesecary be 0
}

TEST_CASE("Checking no card disappered"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    game.playAll();
    CHECK_EQ(p1.cardesTaken()+p2.cardesTaken()+2*p1.stacksize(), 52); //even if ended in draw, num at bote players stacks should be equal
}

TEST_CASE("num of cards lowers after each turn"){
    ariel::Player p1("Moshe");
    ariel::Player p2("Haim");
    ariel::Game game(p1,p2);
    int j=26;
    for(int i=0; i<3; i++){
        game.playTurn();
        CHECK(p1.stacksize()<j);
        j=26-i;
    }
}
