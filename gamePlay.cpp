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
    Map house("houseMap.txt", "houseKeys.txt", "houseDoorKeys.txt", HOUSE);
    Map valley("valley.txt", "valleyKeys.txt", "valleyDoorKeys.txt", VALLEY);
    Map forest("forest.txt", "forestKeys.txt", "forestDoorKeys.txt", FOREST);
    Map deepForrest("deepForest.txt", "deepForestKeys.txt", "deepForestDoorKeys.txt", FOREST);
    Map lake("lake.txt", "lakeKeys.txt", "lakeDoorKeys.txt", LAKE);
    Map ranch("ranch.txt", "ranchKeys.txt", "ranchDoorKeys.txt", RANCH);
    Map castle("castle.txt", "castleKeysKeys.txt", "castleDoorKeys.txt", CASTLE);

    Map *map = &house;
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

    //DEBUG
    player.pickUpKey("houseKey");
    player.pickUpKey("lakeKey");
    player.pickUpKey("ranchKey");
    player.pickUpKey("castleKey");

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
                map = &house;
                break;
            case VALLEY:
                map = &valley;
                break;
            case FOREST:
                map = &forest;
                break;
            case DEEPFOREST:
                map = &deepForrest;
                break;
            case LAKE:
                map = &lake;
                break;
            case RANCH:
                map = &ranch;
                break;
            case CASTLE:
                map = &castle;
                break;
            default:
                map = &house;
                cout << "[ERROR] in MapState in GamePlay.cpp" << endl;
        };

        playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
        map->printMap(player.getXCoord(), player.getYCoord());

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
                    map = &house;
                    break;
                case VALLEY:
                    map = &valley;
                    break;
                case FOREST:
                    map = &forest;
                    break;
                case DEEPFOREST:
                    map = &deepForrest;
                    break;
                case LAKE:
                    map = &lake;
                    break;
                case RANCH:
                map = &ranch;
                    break;
                case CASTLE:
                map = &castle;
                    break;
                default:
                    cout << "[ERROR] in moveMaps in GamePlay.cpp" << endl;
            };

            // player just entered the map. Find their location
            player.setXCoord(map->getDoorXCoord(doorID));
            player.setYCoord(map->getDoorYCoord(doorID));

            playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
            map->printMap(player.getXCoord(), player.getYCoord());

            passedThroughDoor = false;
        }
    }
}






