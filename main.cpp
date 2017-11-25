/*********************************************************************
 * Program Name: lab9 Stack and Queue Containers
 * Author: Patrick Rice
 * Date: 11/24/2017
 * Description: Has two primary options, creating a buffer sim,
 * (implemented in the buffer sim class) or creating a palindrome,
 * (implemented in the main.cpp file). Both operations use STL
 * containers.
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

    int width = 72, mainMenuChoice = 0;
    unsigned min = 0, max = 0;


    return 0;
}