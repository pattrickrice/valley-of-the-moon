/*********************************************************************
 * Author: Patrick Rice
 * Date: 10/5/2017
 * Description: The class implementation file for the Menu class.
*********************************************************************/
#include "menu.hpp"
#include "utilities.hpp"
#include <sstream>

using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;

/*********************************************************************
 * Default Constructor, no greeting is provided.
 ********************************************************************/
Menu::Menu() {
    menuGreeting = "";
};

/*********************************************************************
 * Constructor with greeting. Greeting is printed at the top of the
 * menu. Typically contains instructions or a description of what the
 * user is choosing.
 ********************************************************************/
Menu::Menu(string greeting) {
    this->menuGreeting = greeting;
};

/*********************************************************************
 * The printMenu function can be called on the menu object. Both
 * prints the menu and prompts the user for input. The menu items
 * are given an additional 1 so that the list starts at 1.
 ********************************************************************/
void Menu::printMenu() {
    cout << endl << menuGreeting << endl;

    for (unsigned int i = 0; i < options.size(); i++) {
        cout << i + 1 << "." << options[i] << endl;
    }
};

/*********************************************************************
 * Calls the printMenu function and prompts for second choice
 ********************************************************************/
void Menu::print2ChoiceMenu(){
    printMenu();
};


/*********************************************************************
 * Gets the choice from the user. Requires an int as the input.
 ********************************************************************/
void Menu::setChoice() {
    unsigned int min = 0;
    cout << "Please enter a selection: ";
    this->userChoice = getInt(min,
                              static_cast<unsigned int>(options.size()));
};

/*********************************************************************
 * Gets the 2nd choice from the user. Requires an int as the input.
 ********************************************************************/
void Menu::setSecondChoice(){
    unsigned int min = 0;
    cout << "Please enter your 2nd selection: ";
    this->userSecondChoice = getInt(min,
                                    static_cast<unsigned int>(options.size()));
};

/*********************************************************************
 * Adds an option to the menu. Menus should require at least 2 options
 ********************************************************************/
void Menu::addOption(string optionText) {
    options.push_back(optionText);
};

/*********************************************************************
 * Returns the users selection. The int will correspond to the menus
 * options in the order that they were added.
 ********************************************************************/
int Menu::getChoice() {
    setChoice();
    return userChoice;
};

/*********************************************************************
 * Returns the users second selection. The int will correspond to the
 * menu's options in the order that they were added.
 ********************************************************************/
int Menu::getSecondChoice(){
    setSecondChoice();
    return userSecondChoice;
};
