/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Implementation file for the DoorSpace class
*********************************************************************/
#include "doorSpace.hpp"

DoorSpace::DoorSpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
DoorSpace::DoorSpace(char value,
                     Space *top,
                     Space *left,
                     Space *right,
                     Space *bottom,
                     string key,
                     MapState mapState,
                     char doorID,
                     int XCoord,
                     int YCoord) : Space(DOOR,
                                         true,
                                         value,
                                         top,
                                         left,
                                         right,
                                         bottom,
                                         mapState) {
    this->key = key;
    this->doorID = doorID;
    this->XCoord = XCoord;
    this->YCoord = YCoord;
}

void DoorSpace::printMessage() {}


/********************************************************************
* Returns the door's required key
********************************************************************/
string DoorSpace::getKey() {
    return this->key;
}

/********************************************************************
* Returns the door's ID
********************************************************************/
char DoorSpace::getDoorID() {
    return this->doorID;
}

/********************************************************************
* Returns the door's X-coordinate
********************************************************************/
int DoorSpace::getXCoord() {
    return this->XCoord;
}

/********************************************************************
* Returns the door's Y-coordinate
********************************************************************/
int DoorSpace::getYCoord() {
    return this->YCoord;
}
