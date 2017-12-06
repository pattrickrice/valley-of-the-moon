/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Implementation of the map class
*********************************************************************/
#include "map.hpp"
#include "emptySpace.hpp"
#include "wallSpace.hpp"
#include "keySpace.hpp"
#include "doorSpace.hpp"
#include "exitSpace.hpp"
#include "characterSpace.hpp"
#include <fstream>

using std::fstream;
using std::ios;
using std::endl;
using std::cout;

/*********************************************************************
 * Default constructor
*********************************************************************/
Map::Map() {
    this->boardHead = nullptr;
    this->keyCounter = 0;
    this->doorCounter = 0;
    this->mapID = HOUSE;
}

/*********************************************************************
 * Constructor taking the name of the file.
 * @param mapFileName is the name of the map file.
 * @param keyFileName is the name of the keys file.
 * @param doorFileName is the name of the locks for the doors file.
 * @param mapState is the state the map is in.
*********************************************************************/
Map::Map(string mapFileName, string keyFileName, string doorFileName, MapState mapState) {
    this->keyCounter = this->doorCounter = 0;
    this->mapID = mapState;
    this->boardHead = nullptr;
    keys = importKeys(keyFileName);
    doors = importDoors(doorFileName);
    importBoard(mapFileName, mapState);
}

/*********************************************************************
 * Reads the text file and creates a key vector
 * @param doorFileName is the name of the file.
*********************************************************************/
vector<string> Map::importKeys(string keyFileName) {
    fstream fileStream;
    string readKey;
    fileStream.open(keyFileName);
    vector<string> read;

    // could not open
    if (fileStream.fail()) {
        cout << "[ERROR] Could not open " + keyFileName << endl;
    } else {
        while (fileStream >> keyFileName) {
            read.push_back(keyFileName);
        }
    }
    fileStream.close();
    return read;
}

/*********************************************************************
 * Reads the text file and creates a door vector
 * @param doorFileName is the name of the file.
*********************************************************************/
vector<Map::Door> Map::importDoors(string doorFileName) {
    fstream fileStream;
    string keyID;
    char mapID;
    char doorID;
    MapState mapState;
    Map::Door readDoor;
    fileStream.open(doorFileName);
    vector<Map::Door> read;

    // could not open
    if (fileStream.fail()) {
        cout << "[ERROR] Could not open " + doorFileName << endl;
    } else {
        while (fileStream >> keyID) {
            fileStream >> mapID;
            fileStream >> doorID;

            readDoor.key = keyID;
            mapState = getDoorMapState(mapID);
            readDoor.doorway = mapState;
            readDoor.doorID = doorID;

            read.push_back(readDoor);
        }
    }
    fileStream.close();
    return read;
}

/*********************************************************************
 * Reads the text file and creates data members with the map
 * information.
 * @param fileName is the name of the file.
*********************************************************************/
bool Map::importBoard(string fileName, MapState mapState) {
    fstream fileStream;
    int width = 0, height = 0, maxWidth = 0;
    char readChar;
    fileStream.open(fileName);

    // could not open
    if (fileStream.fail()) {
        cout << "[ERROR] Could not open " + fileName << endl;
        return false;
    } else {
        // get dimensions of file
        readChar = static_cast<char>(fileStream.get());
        while (readChar != EOF) {
            // get current width of line
            width++;

            // end of line
            if (readChar == '\n' || readChar == '\r') {
                // y-axis of map.
                height++;
                // we need to know the width of the map, could change between maps
                if (width > maxWidth) {
                    maxWidth = width;
                }

                // reset
                width = 0;
            }

            readChar = static_cast<char>(fileStream.get());
            if (readChar == '\r') {
                readChar = static_cast<char>(fileStream.get());
            }
        }

        // set object data members
        boardSizeX = maxWidth;
        boardSizeY = height + 1;

        // clear flag and go back to beginning
        fileStream.clear();
        fileStream.seekg(0, ios::beg);

        height = 0;
        width = 0;
        int i = 0;
        Space *current = nullptr, *tempUp = boardHead;
        bool startOfMap, firstRow;

        // add file information
        readChar = static_cast<char>(fileStream.get());
        while (readChar != EOF) {
            startOfMap = (boardHead == nullptr);
            firstRow = (height == 0);
            current = boardHead;

            // if the board has been started
            if (!startOfMap) {
                tempUp = boardHead;
                i = 0;

                if (i < height && width != 0) {
                    while (i < height) {
                        // get to y-axis location

                        current = current->getBottom();

                        if (!firstRow && i < height - 1) {
                            tempUp = tempUp->getBottom();
                        }
                        i++;
                    }
                } else if (width == 0) {
                    while (i < height - 1) {
                        // get to y-axis location
                        current = current->getBottom();
                        if (!firstRow && i < height - 1) {
                            tempUp = tempUp->getBottom();
                        }
                        i++;
                    }
                }


                i = 0;
                //get to x-axis location
                while (i < width - 1) {
                    current = current->getRight();
                    if (!firstRow) {
                        tempUp = tempUp->getRight();
                    }
                    i++;
                }
            }

            // assign value
            // first tile of map
            if (boardHead != nullptr && width != 0) {
                current->setRight(this->setSpace(
                        readChar,
                        tempUp->getRight(),
                        current,
                        nullptr,
                        nullptr,
                        mapState,
                        width, height));

                if (height != 0) {
                    tempUp->getRight()->setBottom(current->getRight());
                }

            } else if (boardHead != nullptr) {
                current->setBottom(this->setSpace(
                        readChar,
                        current,
                        nullptr,
                        nullptr,
                        nullptr,
                        mapState,
                        width,
                        height));
            } else {
                current = this->setSpace(
                        readChar,
                        nullptr,
                        nullptr,
                        nullptr,
                        nullptr,
                        mapState,
                        width,
                        height);
                boardHead = current;
            }

            // assign value
            width++;
            // end of line
            if (readChar == '\n') {
                // y-axis of map.
                height++;
                // we need to know the width of the map, could change between maps
                if (width > maxWidth) {
                    maxWidth = width;
                }

                // reset width;
                width = 0;

            }
            readChar = static_cast<char>(fileStream.get());
            if (readChar == '\r') {
                readChar = static_cast<char>(fileStream.get());
            }
        }

        // close the stream
        fileStream.close();
    }
    return true;
}

