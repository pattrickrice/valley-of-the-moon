/*********************************************************************
 * Author: Patrick Rice
 * Date: 10/5/2017
 * Description: The header file of the Utilities class.
*********************************************************************/
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <fstream>

using std::string;
using std::fstream;

unsigned int getInt(unsigned int min, unsigned int max);

string getString(unsigned int min, unsigned int max);

double getDouble(double min, double max);

void printLeftAligned(string, int);

void printCenterTitle(string, int);

void printCenteredString(string, int);

void printBoldCenterTitle(string input, int width);

void printBorder(int);

bool isEven(int);

void printMoneyStatement(string prefix, double money, int width);

string formatTwoDecimalDouble(double value);

void printLeftAndRightAlignedStrings(string prefix, string suffix, int width);

string getMultiWordString(unsigned int, unsigned int);

string getAddress();

void printCenteredBox(string input, int width, char filler);

#endif