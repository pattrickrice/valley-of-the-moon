/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Implementation file for the gameState class
*********************************************************************/
#include <cstdlib>
#include "gamePlay.hpp"
#include "utilities.hpp"
#include "keySpace.hpp"
#include "doorSpace.hpp"
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
    Map map();
    Map house("houseMap.txt", "houseKeys.txt", "houseDoorKeys.txt", HOUSE);
    Map valley("valley.txt", "valleyKeys.txt", "valleyDoorKeys.txt", VALLEY);
    Map forest("forest.txt", "forestKeys.txt", "forestDoorKeys.txt", FOREST);
    Map deepForrest("deepForest.txt", "deepForestKeys.txt", "deepForestDoorKeys.txt", FOREST);
    MapState mapState = HOUSE;
    Space *playerSpace;
    player.setXCoord(house.getPlayerStartingX());
    player.setYCoord(house.getPlayerStartingY());
    char move = ' ', doorID = ' ';
    bool passedThroughDoor = false;
    KeySpace *keySpace;
    DoorSpace *doorSpace;
    string newKey;
    int size = 5;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e'};

    string instructions = "a = left, s = down, d = right, w = up, e = exit \n";
    instructions += "Enter move: ";

    playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
    house.printMap(player.getXCoord(), player.getYCoord());
    while (move != 'e' && mapState != EXIT) {
        // takes a,s,d,w
        cout << instructions;
        move = getCharacterNoReturn(acceptable, size);
        player.makeMove(move, playerSpace);
        system("clear");

        switch (mapState) {
            case HOUSE:
                playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
                house.printMap(player.getXCoord(), player.getYCoord());
                break;
            case VALLEY:

                playerSpace = valley.getSpace(player.getXCoord(), player.getYCoord());
                valley.printMap(player.getXCoord(), player.getYCoord());
                break;
            case FOREST:
                playerSpace = forest.getSpace(player.getXCoord(), player.getYCoord());
                forest.printMap(player.getXCoord(), player.getYCoord());
                break;
            case DEEPFOREST:
                playerSpace = deepForrest.getSpace(player.getXCoord(), player.getYCoord());
                deepForrest.printMap(player.getXCoord(), player.getYCoord());
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

        switch (playerSpace->getSpaceType()) {
            case KEY:
                keySpace = dynamic_cast<KeySpace *>(playerSpace);
                newKey = keySpace->takeKey();
                player.pickUpKey(newKey);
                cout << "You picked up the key: " + newKey + " !" << endl;
                break;
            case DOOR:
                doorSpace = dynamic_cast<DoorSpace *>(playerSpace);
                if (player.hasKey(doorSpace->getKey())) {
                    mapState = doorSpace->getMapState();
                    passedThroughDoor = true;
                    doorID = doorSpace->getDoorID();
                } else {
                    cout << "You do not have the required key: "
                         << doorSpace->getKey() << endl;
                }
            default:
                break;
        }

        // move maps
        if (passedThroughDoor) {
            system("clear");
            switch (mapState) {
                case HOUSE:
                    // player just entered the map. Find their location
                    player.setXCoord(house.getDoorXCoord(doorID));
                    player.setYCoord(house.getDoorYCoord(doorID));

                    playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
                    house.printMap(player.getXCoord(), player.getYCoord());
                    break;
                case VALLEY:
                    // player just entered the map. Find their location
                    player.setXCoord(valley.getDoorXCoord(doorID));
                    player.setYCoord(valley.getDoorYCoord(doorID));


                    playerSpace = valley.getSpace(player.getXCoord(), player.getYCoord());
                    valley.printMap(player.getXCoord(), player.getYCoord());
                    break;
                case FOREST:
                    // player just entered the map. Find their location
                    player.setXCoord(forest.getDoorXCoord(doorID));
                    player.setYCoord(forest.getDoorYCoord(doorID));


                    playerSpace = forest.getSpace(player.getXCoord(), player.getYCoord());
                    forest.printMap(player.getXCoord(), player.getYCoord());
                    break;
                case DEEPFOREST:
                    // player just entered the map. Find their location
                    player.setXCoord(deepForrest.getDoorXCoord(doorID));
                    player.setYCoord(deepForrest.getDoorYCoord(doorID));


                    playerSpace = deepForrest.getSpace(player.getXCoord(), player.getYCoord());
                    deepForrest.printMap(player.getXCoord(), player.getYCoord());
                    break;
                case LAKE:
                    break;
                case RANCH:
                    break;
                case CASTLE:
                    break;
                default:
                    cout << "[ERROR] in moveMaps in GamePlay.cpp" << endl;
            };
            passedThroughDoor = false;
        }
    }
}






