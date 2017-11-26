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
Character::Character(){
    this->XCoord = -1;
    this->YCoord = -1;
}

/*********************************************************************
 * Constructor for character.
 * @param startingX is the starting x coordinate.
 * @param startingY is the starting y coordinate.
 ********************************************************************/
Character::Character(int startingX, int startingY){
    this->XCoord = startingX;
    this->YCoord = startingY;
}

/*********************************************************************
 * Moves the character in the forward direction depending on the direction
 * the ant is facing.
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