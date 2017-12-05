/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: Implementation file for the ExitSpace class
*********************************************************************/
#include "exitSpace.hpp"

ExitSpace::ExitSpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
ExitSpace::ExitSpace(char value,
                     Space *top,
                     Space *left,
                     Space *right,
                     Space *bottom,
                     MapState mapState) : Space(EXIT,
                                                false,
                                                value,
                                                top,
                                                left,
                                                right,
                                                bottom,
                                                mapState) {
}

void ExitSpace::react(int width) {

}