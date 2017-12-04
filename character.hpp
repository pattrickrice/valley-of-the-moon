/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file of the character class
*********************************************************************/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <vector>
#include "space.hpp"
using std::vector;
using std::string;

class Character {
    enum Direction {
        left, up, right, down
    };
private:
    Direction direction;
    int XCoord;
    int YCoord;
    vector<string> keys;
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
    void setXCoord(int);
    void setYCoord(int);
};


#endif
