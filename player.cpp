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
 * @param width is the width of the map
*********************************************************************/
bool Player::makeMove(char move, Space * playerSpace, int width){

    switch (move){
        //D-pad controller
        case 'a':
            return moveLeft(playerSpace, width);
        case 's':
            return moveDown(playerSpace, width);
        case 'd':
            return moveRight(playerSpace, width);
        case 'w':
            return moveUp(playerSpace, width);
        default:
            //TODO
            //invalid input;
            return false;
    }
};


/*********************************************************************
 * Takes the input of the player and prints the message of not moving
 * @param move is the move from the input
 * @param playerSpace is the space the player occupies
 * @param width is the width of the map
*********************************************************************/
void Player::failedMoveReact(char move, Space * playerSpace, int width){

    switch (move){
        //D-pad controller
        case 'a':
            moveLeftReaction(playerSpace, width);
            break;
        case 's':
            moveDownReaction(playerSpace, width);
            break;
        case 'd':
            moveRightReaction(playerSpace, width);
            break;
        case 'w':
            moveUpReaction(playerSpace, width);
            break;
        case 'e':
            printMessage("Exiting Game", width);
            break;
        default:
            printMessage("Error", width);
            //TODO
            //invalid input;
    }
};

/*********************************************************************
 * Moves character left
 ********************************************************************/
bool Player::moveLeft(Space *playerSpace, int width) {
    return Character::moveLeft(playerSpace, width);
}

/*********************************************************************
 * Moves character right
 ********************************************************************/
bool Player::moveRight(Space *playerSpace, int width) {
    return Character::moveRight(playerSpace, width);
}

/*********************************************************************
 * Moves character up
 ********************************************************************/
bool Player::moveUp(Space *playerSpace, int width) {
    // inverted
    return Character::moveUp(playerSpace, width);
}

/*********************************************************************
 * Moves character down
 ********************************************************************/
bool Player::moveDown(Space *playerSpace, int width) {
    // inverted
    return Character::moveDown(playerSpace, width);
}

/*********************************************************************
 * shows the reactions of a failed move up
 ********************************************************************/
void Player::moveUpReaction(Space *playerSpace, int width){
    if(playerSpace->getTop() != nullptr){
        playerSpace->getTop()->react(width);
    }
}

/*********************************************************************
 * shows the reactions of a failed move right
 ********************************************************************/
void Player::moveRightReaction(Space *playerSpace, int width){
    if(playerSpace->getRight() != nullptr){
        playerSpace->getRight()->react(width);
    }
}

/*********************************************************************
 * shows the reactions of a failed move left
 ********************************************************************/
void Player::moveLeftReaction(Space *playerSpace, int width){
    if(playerSpace->getLeft() != nullptr){
        playerSpace->getLeft()->react(width);
    }
}

/*********************************************************************
 * shows the reactions of a failed move down
 ********************************************************************/
void Player::moveDownReaction(Space *playerSpace, int width){
    if(playerSpace->getBottom() != nullptr){
        playerSpace->getBottom()->react(width);
    }
}

/*********************************************************************
 * Adds the key to the character's pocket
 * @param key is the key being added to the set.
 ********************************************************************/
void Player::pickUpKey(string key){
    keys.insert(key);
}

/*********************************************************************
 * Adds the key to the character's pocket
 * @param key is the key we are looking for
 * sources cited: https://stackoverflow.com/questions/6277646/in-c-check-if-stdvectorstring-contains-a-certain-value
 ********************************************************************/
bool Player::hasKey(string key){
    return keys.find(key) != keys.end();
}

/*********************************************************************
 * Returns the set of the player's keys.
 ********************************************************************/
set<string> Player::getKeys(){
    return keys;
}



