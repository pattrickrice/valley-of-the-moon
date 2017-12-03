/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the map class
*********************************************************************/
#ifndef MAP_HPP
#define MAP_HPP

#include "space.hpp"
#include <iostream>

using std::string;

class Map {
private:
    Space *boardHead;
    int boardSizeX;
    int boardSizeY;

    bool importBoard(string filename, MapState mapState);

public:
    Map();

    Map(string filename, MapState mapState);

    Space *getBoardHead();

    int getBoardSizeX();

    int getBoardSizeY();

    Space *setSpace(char,
                    Space *,
                    Space *,
                    Space *,
                    Space *,
                    MapState);

    void printMap(int XCoord, int YCoord);

    Space *getSpace(int, int);

    ~Map();
};


#endif
