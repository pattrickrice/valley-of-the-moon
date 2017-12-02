/*********************************************************************
 * Program Name: Valley of the Moon
 * Author: Patrick Rice
 * Date: 11/24/2017
 * Description:
*********************************************************************/

#include "menu.hpp"
#include "map.hpp"
#include "utilities.hpp"
#include "gamePlay.hpp"

using std::cout;
using std::endl;

int main() {
    // rand() function needs to be seeded only one time. Seeding
    // happens here so that it is only called once.
    unsigned seed;
    seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    int width = 90, mainMenuChoice = 0;


    printBoldCenterTitle("Valley of the Moon", width);
    printCenteredString("A text-based adventure game", width);
    printBorder(width);

    GamePlay gameState;
    gameState.play();

    printBoldCenterTitle("Goodbye", width);

    return 0;
}