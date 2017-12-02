/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Header file for the gameState class
*********************************************************************/
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "player.hpp"
#include "map.hpp"

class GameState {
private:
    int width;
    Player player;
    string startingMap;
//    Space *board;

public:
    GameState();
    GameState(int);
    GameState(int, string);
    GameState(int, string, Player);

    void play();

};

#endif
