/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Header file for the DoorSpace class
*********************************************************************/
#ifndef DOORSPACE_HPP
#define DOORSPACE_HPP

#include <string>
#include "space.hpp"

using std::string;


class DoorSpace : public Space {
    string key;
    char doorID;
    int XCoord;
    int YCoord;
    int width;
public:
    DoorSpace();

    DoorSpace(char value,
              Space *top,
              Space *left,
              Space *right,
              Space *bottom,
              string key,
              MapState mapState,
              char doorID,
              int XCoord,
              int YCoord
    );

    string getKey();

    char getDoorID();

    int getXCoord();

    int getYCoord();

    void react(int width) override;

    ~DoorSpace() {
        // Do some important cleanup
    }

};


#endif
