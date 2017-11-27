/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Header file for the space class
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

class Space {
    Space *top;
    Space *right;
    Space *left;
    Space *bottom;

    enum SpaceType {
        EMPTY, WALL, DOOR, KEY,
    };
    SpaceType spaceType;
    bool permiable;

public:
    Space();

    Space(SpaceType,
          bool,
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

    Space *getTop();

    Space *getRight();

    Space *getLeft();

    Space *getBottom();
    
    ~Space();
};

#endif
