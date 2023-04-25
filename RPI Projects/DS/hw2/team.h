//
// Created by Jary Chen on 1/23/23.
//

#ifndef HW2_TEAM_H
#define HW2_TEAM_H
#include <iostream>

using namespace std;
class team{
public:
    // constructor that only takes in the team name
    team(string tname);

    // getters
    string gettname() const;
    int getwins() const;
    int getloses() const;
    int getties() const;
    int getgoals() const;
    int getpenalty() const;
    float getwinP() const;
    float getpenP() const;

    //modifier
        // all these 1 on the back means increase by 1
    void win1();
    void lose1();
    void tied1();
    void goal1();
    void penalty1();
    void game1();

private:
    string teamname;
    int wins;
    int loses;
    int ties;
    int goals;
    int penalties;
    int games;

};

// function that sorts the strongest team first
bool strongestt(const team & t1, const team & t2);

// function that sorts the weakest team first
bool weakestt(const team & t1, const team & t2);
#endif //HW2_TEAM_H
