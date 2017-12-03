/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Implementation of the character class
*********************************************************************/
#include "character.hpp"
#include <iostream>

using std::cout;
using std::endl;

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
            cout << "ERROR: Could not read the characters's direction!";
    }
    return false;
};

/*********************************************************************
 * Moves character left
 ********************************************************************/
bool Character::moveLeft(Space *characterSpace) {
    if (characterSpace->getLeft() != nullptr && characterSpace->getLeft()->isPermiable()) {
        XCoord--;
        return true;
    }
    return false;
}

/*********************************************************************
 * Moves character right
 ********************************************************************/
bool Character::moveRight(Space *characterSpace) {
    if (characterSpace->getRight() != nullptr && characterSpace->getRight()->isPermiable()) {
        XCoord++;
        return true;
    }
    return false;
}

/*********************************************************************
 * Moves character up
 ********************************************************************/
bool Character::moveUp(Space *characterSpace) {
    if (characterSpace->getTop() != nullptr && characterSpace->getTop()->isPermiable()) {
        //inverted
        YCoord--;
        return true;
    }
    return false;
}

/*********************************************************************
 * Moves character down
 ********************************************************************/
bool Character::moveDown(Space *characterSpace) {
    if (characterSpace->getBottom() != nullptr && characterSpace->getBottom()->isPermiable()) {
        YCoord++;
        return true;
    }
    return false;
}

/*********************************************************************
 * Returns the character's x-coordinate
 ********************************************************************/
int Character::getXCoord() {
    return XCoord;
}

/*********************************************************************
 * Returns the character's y-coordinate
 ********************************************************************/
int Character::getYCoord() {
    return YCoord;
}

/*********************************************************************
 * Sets the character's x-coordinate
 ********************************************************************/
int Character::setXCoord(int XCoord) {
    this->XCoord = XCoord;
}

/*********************************************************************
 * sets the character's y-coordinate
 ********************************************************************/
int Character::setYCoord(int YCoord) {
    this->YCoord = YCoord;
}