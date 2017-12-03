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

public:
    GamePlay();

    GamePlay(int);

    GamePlay(int, string);

    GamePlay(int, string, Player);

    void play();

};

#endif
