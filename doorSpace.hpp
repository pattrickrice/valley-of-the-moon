/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Header file for the DoorSpace class
*********************************************************************/
#ifndef DOORSPACE_HPP
#define DOORSPACE_HPP

#include "space.hpp"

class DoorSpace : Space{
public:
    DoorSpace();
    DoorSpace::DoorSpace(char value,
                         Space *top,
                         Space *left,
                         Space *right,
                         Space *bottom);
};


#endif