/*********************************************************************
 * Prints the map to the screen.
 * @param XCoord is the players XCoordinate
 * @param YCoord is the players YCoordinate
*********************************************************************/
void Map::printMap(int XCoord, int YCoord) {
    int x = 0, y = 0;
    string print;
    if (boardHead != nullptr) {
        Space *current = boardHead;
        Space *nextRow = boardHead;

        // there is a another row
        if (boardHead->getBottom() != nullptr) {
            nextRow = boardHead->getBottom();
        }

        // go through the list
        do {
            while (current != nullptr) {
                // players position
                if (x == XCoord && y == YCoord) {
                    print += 'P';
                } else {
                    print += current->getValue();
                }
                // x-axis
                current = current->getRight();
                x++;
            }

            if (nextRow != nullptr) {
                current = nextRow;
                nextRow = current->getBottom();
                x = 0;
                y++;
            }
        } while (current != nullptr);

        cout << print << endl;
    }
}

/*********************************************************************
 * Returns a pointer to a space character.
 * @param value is the character value
 * @param top is the top space pointer.
 * @param left is the left space pointer.
 * @param right is the right space pointer.
 * @param bottom is the bottom space pointer.
 * @param mapState is the mapState the space has
 * @param currentX is the current XCoord of the board
 * @param currentY is the current YCoord of the board
*********************************************************************/
Space *Map::setSpace(char value,
                     Space *top,
                     Space *left,
                     Space *right,
                     Space *bottom,
                     MapState mapState,
                     int currentX,
                     int currentY) {
    Space *newTile;
    EmptySpace *newEmpty;
    WallSpace *newWall;
    KeySpace *newKey;
    DoorSpace *newDoor;

    string doorKey;

    DoorLocation doorLocation;

    // create space based on value
    switch (value) {
        case ' ':
            newEmpty = new EmptySpace(value,
                                      top,
                                      left,
                                      right,
                                      bottom,
                                      mapState);
            newTile = newEmpty;
            break;
        case '-':
        case '|':
        case '=':
        case '/':
        case '\\':
        case '+':
        case '_':
            newWall = new WallSpace(value,
                                    top,
                                    left,
                                    right,
                                    bottom,
                                    mapState);
            newTile = newWall;
            break;
        case 'K':
            newKey = new KeySpace(value,
                                  top,
                                  left,
                                  right,
                                  bottom,
                                  mapState,
                                  keys.at(keyCounter));
            keyCounter++;
            newTile = newKey;
            break;
        case 'D':
            doorLocation.doorID = doors.at(doorCounter).doorID;
            doorLocation.XCoord = currentX;
            doorLocation.YCoord = currentY;

            doorLocator.push_back(doorLocation);

            newDoor = new DoorSpace(value,
                                    top,
                                    left,
                                    right,
                                    bottom,
                                    doors.at(doorCounter).key,
                                    doors.at(doorCounter).doorway,
                                    doors.at(doorCounter).doorID,
                                    currentX,
                                    currentY);
            doorCounter++;
            newTile = newDoor;
            break;
        case 'N':
            newTile = new CharacterSpace(value,
                                         top,
                                         left,
                                         right,
                                         bottom,
                                         mapState);
            break;
        case 'A':
            newTile = new ExitSpace(value,
                                    top,
                                    left,
                                    right,
                                    bottom,
                                    mapState);
            break;
        case 'S':
            playerStartingX = currentX;
            playerStartingY = currentY;
            value = ' ';

        default:
            newTile = new EmptySpace(value,
                                     top,
                                     left,
                                     right,
                                     bottom,
                                     mapState);
    }

    return newTile;
}

