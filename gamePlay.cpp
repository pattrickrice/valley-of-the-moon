/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Implementation file for the gameState class
*********************************************************************/
#include <cstdlib>
#include "gamePlay.hpp"
#include "utilities.hpp"
#include "keySpace.hpp"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*********************************************************************
 * Default constructor
*********************************************************************/
GamePlay::GamePlay() {
    Player player(2, 2);
    this->player = player;
    this->width = 90;
    this->startingMap = "houseMap.txt";
    this->mapState = HOUSE;
}

/*********************************************************************
 * Constructor
 * @param width is the width of the console output
*********************************************************************/
GamePlay::GamePlay(int width) {
    Player player(0, 0);
    this->player = player;
    this->width = width;
    this->startingMap = "houseMap.txt";
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
*********************************************************************/
GamePlay::GamePlay(int width, string fileName, MapState mapState) {
    Player player(0, 0);
    this->player = player;
    this->width = width;
    this->startingMap = fileName;
    this->mapState = mapState;
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
 * @param player is the player object and can include starting
 * information such as its initial position.
*********************************************************************/
GamePlay::GamePlay(int width, string fileName, MapState mapState, Player player) {
    this->player = player;
    this->width = width;
    this->startingMap = fileName;
    this->mapState = mapState;
}

/*********************************************************************
 * Contains the game play for th game. Continues until the player
 * chooses to exit the game.
*********************************************************************/
void GamePlay::play() {
    Map house("houseMap.txt", "houseKeys.txt", HOUSE);
    MapState mapState = HOUSE;
    Space *playerSpace;
    player.setXCoord(house.getPlayerStartingX());
    player.setYCoord(house.getPlayerStartingY());
    char move = ' ';
    KeySpace *keySpace;
    string newKey;
    int size = 5;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e'};

    string instructions = "a = left, s = down, d = right, w = up, e = exit \n";
    instructions += "Enter move: ";


    while (move != 'e' && mapState != EXIT) {
        // takes a,s,d,w

        switch (mapState) {
            case HOUSE:
                playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
                house.printMap(player.getXCoord(), player.getYCoord());

                break;
            case VALLEY:
                break;
            case FOREST:
                break;
            case LAKE:
                break;
            case RANCH:
                break;
            case CASTLE:
                break;
            default:
                playerSpace = house.getSpace(1, 1);
                house.printMap(player.getXCoord(), player.getYCoord());
                cout << "[ERROR] in MapState in GamePlay.cpp" << endl;
        };

        if(playerSpace->getSpaceType() == KEY){
            keySpace = dynamic_cast<KeySpace *>(playerSpace);
            newKey = keySpace->takeKey();
            player.pickUpKey(newKey);
            cout << "You picked up the key: " + newKey + " !" << endl;
        }
        cout << instructions;
        move = getCharacterNoReturn(acceptable, size);
        player.makeMove(move, playerSpace);
        system("clear");
    }
}





