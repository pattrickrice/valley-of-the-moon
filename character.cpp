/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Implementation of the character class
*********************************************************************/
#include "character.hpp"
#include <iostream>

using std::cout;

/*********************************************************************
 * Default constructor. Should not be called
 ********************************************************************/
Character::Character() {
    this->XCoord = -1;
    this->YCoord = -1;
}

/*********************************************************************
 * Constructor for character.
 * @param startingX is the starting x coordinate.
 * @param startingY is the starting y coordinate.
 ********************************************************************/
Character::Character(int startingX, int startingY) {
    this->XCoord = startingX;
    this->YCoord = startingY;
}

/*********************************************************************
 * Moves the character in the forward direction depending on the
 * direction they are facing.
 ********************************************************************/
bool Character::makeMove() {
    switch (direction) {
        // TODO: requires information about the space that the character is moving into

        case left:

            break;
        case right:

            break;
        case up:

            break;
        case down:

            break;
        default:
            //just in case
            cout << "ERROR: Could not read the ant's direction!";
    }
    return false;
};

/*********************************************************************
 * Moves character left
 ********************************************************************/
void Character::moveLeft() {
    XCoord--;
}

/*********************************************************************
 * Moves character right
 ********************************************************************/
void Character::moveRight() {
    XCoord++;
}

/*********************************************************************
 * Moves character up
 ********************************************************************/
void Character::moveUp() {
    // inverted
    YCoord--;
}

/*********************************************************************
 * Moves character down
 ********************************************************************/
void Character::moveDown() {
    // inverted
    YCoord++;
}

int Character::getXCoord(){
    return XCoord;
}
int Character::getYCoord(){
    return YCoord;
}
int Character::setXCoord(int XCoord){
    this->XCoord = XCoord;
}
int Character::setYCoord(int YCoord){
    this->YCoord = YCoord;
}