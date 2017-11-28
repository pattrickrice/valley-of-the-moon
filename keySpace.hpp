/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Header file for the key space class
*********************************************************************/

#ifndef KEYSPACE_HPP
#define KEYSPACE_HPP

#include "space.hpp"

class KeySpace : public Space {
public:
    KeySpace();

    KeySpace(char value,
             Space *top,
             Space *left,
             Space *right,
             Space *bottom);
};


#endif
