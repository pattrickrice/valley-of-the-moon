/*********************************************************************
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: Implementation file for the characterSpace class
*********************************************************************/
#include "characterSpace.hpp"
#include "../utils/utilities.hpp"
using std::string;
using std::cin;

CharacterSpace::CharacterSpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
CharacterSpace::CharacterSpace(char value,
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

/*********************************************************************
 * prints the characters dialogue
 * @param width is the width of the console
 ********************************************************************/
void CharacterSpace::react(int width) {
    string dialogue;
    dialogue += "Stop wasting time! Find the antidote!";
    printBorder(width);
    printLeftAligned(dialogue, width);
    printBorder(width);
}