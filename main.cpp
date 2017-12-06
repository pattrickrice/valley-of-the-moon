/*********************************************************************
 * Program Name: Valley of the Moon
 * Author: Patrick Rice
 * Date: 12/5/2017
 * Description: A text based adventure game, that uses the keyboard
 * to move around. The character must collect a set of keys in order
 * to reach the end of the game. The number of steps the character
 * has left, is the limit to the length of the game.
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

    Menu playAgain("Would you like to play again?");
    playAgain.addOption("Yes");
    playAgain.addOption("No");


    mainMeu.printMenu();
    mainMenuChoice = mainMeu.getChoice();
    if (mainMenuChoice != 2) {
        do {
            if (mainMenuChoice == 1) {
                // play the game
                GamePlay gameState;
                gameState.play();

                playAgain.printMenu();
                mainMenuChoice = playAgain.getChoice();
            }

        } while (mainMenuChoice != 2);
    }

    printMessage("Goodbye",width);

    return 0;
}