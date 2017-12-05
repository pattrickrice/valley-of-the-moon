/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: Header file for the ExitSpace class
*********************************************************************/

#ifndef EXITSPACE_HPP
#define EXITSPACE_HPP

#include "space.hpp"

class ExitSpace : public Space {
public:
    ExitSpace();

    ExitSpace(char value,
              Space *top,
              Space *left,
              Space *right,
              Space *bottom,
              MapState mapState);

    void react(int width) override ;

    ~ExitSpace() {}

};


#endif
