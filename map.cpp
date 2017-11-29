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
}

/*********************************************************************
 * Constructor taking the name of the file.
 * @param filename is the name of the map file.
*********************************************************************/
Map::Map(string filename) {
    this->boardHead = nullptr;
    importBoard(filename);
}

/*********************************************************************
 * Reads the text file and creates data members with the map
 * information.
 * @param fileName is the name of the file.
*********************************************************************/
bool Map::importBoard(string fileName) {
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

            if (readChar == 6) {
                cout << "here";
            }
            // assign value
            // first tile of map
            if (boardHead != nullptr && width != 0) {
                current->setRight(this->setSpace(
                        readChar,
                        tempUp,
                        current,
                        nullptr,
                        nullptr));
            } else if (boardHead != nullptr) {
                current->setBottom(this->setSpace(
                        readChar,
                        nullptr,
                        nullptr,
                        nullptr,
                        nullptr));
            } else {
                current = this->setSpace(
                        readChar,
                        nullptr,
                        nullptr,
                        nullptr,
                        nullptr);
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

void Map::printMap() {
    string print;
    if (boardHead != nullptr) {
        auto current = boardHead;
        auto nextRow = boardHead;

        // there is a another row
        if (boardHead->getBottom() != nullptr) {
            nextRow = boardHead->getBottom();
        }

        // go through the list
        do {
            while (current != nullptr) {
                print += current->getValue();
                // x-axis
                current = current->getRight();
            }

            if (nextRow != nullptr) {
                current = nextRow;
                nextRow = current->getBottom();
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
*********************************************************************/
Space *Map::setSpace(char value,
                     Space *top,
                     Space *left,
                     Space *right,
                     Space *bottom) {
    Space *newTile;
    EmptySpace *newEmpty;
    WallSpace *newWall;
    KeySpace *newKey;
    DoorSpace *newDoor;

    // create space based on value
    switch (value) {
        case ' ':
            newEmpty = new EmptySpace(value,
                                     top,
                                     left,
                                     right,
                                     bottom);
            newTile = newEmpty;
            break;
        case '-':
        case '|':
        case '=':
        case '+':
            newWall = new WallSpace(value,
                                     top,
                                     left,
                                     right,
                                     bottom);
            newTile = newWall;
            break;
        case 'K':
            newKey = new KeySpace(value,
                                     top,
                                     left,
                                     right,
                                     bottom);
            newTile = newKey;
            break;
        case 'D':
            newDoor = new DoorSpace(value,
                                   top,
                                   left,
                                   right,
                                   bottom);
            newTile = newDoor;
            break;

        default:
            newTile = new EmptySpace(value,
                                     top,
                                     left,
                                     right,
                                     bottom);
    }

    return newTile;
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
