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
    Space *boardHead;
    int boardSizeX;
    int boardSizeY;
    int playerStartingX;
    int playerStartingY;
    vector<string> keys;
    unsigned long keyCounter;

    bool importBoard(string filename, MapState mapState);

    bool importKeys(string filename);

public:
    Map();

    Map(string mapFileName, string keyFileName, MapState mapState);

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

    ~Map();
};


#endif
