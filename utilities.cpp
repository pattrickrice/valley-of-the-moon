/*********************************************************************
 * Author: Patrick Rice
 * Date: 10/5/2017
 * Description: The implementation of the Utilities class. Class is
 * meant to provide functions that are common and useful.
*********************************************************************/
#include "utilities.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::string;
using std::fstream;
using std::vector;

/*********************************************************************
 * Integer validation. Takes the entire line as a string,
 * finds the integer in the string. Also checks if the input
 * is a float with "." check. Takes in two parameters that
 * define the range of the acceptable int.
 *
 * @param min is the minimum acceptable.
 * @param max is the maximum acceptable.
 *
 * Sources cited:
 * stringstream: https://stackoverflow.com/questions/16987461/extraction-of-integers-from-strings
 *********************************************************************/
unsigned int getInt(unsigned int min, unsigned int max) {
    bool validInput = false;
    unsigned int validInt = 0;
    string userInput;
    do {
        getline(cin, userInput);
        stringstream ss(userInput);
        if (ss >> validInt) {
            //found an integer!
            string decimal(".");
            if (userInput.find(decimal) != string::npos) {
                //found a decimal
                cout << "The selection must be a whole number!"
                     << endl;
            } else {
                //pass as a whole number and not a long string.
                //now check if its in the range
                if (validInt < min || validInt > max) {

                    cout << "The selection must be between "
                         << min << " and "
                         << max << endl;
                    cout << "You input: " << validInput << endl;
                } else {
                    //it's all good!
                    validInput = true;
                }
            }
        } else {
            //did not find an integer!
            cout << "Please enter a number!" << endl;
        }
        if (!validInput) {
            //reprompt for an input!
            cout << "Please enter a different selection: ";
        }
    } while (!validInput);
    return validInt;
}

/*********************************************************************
 * Double validation. Takes the entire line as a string,
 * finds the double in the string. Takes in two parameters that
 * define the range of the acceptable double.
 *
 * @param min is the minimum acceptable.
 * @param max is the maximum acceptable.
*********************************************************************/
double getDouble(double min, double max) {
    bool validInput = false;
    double validDouble = 0;
    string userInput;
    do {
        getline(cin, userInput);
        stringstream ss(userInput);
        if (ss >> validDouble) {
            //found an Double!
            if (userInput.size() > max || userInput.size() < min) {
                //not in the range of acceptable inputs.
                cout << "The selection must be between "
                     << min + 1 << " and "
                     << max << endl;
            } else {
                //pass as a whole number and not a long string.
                //now check if its in the range
                if (validDouble < min || validDouble > max) {
                    cout << "The selection must be between "
                         << min << " and "
                         << max << endl;
                } else {
                    //it's all good!
                    validInput = true;
                }
            }
        }
    } while (!validInput);
    return validDouble;
}

/*********************************************************************
 * String validation. Takes the entire line as a string.
 *
 * @param min is the minimum length acceptable.
 * @param max is the maximum length acceptable.
*********************************************************************/
string getString(unsigned int min, unsigned int max) {
    bool validInput = false;
    unsigned int containsInt = 0;
    string userInput;
    do {
        getline(cin, userInput);
        stringstream ss(userInput);
        string decimal(".");
        string space(" ");

        if (ss >> containsInt) {
            //found an integer!
            cout << "The word cannot contain numbers!" << endl;
        } else if (userInput.find(decimal) != string::npos) {
            //found a decimal
            cout << "The word cannot contain decimals!"
                 << endl;
        } else if (userInput.size() > max || userInput.size() < min) {
            //not in the range of acceptable inputs.
            cout << "The word must be between "
                 << min + 1 << " and "
                 << max << " letters long" << endl;
        } else if (userInput.find(space) != string::npos) {
            // contains space
            cout << "The word cannot contain a space!" << endl;
        } else {
            //it's all good!
            validInput = true;
        }
        if (!validInput) {
            //reprompt for an input!
            cout << "Please enter a different selection: ";
        }

    } while (!validInput);
    return userInput;

}

