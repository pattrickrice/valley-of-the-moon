/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: Implementation file for the ExitSpace class
*********************************************************************/
#include "exitSpace.hpp"
#include "utilities.hpp"

using std::string;
using std::cin;

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
                                                true,
                                                value,
                                                top,
                                                left,
                                                right,
                                                bottom,
                                                mapState) {
}

/*********************************************************************
 * Tells the character they found the end of the game
 ********************************************************************/
void ExitSpace::react(int width) {
    string dialogue;
    dialogue += "You've found the antidote! [Press enter to continue]";
    printBorder(width);
    printLeftAligned(dialogue, width);
    printBorder(width);
    cin.ignore();
}