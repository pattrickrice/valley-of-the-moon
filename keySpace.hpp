/*********************************************************************
 * Author: Patrick Rice
 * Date: 11/26/2017
 * Description: Header file for the key space class
*********************************************************************/

#ifndef KEYSPACE_HPP
#define KEYSPACE_HPP

#include "space.hpp"
#include <string>

using std::string;


class KeySpace : public Space {
    string key;
    bool keyPresent;
public:
    KeySpace();

    KeySpace(char value,
             Space *top,
             Space *left,
             Space *right,
             Space *bottom,
             MapState mapState,
             string key);

    void react(int width) override;

    string getKey();

    bool isKeyPresent();

    string takeKey();

    ~KeySpace() {}

};


#endif
