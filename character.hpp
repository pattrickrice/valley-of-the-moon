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

    virtual bool moveLeft(Space *, int);

    virtual bool moveRight(Space *, int);

    virtual bool moveUp(Space *, int);

    virtual bool moveDown(Space *, int);

    int getXCoord();

    int getYCoord();

    void setXCoord(int);

    void setYCoord(int);
};


#endif
