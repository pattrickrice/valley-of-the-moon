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
using std::cin;

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

    // create all of the maps
    Map house("houseMap.txt", "houseKeys.txt", "houseDoorKeys.txt", HOUSE);
    Map valley("valley.txt", "valleyKeys.txt", "valleyDoorKeys.txt", VALLEY);
    Map forest("forest.txt", "forestKeys.txt", "forestDoorKeys.txt", FOREST);
    Map deepForrest("deepForest.txt", "deepForestKeys.txt", "deepForestDoorKeys.txt", FOREST);
    Map lake("lake.txt", "lakeKeys.txt", "lakeDoorKeys.txt", LAKE);
    Map ranch("ranch.txt", "ranchKeys.txt", "ranchDoorKeys.txt", RANCH);
    Map castle("castle.txt", "castleKeysKeys.txt", "castleDoorKeys.txt", CASTLE);

    vector<Map *> maps;
    maps.push_back(&house);
    maps.push_back(&valley);
    maps.push_back(&forest);
    maps.push_back(&deepForrest);
    maps.push_back(&lake);
    maps.push_back(&ranch);
    maps.push_back(&castle);

    // get the max width of the screen
    for (unsigned int i = 0; i < maps.size(); ++i) {
        if (maps.at(i)->getBoardSizeX() > width) {
            this->width = maps.at(i)->getBoardSizeX() - 2;
        }
    }


    // initialize character starting position
    Space *playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
    player.setXCoord(house.getPlayerStartingX());
    player.setYCoord(house.getPlayerStartingY());
    house.printMap(player.getXCoord(), player.getYCoord());

    // initialize variables
    Map *map = &house;

    printStartingDialogue(map, player);

    system("clear");
    house.printMap(player.getXCoord(), player.getYCoord());

    MapState mapState = HOUSE;
    char move = ' ', doorID = ' ';
    bool passedThroughDoor = false;
    bool couldMove = false;
    KeySpace *keySpace;
    DoorSpace *doorSpace;
    string newKey;

    // key input instructions
    int size = 5;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e'};
    string instructions = "a = left, s = down, d = right, w = up, e = exit";

    //DEBUG - use as shortcuts
//    player.pickUpKey("houseKey");
//    player.pickUpKey("lakeKey");
//    player.pickUpKey("ranchKey");
//    player.pickUpKey("castleKey");

    while (move != 'e' && mapState != END) {
        // takes a,s,d,w,e
        printInstructions(instructions, map->getBoardSizeX());
        move = getCharacterNoReturn(acceptable, size);
        couldMove = player.makeMove(move, playerSpace, width);

        system("clear");
        playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
        map->printMap(player.getXCoord(), player.getYCoord());

        // print space reaction
        if(!couldMove){
            player.failedMoveReact(move, playerSpace, width);
        }


        switch (playerSpace->getSpaceType()) {
            case KEY:
                keySpace = dynamic_cast<KeySpace *>(playerSpace);
                keySpace->react(width);
                // if the player hasn't grabbed the key already
                if (keySpace->isKeyPresent()) {
                    newKey = keySpace->takeKey();
                    player.pickUpKey(newKey);
                }
                break;
            case DOOR:
                doorSpace = dynamic_cast<DoorSpace *>(playerSpace);

                // check that player posesses key
                if (player.hasKey(doorSpace->getKey())) {
                    mapState = doorSpace->getMapState();
                    passedThroughDoor = true;
                    doorID = doorSpace->getDoorID();
                } else {
                    printMessage("You do not have the required key: "
                                 + doorSpace->getKey(), width);
                }
            default:
                break;
        }

        // move maps
        if (passedThroughDoor) {
            system("clear");
            map = getMap(maps, mapState);
            this->width = map->getBoardSizeX() - 2;

            // player just entered the map. Find their location
            player.setXCoord(map->getDoorXCoord(doorID));
            player.setYCoord(map->getDoorYCoord(doorID));

            playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
            map->printMap(player.getXCoord(), player.getYCoord());

            passedThroughDoor = false;
        }
    }
}

Map *GamePlay::getMap(vector<Map *> maps, MapState mapState) {
    for (unsigned int i = 0; i < maps.size(); ++i) {
        if (maps.at(i)->getMapID() == mapState) {
            return maps.at(i);
        }
    }
    cout << "[ERROR] in moveMaps in GamePlay.cpp" << endl;
    return maps.at(0);
}

void GamePlay::printInstructions(string instructions, int width) {
    width = width - 2;
    printBorder(width);
    printLeftAligned(instructions, width);
    printLeftAligned("Enter your move: ", width);
    printBorder(width);
}

void GamePlay::printDialogue(string dialogue, int width){
    dialogue += "\n [Press enter to continue]";
    printBorder(width);
    printLeftAligned(dialogue, width);
    printBorder(width);
    cin.ignore();
}

/*********************************************************************
 * Constructor
 * @param width is the width of the console output
*********************************************************************/
void GamePlay::printStartingDialogue(Map* map, Player player){
    int width = map->getBoardSizeX() - 2;
    string dialogue;
    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: I can't believe this is happening!";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: Of all the thoughtless things you could have done...";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: I told you to grab Queen Anne's Lace for some carrot tea, and you grabbed poison hemlock! It's just a matter of time before the poison's effects take hold on you...";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: There's only one place you can get an antidote, the castle at the southern end of the Valley of the Moon.";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: You're going to have find a key to get you access to it, and beware, every step you take is one step towards that poison taking your life";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Brother: Go now, find your way to the castle and save your self.";
    printDialogue(dialogue, width);

}





