/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/29/2017
 * Description: Header file for the player class
*********************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

class Player : public Character {
private:
public:
    Player();

    Player(int XCoord, int YCoord);

    bool makeMove();


    //void getUserInput();

};


#endif
