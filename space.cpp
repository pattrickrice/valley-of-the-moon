/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Implementation file for the space class
*********************************************************************/
#include "space.hpp"

/*********************************************************************
 * Default constructor. Should not be called
 ********************************************************************/
Space::Space() {
    this->spaceType = EMPTY;
    this->permeable = false;
    this->value = ' ';
    setTop(nullptr);
    setLeft(nullptr);
    setBottom(nullptr);
    setRight(nullptr);
}

/*********************************************************************
 * Constructor.
 * @param spaceType is the category of space
 * @param permeable whether or not a character can move to the space/
 * @param value is the character value
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 ********************************************************************/
Space::Space(SpaceType spaceType,
             bool permeable,
             char value,
             Space *top,
             Space *left,
             Space *right,
             Space *bottom,
             MapState mapState) {
    this->spaceType = spaceType;
    this->permeable = permeable;
    this->value = value;
    setTop(top);
    setLeft(left);
    setBottom(bottom);
    setRight(right);
    this->mapState = mapState;
}

/*********************************************************************
 * Returns space type
 ********************************************************************/
SpaceType Space::getSpaceType() {
    return this->spaceType;
}

/*********************************************************************
 * sets the space type
 ********************************************************************/
void Space::setSpaceType(SpaceType spaceType) {
    this->spaceType = spaceType;
}

/*********************************************************************
 * Returns if the character can move into it.
 ********************************************************************/
bool Space::canMoveTo() {
    return this->permeable;
}

/*********************************************************************
 * Sets the top pointer
 * @param top is the pointer to the top space
 ********************************************************************/
void Space::setTop(Space *top) {
    this->top = top;
}

/*********************************************************************
 * Sets the right pointer
 * @param right is the pointer to the right space
 ********************************************************************/
void Space::setRight(Space *right) {
    this->right = right;
}

/*********************************************************************
 * Sets the left pointer
 * @param left is the pointer to the left space
 ********************************************************************/
void Space::setLeft(Space *left) {
    this->left = left;
}

/*********************************************************************
 * Sets the bottom pointer
 * @param bottom is the pointer to the bottom space
 ********************************************************************/
void Space::setBottom(Space *bottom) {
    this->bottom = bottom;
}

/*********************************************************************
 * Sets the character value which is printed
 * @param value is the character
 ********************************************************************/
void Space::setValue(char value) {
    this->value = value;
}

/*********************************************************************
 * Returns pointer to the top space
 ********************************************************************/
Space *Space::getTop() {
    return top;
}

/*********************************************************************
 * Returns pointer to the right space
 ********************************************************************/
Space *Space::getRight() {
    return right;
}

/*********************************************************************
 * Returns pointer to the left space
 ********************************************************************/
Space *Space::getLeft() {
    return left;
}

/*********************************************************************
 * Returns pointer to the bottom space
 ********************************************************************/
Space *Space::getBottom() {
    return bottom;
}

/*********************************************************************
 * Returns pointer to the bottom space
 ********************************************************************/
char Space::getValue() {
    return value;
}

/*********************************************************************
 * Returns if the space is permiable
 ********************************************************************/
bool Space::isPermeable() {
    return permeable;
}

MapState Space::getMapState(){
    return mapState;
}

/*********************************************************************
 * Destructor
 ********************************************************************/
Space::~Space() {
};
