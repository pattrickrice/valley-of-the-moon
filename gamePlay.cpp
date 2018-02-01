/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Implementation file for the gameState class
*********************************************************************/
#include <cstdlib>
#include "gamePlay.hpp"
#include "utils/utilities.hpp"
#include "space/keySpace.hpp"
#include "space/doorSpace.hpp"

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
    this->stepsLeft = 1600;
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
    this->stepsLeft = 1600;
    this->startingMap = "houseMap.txt";
    this->mapState = HOUSE;
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
 * @param mapState is the starting map state
*********************************************************************/
GamePlay::GamePlay(int width, string fileName, MapState mapState) {
    Player player(0, 0);
    this->player = player;
    this->width = width;
    this->stepCounter = 0;
    this->stepsLeft = 1600;
    this->startingMap = fileName;
    this->mapState = mapState;
}

/*********************************************************************
 * Constructor for debugging specific maps
 * @param width is the width of the console output
 * @param fileName the of the map
 * @param player is the player object and can include starting
 * information such as its initial position.
 * @param mapState is the starting map state
 * @param player is the starting player
*********************************************************************/
GamePlay::GamePlay(int width, string fileName, MapState mapState, Player player) {
    this->player = player;
    this->width = width;
    this->startingMap = fileName;
    this->mapState = mapState;
    this->stepCounter = 0;
    this->stepsLeft = 1600;
}

