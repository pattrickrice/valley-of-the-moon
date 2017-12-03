/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Implementation file for the empty space class
*********************************************************************/
#include "emptySpace.hpp"

EmptySpace::EmptySpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
EmptySpace::EmptySpace(char value,
                       Space *top,
                       Space *left,
                       Space *right,
                       Space *bottom) : Space(EMPTY,
                                              true,
                                              value,
                                              top,
                                              left,
                                              right,
                                              bottom) {
}
void EmptySpace::printMessage(){}


