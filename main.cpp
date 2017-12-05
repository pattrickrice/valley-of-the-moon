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

    system("clear");
    printBoldCenterTitle("Valley of the Moon", width);
    printCenteredString("A text-based adventure game", width);
    printCenteredString("Please adjust your console to fit this dialogue", width);
    printBorder(width);

    Menu mainMeu("Would you like to play the game?");
    mainMeu.addOption("Play");
    mainMeu.addOption("Exit");


    do {

        mainMeu.printMenu();
        mainMenuChoice = mainMeu.getChoice();

        if (mainMenuChoice == 1) {
            // play the game
            GamePlay gameState;
            gameState.play();
        }

    } while (mainMenuChoice != 2);


    return 0;
}