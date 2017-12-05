/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Implementation file for the keySpace class
*********************************************************************/
#include "keySpace.hpp"
#include "utilities.hpp"

KeySpace::KeySpace() = default;

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
KeySpace::KeySpace(char value,
                   Space *top,
                   Space *left,
                   Space *right,
                   Space *bottom,
                   MapState mapState, string key) : Space(KEY,
                                                          true,
                                                          value,
                                                          top,
                                                          left,
                                                          right,
                                                          bottom,
                                                          mapState) {
    this->key = key;
    this->keyPresent = true;
}

/*********************************************************************
 * Returns the value of the key
 ********************************************************************/
string KeySpace::getKey() {
    return key;
}

/*********************************************************************
 * Returns if the user has taken the key.
 ********************************************************************/
bool KeySpace::isKeyPresent() {
    return this->keyPresent;
}

/*********************************************************************
 * Returns key value to user, changes the display character for the
 * screen.
 ********************************************************************/
string KeySpace::takeKey() {
    setValue(' ');
    keyPresent = false;
    return key;
}

/*********************************************************************
 * Alerts the character of its interaction with the key
 ********************************************************************/
void KeySpace::react(int width) {
    if (isKeyPresent()) {
        printMessage("You picked up the key: "
                     + getKey() + " !", width);
    } else {
        printMessage("This is where I found that key... "
                     + getKey(), width);
    }
}
