/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the map class
*********************************************************************/
#ifndef MAP_HPP
#define MAP_HPP

#include "space.hpp"
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Map {

private:
    struct Door {
        string key;
        MapState doorway;
        char doorID;
    };

    struct DoorLocation{
        char doorID;
        int XCoord;
        int YCoord;
    };

    Space *boardHead;
    int boardSizeX;
    int boardSizeY;
    int playerStartingX;
    int playerStartingY;
    vector<string> keys;
    vector<Door> doors;
    vector<DoorLocation> doorLocator;
    unsigned long keyCounter;
    unsigned long doorCounter;

    bool importBoard(string filename, MapState mapState);

    vector<string> importKeys(string filename);

    vector<Door> importDoors(string filename);


public:
    Map();

    Map(string mapFileName, string keyFileName, string doorFileName, MapState mapState);

    Space *getBoardHead();

    int getBoardSizeX();

    int getBoardSizeY();

    Space *setSpace(char,
                    Space *,
                    Space *,
                    Space *,
                    Space *,
                    MapState,
                    int currentX,
                    int currentY);

    void printMap(int XCoord, int YCoord);

    Space *getSpace(int, int);

    int getPlayerStartingX();

    int getPlayerStartingY();

    int getDoorXCoord(char inputDoorID);

    int getDoorYCoord(char inputDoorID);


    MapState getDoorMapState(char key);

    ~Map();
};


#endif
