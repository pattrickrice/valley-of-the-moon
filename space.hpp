/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the space class
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

enum SpaceType {
    EMPTY, WALL, DOOR, KEY,
};

class Space {
    Space *top;
    Space *right;
    Space *left;
    Space *bottom;

    SpaceType spaceType;
    bool permiable;
    char value;

public:
    Space();

    Space(SpaceType,
          bool,
          char,
          Space *,
          Space *,
          Space *,
          Space *);

    SpaceType getSpaceType();

    void setSpaceType(SpaceType);

    bool canMoveTo();

    void setTop(Space *);

    void setRight(Space *);

    void setLeft(Space *);

    void setBottom(Space *);

    void setValue(char);

    Space *getTop();

    Space *getRight();

    Space *getLeft();

    Space *getBottom();

    char getValue();

    bool isPermiable();

    virtual void printMessage() = 0;
    
    virtual ~Space();
};

#endif
