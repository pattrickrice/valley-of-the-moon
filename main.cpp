/*********************************************************************
 * Program Name: Valley of the Moon
 * Author: Patrick Rice
 * Date: 11/24/2017
 * Description:
*********************************************************************/

#include "menu.hpp"
#include "map.hpp"
#include "utilities.hpp"
#include "player.hpp"

using std::cout;
using std::endl;

int main() {
    // rand() function needs to be seeded only one time. Seeding
    // happens here so that it is only called once.
    unsigned seed;
    seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    int width = 90, mainMenuChoice = 0;
    unsigned min = 0, max = 0;


    printBoldCenterTitle("Valley of the Moon", width);
    printCenteredString("A text-based adventure game", width);
    printBorder(width);

    Map map1("houseMap.txt");
    Player p1(2,2);

    // moves player
    map1.printMap(p1.getXCoord(), p1.getYCoord());
    // takes a,s,d,w
    p1.makeMove('s');
    map1.printMap(p1.getXCoord(), p1.getYCoord());




    return 0;
}