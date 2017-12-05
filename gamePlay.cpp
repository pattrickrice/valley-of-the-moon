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
using std::to_string;

/*********************************************************************
 * Default constructor
*********************************************************************/
GamePlay::GamePlay() {
    Player player(2, 2);
    this->player = player;
    this->width = 90;
    this->stepCounter = 0;
    this->stepsLeft = 1500;
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
    this->stepCounter = 0;
    this->stepsLeft = 1500;
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
    this->stepCounter = 0;
    this->stepsLeft = 1500;
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
    this->stepCounter = 0;
    this->stepsLeft = 1500;
}

/*********************************************************************
 * Contains the game play for th game. Continues until the player
 * chooses to exit the game.
*********************************************************************/
void GamePlay::play() {
    char move = ' ', doorID = ' ';
    bool passedThroughDoor = false;
    bool couldMove = false, wonGame = false;
    KeySpace *keySpace;
    DoorSpace *doorSpace;
    string newKey;

    // key input instructions
    int size = 6;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e', 'p'};
    string instructions = "a = left, s = down, d = right, w = up, p = print keys, e = exit";
    string keysList = "You have the following keys: ";

    // create all of the maps
    Map house("houseMap.txt", "houseKeys.txt", "houseDoorKeys.txt", HOUSE);
    Map valley("valley.txt", "valleyKeys.txt", "valleyDoorKeys.txt", VALLEY);
    Map forest("forest.txt", "forestKeys.txt", "forestDoorKeys.txt", FOREST);
    Map deepForrest("deepForest.txt", "deepForestKeys.txt", "deepForestDoorKeys.txt", DEEPFOREST);
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

    // initialize variables
    Map *map = &house;
    MapState mapState = HOUSE;

    // initialize character starting position
    Space *playerSpace = house.getSpace(player.getXCoord(), player.getYCoord());
    player.setXCoord(house.getPlayerStartingX());
    player.setYCoord(house.getPlayerStartingY());
    house.printMap(player.getXCoord(), player.getYCoord());

    // begin printing
    printStartingDialogue(map, player);
    system("clear");
    house.printMap(player.getXCoord(), player.getYCoord());



//    //DEBUG - use as shortcuts
//    player.pickUpKey("forestKey");
//    player.pickUpKey("houseKey");
//    player.pickUpKey("lakeKey");
//    player.pickUpKey("ranchKey");
//    player.pickUpKey("castleKey");

    this->width = map->getBoardSizeX() - 2;
    while (move != 'e' && mapState != END && stepsLeft != 0) {
        // takes a,s,d,w,e
        printInstructions(instructions, map->getBoardSizeX());
        move = getCharacterNoReturn(acceptable, size);
        stepsLeft--;
        couldMove = player.makeMove(move, playerSpace, width);

        system("clear");
        playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
        map->printMap(player.getXCoord(), player.getYCoord());

        // print space reaction
        if(!couldMove){
            // print space reaction
            player.failedMoveReact(move, playerSpace, width);

            // show keys
            if(move == 'p'){
                keysList = "You have the following keys: ";
                player.getKeys();
                if(player.getKeys().size() == 0){
                    keysList += "you have no keys!";
                }
                for (const auto &key : player.getKeys()) {
                    keysList += key + " ";
                }
                printMessage(keysList,width);
            }
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
                break;
            case EXIT:
                playerSpace->react(width);
                mapState = END;
                wonGame = true;
                break;
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
    if(wonGame) {
        printEndingDialogue(map, player);
    }

    // good bye screen
    system("clear");
    printBorder(width);
    printLeftAligned("Thank you for playing my project, this was made for Oregon State's CS 162 intro to computer science II", width);
    printLeftAligned("Credit: Patrick Rice", width);
    printCenterTitle("Goodbye", width);
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
    printLeftAligned("Steps left: " + to_string(stepsLeft), width);
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

/*********************************************************************
 * Constructor
 * @param width is the width of the console output
*********************************************************************/
void GamePlay::printEndingDialogue(Map* map, Player player){
    int width = map->getBoardSizeX() - 2;
    string dialogue;
    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "You found the antidote!";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "With the little energy you have left, you open the bottle and drink until it's dry.";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "...";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "You can feel your energy coming back!";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Never again will you make the mistake between Queen Anne's Lace and poison hemlock!";
    printDialogue(dialogue, width);

    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    dialogue = "Remember, hemlock's stems are red with the blood of Socrates.";
    printDialogue(dialogue, width);

}





