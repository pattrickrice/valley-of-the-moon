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
    Direction direction;
    int XCoord;
    int YCoord;
public:
    Character();

    Character(int startingX, int startingY);

    bool makeMove();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    int getXCoord();
    int getYCoord();
    int setXCoord(int);
    int setYCoord(int);
};


#endif