/*********************************************************************
 * Retrieves a character from the user, requires a return.
*********************************************************************/
char getCharacterWithReturn(char acceptable[], int size) {
    char inputChar = 'a';
    string inputString;
    bool valid = false;

    // loop if not valid character
    while (!valid) {
        // get input
        getline(cin, inputString);
        stringstream ss(inputString);

        // first character is user input
        ss >> inputString;
        inputChar = inputString.at(0);

        // check that it is acceptable.
        for (int i = 0; i < size; ++i) {
            if (inputChar == acceptable[i]) {
                valid = true;
            }
        }
        if (!valid) {
            cout << "Please choose from: ";

            for (int i = 0; i < size - 1; ++i) {
                cout << acceptable[i] + ", ";
            }
            cout << acceptable[size - 1] + ' ';
        }
    }

    return inputChar;
}

/*********************************************************************
 * Retrieves a character from the user.
 * @warning Relies on Linux commands
 * Source: https://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar
*********************************************************************/
char getCharacterNoReturn(char acceptable[], int size) {
    bool valid = false;
    string userInput;
    string output;

    char inputChar = 'a';
    char pushing;

    // acceptable characters
    for (int i = 0; i < size - 1; ++i) {
        pushing = acceptable[i];
        output.push_back(pushing);
        output += ", ";
    }
    output.push_back(acceptable[size - 1]);


    // loop if not valid character
    while (!valid) {
        // get input
        system("stty raw");
        cin.get(inputChar);
        system("stty cooked");
        cout << endl;

        // check that it is acceptable.
        for (int i = 0; i < size; ++i) {
            if (inputChar == acceptable[i]) {
                valid = true;
            }
        }
        if (!valid) {
            cout << "Please choose from: " + output << endl;
        }
    }
    return inputChar;
}

/*********************************************************************
 * Takes a string and formats the output to have a border on the left
 * and the right of the output.
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 ********************************************************************/
void printLeftAligned(string input, int width) {

    string buffer;
    stringstream ss(input);
    string build;
    vector<string> brokenStrings;

    // split by white space
    // break string up if it is too long.
    while (ss >> buffer) {
        build += buffer + " ";
        if (build.size() == static_cast<unsigned int>(width) - 4) {
            brokenStrings.push_back(build);
            build.clear();
        }
    }
    brokenStrings.push_back(build);

    //get string length
    int stringLength;
    //left border
    string output;

    for (unsigned int j = 0; j < brokenStrings.size(); ++j) {
        stringLength = static_cast<int>(brokenStrings.at(j).length());

        //left border
        output = "| ";
        output += brokenStrings.at(j);

        //fill empty space of the box
        for (int i = 0; i < width - 2 - stringLength; ++i) {
            output += " ";
        }

        //right border
        output += "|\n";
        cout << output;
    }
}

/*********************************************************************
 * Takes a string and formats the output to have the string in the
 * center of the line with a "-" border around it.
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 ********************************************************************/
void printCenterTitle(string input, int width) {
    printCenteredBox(input, width, '-');
}

/*********************************************************************
 * Takes a string and formats the output to have the string in the
 * center of the line with a "=" border around it.
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 ********************************************************************/
void printBoldCenterTitle(string input, int width) {
    printCenteredBox(input, width, '=');
}

/*********************************************************************
 * Takes a string and formats the output to have the string in the
 * center of the line with a " " border around it.
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 ********************************************************************/
void printCenteredString(string input, int width) {
    printCenteredBox(input, width, ' ');
}

/*********************************************************************
 * Takes a string and formats the output to be a box with a centered
 * message
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 ********************************************************************/
void printMessage(string input, int width) {
    printBorder(width);
    printCenteredString(input, width);
    printBorder(width);
}

/*********************************************************************
 * Prints a border with "-" dependent on the width given.
 *
 * @param width is the width of the border.
 ********************************************************************/
void printBorder(int width) {
    string output;
    output += "+";
    for (int i = 1; i < width; ++i) {
        output += "-";
    }
    output += "+\n";
    cout << output;
}

/*********************************************************************
 * Returns whether or not a given number is even or odd.
 * @param number is the number to be evaluated.
 ********************************************************************/
bool isEven(int number) {
    return number % 2 == 0;
}

/*********************************************************************
 * Formats a statement with a string and a dollar amount. Prints
 * the statement.
 * @param prefix the left side of the statement.
 * @param money is the dollar amount.
 * @param width is the width of the box.
 ********************************************************************/
void printMoneyStatement(string prefix, double money, int width) {
    // Conversion found here:
    // https://stackoverflow.com/questions/29200635/convert-float-to-string-with-set-precision-number-of-decimal-digits
    stringstream total;
    stringstream dollarAmount;
    dollarAmount << "$" << std::fixed << std::setprecision(2) << money;
    printLeftAndRightAlignedStrings(prefix, dollarAmount.str(), width);
}