/*********************************************************************
 * Contains the game play for th game. Continues until the player
 * chooses to exit the game.
*********************************************************************/
void GamePlay::play() {
    // declare variables
    char move = ' ', doorID = ' ';
    bool passedThroughDoor = false;
    bool couldMove = false, wonGame = false;
    KeySpace *keySpace;
    DoorSpace *doorSpace;
    string newKey;

    // key input instructions
    int size = 6;
    char acceptable[6] = {'a', 's', 'd', 'w', 'e', 'p'};
    string instructions = "a = left, s = down, d = right, w = up, p = print keys, e = exit";
    string keysList = "You have the following keys: ";

    // create all of the maps
    Map house("maps/houseMap.txt", "keys/houseKeys.txt", "doors/houseDoorKeys.txt", HOUSE);
    Map valley("maps/valley.txt", "keys/valleyKeys.txt", "doors/valleyDoorKeys.txt", VALLEY);
    Map forest("maps/forest.txt", "keys/forestKeys.txt", "doors/forestDoorKeys.txt", FOREST);
    Map deepForrest("maps/deepForest.txt", "keys/deepForestKeys.txt", "doors/deepForestDoorKeys.txt", DEEPFOREST);
    Map lake("maps/lake.txt", "keys/lakeKeys.txt", "doors/lakeDoorKeys.txt", LAKE);
    Map ranch("maps/ranch.txt", "keys/ranchKeys.txt", "doors/ranchDoorKeys.txt", RANCH);
    Map castle("maps/castle.txt", "keys/castleKeysKeys.txt", "doors/castleDoorKeys.txt", CASTLE);

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

    // width is the size of the board
    this->width = map->getBoardSizeX() - 2;
    while (move != 'e' && mapState != END && stepsLeft != 0) {
        // have the player make the move
        printInstructions(instructions, map->getBoardSizeX());
        move = getCharacterNoReturn(acceptable, size);
        stepsLeft--;
        couldMove = player.makeMove(move, playerSpace, width);

        // display the result
        system("clear");
        playerSpace = map->getSpace(player.getXCoord(), player.getYCoord());
        map->printMap(player.getXCoord(), player.getYCoord());

        // print space reaction if could not move
        if (!couldMove) {
            // print space reaction
            player.failedMoveReact(move, playerSpace, width);

            // show keys
            if (move == 'p') {
                keysList = "You have the following keys: ";
                player.getKeys();
                if (player.getKeys().size() == 0) {
                    keysList += "you have no keys!";
                }
                for (const auto &key : player.getKeys()) {
                    keysList += key + " ";
                }
                printMessage(keysList, width);
            }
        }

        // specific space functions
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
    if (wonGame) {
        printEndingDialogue(map, player);
    } else if (move == 'e') {
        printDialogue("Quiting game", width);
    } else {
        {}
        printDialogue("You have died from poisoning", width);
    }

    // ending screen
    system("clear");
    printBorder(width);
    printLeftAligned(
            "Thank you for playing my project, this was made for Oregon State's CS 162 intro to computer science II",
            width);
    printLeftAligned("Credit: Patrick Rice", width);
    printCenterTitle("Goodbye", width);
}

/*********************************************************************
 * Returns the new map
 * @param maps is the list of the maps for the game
 * @param mapState is the new mapstate the game is in
 ********************************************************************/
Map *GamePlay::getMap(vector<Map *> maps, MapState mapState) {
    for (unsigned int i = 0; i < maps.size(); ++i) {
        if (maps.at(i)->getMapID() == mapState) {
            return maps.at(i);
        }
    }
    cout << "[ERROR] in moveMaps in GamePlay.cpp" << endl;
    return maps.at(0);
}

/*********************************************************************
 * prints the instructions on how to move the character
 * @param instructions is a built string with some instructions in it
 * @param width is the size of the console
 ********************************************************************/
void GamePlay::printInstructions(string instructions, int width) {
    width = width - 2;
    printBorder(width);
    printLeftAligned(instructions, width);
    printLeftAligned("Steps left: " + to_string(stepsLeft), width);
    printLeftAligned("Enter your move: ", width);
    printBorder(width);
}

/*********************************************************************
 * prints the dialogue on the screen
 * @param dialogue is the dialogue to be printed
 * @param width is the size of the console
 ********************************************************************/
void GamePlay::printDialogue(string dialogue, int width) {
    dialogue += "\n [Press enter to continue]";
    printBorder(width);
    printLeftAligned(dialogue, width);
    printBorder(width);
    cin.ignore();
}

/*********************************************************************
 * Prints the starting dialogue
 * @param map is the map that is displayed with the dialogue
 * @param player is the player
*********************************************************************/
void GamePlay::printStartingDialogue(Map *map, Player player) {
    string speech[6] = {"Brother: I can't believe this is happening!",
                        "Brother: Of all the thoughtless things you could have done...",
                        "Brother: I told you to grab Queen Anne's Lace for some carrot tea, and you grabbed poison hemlock! It's just a matter of time before the poison's effects take hold on you...",
                        "Brother: There's only one place you can get an antidote, the castle at the southern end of the Valley of the Moon.",
                        "Brother: You're going to have find a key to get you access to it, and beware, every step you take is one step towards that poison taking your life",
                        "Brother: Go now, find your way to the castle and save your self."};

    for (int i = 0; i < 6; ++i) {
        advanceDialouge(speech[i], map, player);
    }
}

/*********************************************************************
 * prints the ending dialogue of the game
 * @param map is the map that is displayed with the dialogue
 * @param player is the player
*********************************************************************/
void GamePlay::printEndingDialogue(Map *map, Player player) {
    string speech[6] = {"You found the antidote!",
                        "With the little energy you have left, you open the bottle and drink until it's dry.",
                        "...",
                        "You can feel your energy coming back!",
                        "Never again will you make the mistake between Queen Anne's Lace and poison hemlock!",
                        "Remember, hemlock's stems are red with the blood of Socrates."};

    for (int i = 0; i < 6; ++i) {
        advanceDialouge(speech[i], map, player);
    }
}

/*********************************************************************
 * Advances the dialogue without changing anything else
 * @param dialogue is the dialogue being printed out
 * @param map is the map that is displayed with the dialogue
 * @param player is the player
*********************************************************************/
void GamePlay::advanceDialouge(string dialogue, Map *map, Player player) {
    int width = map->getBoardSizeX() - 2;
    system("clear");
    map->printMap(player.getXCoord(), player.getYCoord());
    printDialogue(dialogue, width);
}
