/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the map class
*********************************************************************/
#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
using std::string;

class Map {
private:
    char **board;
    int boardSizeX;
    int boardSizeY;
    bool importBoard(string filename);

public:
    Map();
    Map(string filename);
    ~Map();
    char **getBoard();
    int getBoardSizeX();
    int getBoardSizeY();
    };


#endif
