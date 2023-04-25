//
// Created by Jary Chen on 1/23/23.
//

#ifndef HW2_PLAYER_H
#define HW2_PLAYER_H
#include <iostream>

using namespace std;
class player {
public:
    // constructor that only takes in the team name and player name
    player(string pname, string tname);

    //getter
    string getpname() const;
    string gettname() const;
    int getgoals() const;
    int getassists() const;
    int getpenalty() const;

    //modifier
         // all these 1 on the back means increase by 1
    void goal1();
    void assist1();
    void penalty1();

private:
    string playername;
    string teamname;
    int goals;
    int assists;
    int penalties;
};

// function that sorts the strongest players first
bool strongestp(const player & p1, const player & p2);

// function that sorts the weakest players first
bool weakestp(const player & p1, const player & p2);
#endif //HW2_PLAYER_H
