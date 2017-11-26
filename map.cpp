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

}

/*********************************************************************
 * Constructor taking the name of the file.
 * @param filename is the name of the map file.
*********************************************************************/
Map::Map(string filename) {

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
        readChar = fileStream.get();
        while (readChar != EOF) {
            // get current width of line
            width++;

            // end of line
            if (readChar == '\n' || readChar == '\000') {
                // y-axis of map.
                height++;
                // we need to know the width of the map, could change between maps
                if (width > maxWidth) {
                    maxWidth = width;
                }

                // reset
                width = 0;
            }

            readChar = fileStream.get();
        }

        /** DEBUG cout << endl << "[MAX WIDTH] " << maxWidth << endl << "[HEIGHT] " << height << endl;*/

        // set object data members
        boardSizeX = maxWidth;
        boardSizeY = height+1;

        // clear flag and go back to beginning
        fileStream.clear();
        fileStream.seekg(0, ios::beg);

        board = new char *[boardSizeY];
        for (int k = 0; k < boardSizeY; k++) {
            board[k] = new char[boardSizeX];
        }

        height = 0;
        width = 1;
        int i = 0;

        // add file information
        readChar = fileStream.get();
        while (readChar != EOF) {

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
            cout << readChar;
            // assign value

            board[height][width] = readChar;
            width++;
            //cout << width << endl;
            readChar = fileStream.get();
        }

        // close the stream
        fileStream.close();
    }
    return true;
}

char **Map::getBoard() {
    return board;
}

int Map::getBoardSizeX() {
    return boardSizeX;
}

int Map::getBoardSizeY() {
    return boardSizeY;
}

/*********************************************************************
 * Deletes map, no memory leaks here.
*********************************************************************/
Map::~Map() {
    for (int i = 0; i < boardSizeY; ++i) {
        delete[] board[i];
    }
    delete[] board;
}
