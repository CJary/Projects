//
// Created by Jary Chen on 3/19/23.
//

#ifndef HW7_FIGHTER_H
#define HW7_FIGHTER_H

#include <string>
#include <iostream>
#include <map>

using namespace std;
class Fighter {
private:
    string name;
    map<string, int> fMoves; //map that holds each characters move and frames

public:

    //constructors
    Fighter(){};
    Fighter(const string& n){
        name = n;
    }

    //getter
    int getFrame(const string& move) const;

    //setter
    void setFrame (const string& move, int f);


};


#endif //HW7_FIGHTER_H
