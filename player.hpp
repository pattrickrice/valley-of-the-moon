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

    bool makeMove(char, Space *, int);

    void failedMoveReact(char move, Space *playerSpace, int width);

    bool moveUp(Space *, int) override;

    bool moveRight(Space *, int) override;

    bool moveLeft(Space *, int) override;

    bool moveDown(Space *, int) override;

    void moveUpReaction(Space *, int);

    void moveRightReaction(Space *, int);

    void moveLeftReaction(Space *, int);

    void moveDownReaction(Space *, int);

    void pickUpKey(string);

    bool hasKey(string);

    set<string> getKeys();
};


#endif
