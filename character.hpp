/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file of the character class
*********************************************************************/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "space.hpp"

class Character {
    enum Direction {
        left, up, right, down
    };
private:
    Direction direction;
    int XCoord;
    int YCoord;
public:
    Character();

    Character(int startingX, int startingY);

    bool makeMove();

    virtual MapState moveLeft(Space *);

    virtual MapState moveRight(Space *);

    virtual MapState moveUp(Space *);

    virtual MapState moveDown(Space *);

    int getXCoord();
    int getYCoord();
    int setXCoord(int);
    int setYCoord(int);
};


#endif
