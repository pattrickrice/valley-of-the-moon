/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: Header file for the characterSpace class
*********************************************************************/

#ifndef CHARACTERSPACE_HPP
#define CHARACTERSPACE_HPP

#include "space.hpp"

class CharacterSpace : public Space {
public:
    CharacterSpace();

    CharacterSpace(char value,
                   Space *top,
                   Space *left,
                   Space *right,
                   Space *bottom,
                   MapState mapState);

    void react(int width) override;

    ~CharacterSpace() {}

};


#endif
