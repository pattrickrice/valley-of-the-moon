/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the space class
*********************************************************************/

#ifndef WALLSPACE_HPP
#define WALLSPACE_HPP

#include "space.hpp"

class WallSpace : public Space {
public:
    WallSpace();

    WallSpace(char value,
              Space *top,
              Space *left,
              Space *right,
              Space *bottom);
};


#endif
