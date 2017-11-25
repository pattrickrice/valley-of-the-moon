/*********************************************************************
 * Author: Patrick Rice
 * Date: 10/5/2017
 * Description: Header file for the Menu class
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP

#include <vector>

using std::vector;

#include <string>

using std::string;

class Menu {
private:
    vector<string> options;
    int userChoice;
    string menuGreeting;
    int userSecondChoice;

    void setChoice();

    void setSecondChoice();

public:
    Menu();

    Menu(string);

    void printMenu();

    void print2ChoiceMenu();

    int getChoice();

    int getSecondChoice();

    void addOption(string);
};

#endif