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
 *
*********************************************************************/
bool Player::makeMove(){
    int size = 5;
    char acceptable[size] = {'a', 's', 'd', 'w', 'e'};
    cout << "a = left, s = down, d = right, w = up" << endl;
    cout << "Enter move: ";
    char move = getCharacterNoReturn(acceptable, size);

    switch (move){
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
