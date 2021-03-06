/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Implementation file for the wallSpace class
*********************************************************************/
#include "wallSpace.hpp"
#include "../utils/utilities.hpp"

WallSpace::WallSpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
WallSpace::WallSpace(char value,
                     Space *top,
                     Space *left,
                     Space *right,
                     Space *bottom,
                     MapState mapState) : Space(WALL,
                                                false,
                                                value,
                                                top,
                                                left,
                                                right,
                                                bottom,
                                                mapState) {
}

/*********************************************************************
 * Alerts the user they cannot proceed
 ********************************************************************/
void WallSpace::react(int width) {
    printMessage("You have hit a wall!", width);
}