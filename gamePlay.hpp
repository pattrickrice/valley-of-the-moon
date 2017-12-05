/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Header file for the gameState class
*********************************************************************/
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "player.hpp"
#include "map.hpp"

class GamePlay {
private:
    int width;
    Player player;
    string startingMap;
    MapState mapState;

public:
    GamePlay();

    GamePlay(int);

    GamePlay(int, string, MapState);

    GamePlay(int, string, MapState, Player);

    Map* getMap(vector<Map*>, MapState);

    void play();

    void printInstructions(string, int width);

};

#endif
