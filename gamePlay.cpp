/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Implementation file for the gameState class
*********************************************************************/
#include <cstdlib>
#include "gamePlay.hpp"
#include "utilities.hpp"
using std::cout;
using std::endl;

/*********************************************************************
 * Default constructor
*********************************************************************/
GamePlay::GamePlay() {
    Player player(2, 2);
    this->player = player;
    this->width = 90;
    this->startingMap = "houseMap.txt";
}

/*********************************************************************
 * Constructor
 * @param width is the width of the console output
*********************************************************************/
GamePlay::GamePlay(int width) {
    Player player(0, 0);
    Map map("houseMap.txt");
    this->player = player;
    this->width = width;
    this->startingMap = "houseMap.txt";
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
*********************************************************************/
GamePlay::GamePlay(int width, string fileName){
    Player player(0, 0);
    this->player = player;
    this->width = width;
    this->startingMap = fileName;
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
 * @param player is the player object and can include starting
 * information such as its initial position.
*********************************************************************/
GamePlay::GamePlay(int width, string fileName, Player player){
    Map map(fileName);
    this->player = player;
    this->width = width;
    this->startingMap = fileName;
}

/*********************************************************************
 * Contains the game play for th game. Continues until the player
 * chooses to exit the game.
*********************************************************************/
void GamePlay::play(){
    Map map(this->startingMap);
    bool moved = true;
    char move = ' ';
    Space * playerSpace;
    map.printMap(player.getXCoord(), player.getYCoord());


    int size = 5;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e'};
//    cout << "The player's space contains: " << playerSpace->getValue() << endl;


    while (move != 'e') {
        // takes a,s,d,w
        playerSpace = map.getSpace(player.getXCoord(), player.getYCoord());

        cout << "a = left, s = down, d = right, w = up, e = exit" << endl;
        cout << "Enter move: ";

        move = getCharacterNoReturn(acceptable, size);
        player.makeMove(move, playerSpace);
        system("clear");
        map.printMap(player.getXCoord(), player.getYCoord());
    }
}



