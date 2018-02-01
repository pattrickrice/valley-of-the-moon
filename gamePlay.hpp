/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/1/2017
 * Description: Header file for the gameState class
*********************************************************************/
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "character/player.hpp"
#include "maps/map.hpp"

class GamePlay {
private:
    int width, stepCounter, stepsLeft;
    Player player;
    string startingMap;
    MapState mapState;

public:
    GamePlay();

    GamePlay(int);

    GamePlay(int, string, MapState);

    GamePlay(int, string, MapState, Player);

    Map *getMap(vector<Map *>, MapState);

    void play();

    void printInstructions(string, int width);

    void printDialogue(string dialogue, int width);

    void printStartingDialogue(Map *, Player player);

    void printEndingDialogue(Map *map, Player player);

    void advanceDialouge(string string,Map *map, Player player);

};

#endif
