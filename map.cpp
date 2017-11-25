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

Map::Map() {

}

Map::Map(string filename) {
    importBoard(filename);
}

bool Map::importBoard(string fileName) {
    fstream fileStream;
    int readChar = nullptr;
    fileStream.open(fileName);

    // could not open
    if (fileStream.fail()) {
        cout << "[ERROR] Could not open " + fileName << endl;
        return false;
    } else {

        // clear flag and go back to beginning
        fileStream.clear();
        fileStream.seekg(0, ios::beg);

        int i = 0;

        // add file information
        while (fileStream >> readChar) {
/*          TODO: count board width
            // create dynamic array
            // add each line to array
            // add file information
*/

        }
    }

    // close the stream
    fileStream.close();

    return true;
}

Map::~Map() {

}