Space *Map::getSpace(int XCoord, int YCoord) {
    int x = 0, y = 0;
    if (boardHead != nullptr) {
        Space *current = boardHead;
        Space *nextRow = boardHead;

        // there is a another row
        if (boardHead->getBottom() != nullptr) {
            nextRow = boardHead->getBottom();
        }

        // go through the list
        do {
            while (current != nullptr) {
                // players position
                if (x == XCoord && y == YCoord) {
                    return current;
                }
                // x-axis
                current = current->getRight();
                x++;
            }

            if (nextRow != nullptr) {
                current = nextRow;
                nextRow = current->getBottom();
                x = 0;
                y++;
            }
        } while (current != nullptr);
    }
    cout << "[ERROR] Did not find player" << endl;
    return nullptr;
}

/*********************************************************************
 * Returns a mapState based on character input
 * @param mapStateID is the input
*********************************************************************/
MapState Map::getDoorMapState(char mapStateID) {
    switch (mapStateID) {
        case 'H':
            return HOUSE;
        case 'F':
            return FOREST;
        case 'D':
            return DEEPFOREST;
        case 'V':
            return VALLEY;
        case 'L':
            return LAKE;
        case 'R':
            return RANCH;
        case 'C':
            return CASTLE;
        default:
            return HOUSE;
    }
}

/*********************************************************************
 * Returns the players starting position X-coordinate
*********************************************************************/
int Map::getPlayerStartingX() {
    return playerStartingX;
}

/*********************************************************************
 * Returns the players starting position Y-coordinate
*********************************************************************/
int Map::getPlayerStartingY() {
    return playerStartingY;
}

/*********************************************************************
 * Returns a doors X-coordinate
 * @param inputDoorID is the door we are looking for
*********************************************************************/
int Map::getDoorXCoord(char inputDoorID) {
    for (unsigned int i = 0; i < doorLocator.size(); ++i) {
        if (doorLocator.at(i).doorID == inputDoorID) {
            return doorLocator.at(i).XCoord;
        }
    }
    return 0;
}

/*********************************************************************
 * Returns a doors Y-coordinate
 * @param inputDoorID is the door we are looking for
*********************************************************************/
int Map::getDoorYCoord(char inputDoorID) {
    for (unsigned int i = 0; i < doorLocator.size(); ++i) {
        if (doorLocator.at(i).doorID == inputDoorID) {
            return doorLocator.at(i).YCoord;
        }
    }
    return 0;
}

/*********************************************************************
 * Returns the board pointer
*********************************************************************/
Space *Map::getBoardHead() {
    return boardHead;
}

/*********************************************************************
 * Returns the x-axis size
*********************************************************************/
int Map::getBoardSizeX() {
    return boardSizeX;
}

/*********************************************************************
 * Returns the y-axis  size
*********************************************************************/
int Map::getBoardSizeY() {
    return boardSizeY;
}

MapState Map::getMapID() {
    return this->mapID;
}

/*********************************************************************
 * Deletes map, no memory leaks here.
*********************************************************************/
Map::~Map() {
    if (boardHead != nullptr) {

        Space *garbage = boardHead;
        Space *current = boardHead;
        Space *nextRowGarbage = nullptr;

        // there is a another row
        if (boardHead->getBottom() != nullptr) {
            nextRowGarbage = boardHead->getBottom();
        }

        // go through the list
        do {
            while (garbage != nullptr) {
                // x-axis
                current = current->getRight();
                delete garbage;
                garbage = current;
            }

            if (nextRowGarbage != nullptr) {
                current = garbage = nextRowGarbage;
                nextRowGarbage = nextRowGarbage->getBottom();
            }
        } while (garbage != nullptr);
    }
}
