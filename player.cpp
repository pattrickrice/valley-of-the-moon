/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/29/2017
 * Description: Implementation of the player class
*********************************************************************/

#include "player.hpp"

/*********************************************************************
 * Constructor
 * @param XCoord is the player's starting X position.
 * @param YCoord is the player's starting Y position.
*********************************************************************/
Player::Player(int XCoord, int YCoord) : Character(XCoord, YCoord){}

/*********************************************************************
 *
*********************************************************************/
bool Player::makeMove(char input){
    switch (input){
        //D-pad controller
        case 'a':
            moveLeft();
            break;
        case 's':
            moveDown();
            break;
        case 'd':
            moveRight();
            break;
        case 'w':
            moveUp();
            break;
        default:
            //TODO
            //invalid input;
            return false;
    }
    return true;
};
