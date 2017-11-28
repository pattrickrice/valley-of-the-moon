/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/25/2017
 * Description: Implementation of the map class
*********************************************************************/
#include "map.hpp"
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

        /** DEBUG cout << endl << "[MAX WIDTH] " << maxWidth << endl << "[HEIGHT] " << height << endl;*/

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

            //cout << readChar;

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
                    while (i < height -1) {
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
                current->setRight(new Space(EMPTY,
                                            true,
                                            readChar,
                                            tempUp,
                                            current,
                                            nullptr,
                                            nullptr));
            } else if (boardHead != nullptr) {
                current->setBottom(new Space(EMPTY,
                                             true,
                                             readChar,
                                             nullptr,
                                             nullptr,
                                             nullptr,
                                             nullptr));
            } else {
                current = new Space(EMPTY,
                                    true,
                                    readChar,
                                    nullptr,
                                    nullptr,
                                    nullptr,
                                    nullptr);
                boardHead = current;
            }

            // set the previous pointer's right pointer


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

void Map::printMap(){
    string print;
    if (boardHead != nullptr) {
        Space *current = boardHead;
        Space *nextRow = nullptr;

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
                nextRow = nextRow->getBottom();
            }
        } while (current != nullptr);

        cout << print << endl;
    }
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

                // get rid of the pointers
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
