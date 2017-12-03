/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/29/2017
 * Description: Implementation of the player class
*********************************************************************/

#include "player.hpp"
#include <iostream>
#include "utilities.hpp"
using std::cout;
using std::endl;
using std::cin;

Player::Player() : Character(0, 0){}

/*********************************************************************
 * Constructor
 * @param XCoord is the player's starting X position.
 * @param YCoord is the player's starting Y position.
*********************************************************************/
Player::Player(int XCoord, int YCoord) : Character(XCoord, YCoord){}

/*********************************************************************
 * Takes the input of the player and moves the player.
 * @param move is the move from the input
 * @param playerSpace is the space the player occupies
*********************************************************************/
MapState Player::makeMove(char move, Space * playerSpace){

    switch (move){
        //D-pad controller
        case 'a':
            moveLeft(playerSpace);
            break;
        case 's':
            moveDown(playerSpace);
            break;
        case 'd':
            moveRight(playerSpace);
            break;
        case 'w':
            moveUp(playerSpace);
            break;
        default:
            //TODO
            //invalid input;
            return HOUSE;
    }
    return HOUSE;
};

/*********************************************************************
 * Moves character left
 ********************************************************************/
MapState Player::moveLeft(Space *playerSpace) {
    return Character::moveLeft(playerSpace);
}

/*********************************************************************
 * Moves character right
 ********************************************************************/
MapState Player::moveRight(Space *playerSpace) {
    return Character::moveRight(playerSpace);
}

/*********************************************************************
 * Moves character up
 ********************************************************************/
MapState Player::moveUp(Space *playerSpace) {
    // inverted
    return Character::moveUp(playerSpace);
}

/*********************************************************************
 * Moves character down
 ********************************************************************/
MapState Player::moveDown(Space *playerSpace) {
    // inverted
    return Character::moveDown(playerSpace);
}


