/*********************************************************************
 * Program Name: Valley of the Moon
 * Author: Patrick Rice
 * Date: 11/24/2017
 * Description:
*********************************************************************/
#include "menu.hpp"
#include "utilities.hpp"

using std::cout;
using std::endl;

int main() {
    // rand() function needs to be seeded only one time. Seeding
    // happens here so that it is only called once.
    unsigned seed;
    seed = static_cast<unsigned int>(time(0));
    srand(seed);

    int width = 100, mainMenuChoice = 0;
    unsigned min = 0, max = 0;


    printBoldCenterTitle("Valley of the Moon", width);
    printCenteredString("A text-based adventure game", width);
    printBorder(width);


    return 0;
}