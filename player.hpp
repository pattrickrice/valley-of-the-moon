/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/29/2017
 * Description: Header file for the player class
*********************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"
#include "space.hpp"
#include "map.hpp"

class Player : public Character {
private:
public:
    Player();

    Player(int XCoord, int YCoord);

    MapState makeMove(char, Space *);

    MapState moveUp(Space *);

    MapState moveRight(Space *);

    MapState moveLeft(Space *);

    MapState moveDown(Space *);
};


#endif