/*********************************************************************
 * Formats a statement with a string and a value that displays two
 * decimals. Prints the statement.
 * @param prefix is the prefix of the statement
 * @param value is the value on the right
 * @param width is the width of the box
 ********************************************************************/
void printTwoDecimalStatement(string prefix, double value, int width) {
    stringstream twoDecimalValue;
    twoDecimalValue << std::fixed << std::setprecision(2) << value;
    printLeftAndRightAlignedStrings(prefix, twoDecimalValue.str(), width);
}

/*********************************************************************
 * Formats and returns a double as a two decimal string.
 * @param double is the value to be formatted.
 ********************************************************************/
string formatTwoDecimalDouble(double value) {
    stringstream twoDecimalValue;
    twoDecimalValue << std::fixed << std::setprecision(2) << value;
    return twoDecimalValue.str();
}

/*********************************************************************
 * Prints one line with a left aligned string and a right aligned
 * string.
 *
 * @param prefix is the left side of the statement.
 * @param suffix is the right side of the statement
 * @param width is the width of the box.
 ********************************************************************/
void printLeftAndRightAlignedStrings(string prefix, string suffix, int width) {
    string total = prefix + suffix;

    //get length of entire string
    int stringLength = static_cast<int>(total.length());

    //left border
    string output = "| ";
    output += prefix;

    //fill empty space of the box
    for (int i = 0; i < width - 3 - stringLength; ++i) {
        output += " ";
    }

    output += suffix + " ";
    //right border
    output += "|\n";
    cout << output;
}

/*********************************************************************
 * Gets a string with multiple words in it.
 ********************************************************************/
string getMultiWordString(unsigned int min, unsigned int max) {
    bool validInput = false;
    string userInput;
    do {
        getline(cin, userInput);
        stringstream ss(userInput);

        if (ss.str().empty()) {
            cout << "Field cannot be left blank!" << endl;
            cout << "Please enter your selection: ";
        } else if (ss.str().length() < min || ss.str().length() > max) {
            //not in the range of acceptable inputs.
            cout << "The word must be between "
                 << min << " and "
                 << max << " letters long" << endl;
        } else {
            validInput = true;
        }
    } while (!validInput);
    return userInput;
}

/*********************************************************************
 * Prompts the user to enter a multiline address.
 ********************************************************************/
string getAddress() {
    bool validInput = false;
    string userInput, address;
    do {
        cout << "Please enter Address line 1: ";
        getline(cin, userInput);
        stringstream ss(userInput);

        cout << "Please enter Address line 2: ";
        getline(cin, userInput);
        stringstream ss2(userInput);
        if (ss.str().empty() && ss2.str().empty()) {
            cout << "Field cannot be left blank!";
        } else {
            validInput = true;
            address += ss.str() + " " + ss2.str();
        }
    } while (!validInput);
    return address;
}

/*********************************************************************
 * Takes a string and formats the output to have the string in the
 * center of the line with a character surrounding.
 *
 * @input is the string to be formatted
 * @width is the width of the box the string will be inside
 * @filler is the character filling the line.
 ********************************************************************/
void printCenteredBox(string input, int width, char filler) {
    string output;
    unsigned long stringLength = input.length();
    bool stringEven = isEven(static_cast<int>(stringLength));
    bool widthEven = isEven(width);
    int stringHalf = static_cast<int>(stringLength / 2);
    int widthHalf = width / 2;

    //left border
    output = "+";

    // Number of dashes will depend on the number of characters
    // in the string and the width of the box. There are four
    // possible cases.
    if (stringEven) {
        if (widthEven) {

            for (int i = 1; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
            output += " " + input + " ";
            for (int i = 1; i < widthHalf - stringHalf - 1; ++i) {
                output += filler;
            }
        } else {
            for (int i = 1; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
            output += " " + input + " ";
            for (int i = 1; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
        }
    } else {
        if (widthEven) {
            for (int i = 2; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
            output += " " + input + " ";
            for (int i = 2; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
        } else {
            for (int i = 2; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
            output += " " + input + " ";
            for (int i = 1; i < widthHalf - stringHalf; ++i) {
                output += filler;
            }
        }
    }

    //right border
    output += "+\n";
    cout << output;
}
