/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the empty space class
*********************************************************************/
#ifndef EMPTYSPACE_HPP
#define EMPTYSPACE_HPP

#include "space.hpp"

class EmptySpace : public Space {
private:
    int money;
public:
    EmptySpace();

    EmptySpace(char value,
               Space *top,
               Space *left,
               Space *right,
               Space *bottom);
};


#endif
