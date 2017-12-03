/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/29/2017
 * Description: Header file for the player class
*********************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <set>
#include "character.hpp"
#include "space.hpp"
#include "map.hpp"
using std::set;

class Player : public Character {
private:
    set<string> keys;
public:
    Player();

    Player(int XCoord, int YCoord);

    MapState makeMove(char, Space *);

    MapState moveUp(Space *) override;

    MapState moveRight(Space *) override;

    MapState moveLeft(Space *) override;

    MapState moveDown(Space *) override;

    void pickUpKey(string);

    bool hasKey(string);

    set<string> getKeys();
};


#endif
