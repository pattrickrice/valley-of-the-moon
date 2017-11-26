/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file of the character class
*********************************************************************/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class Character {
    enum Direction {
        left, up, right, down
    };
private:
    int XCoord;
    int YCoord;
    Direction direction;

public:
    Character();

    Character::Character(int startingX, int startingY);

    bool makeMove();


};

#endif
