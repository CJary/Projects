//
// Created by Jary Chen on 1/23/23.
//

#include "team.h"

team::team(string tname) {
    teamname = tname;
    wins = 0;
    loses = 0;
    ties = 0;
    goals = 0;
    penalties = 0;
    games = 0;
}

string team::gettname() const {
    return teamname;
}
int team::getwins() const {
    return wins;
}

int team::getloses() const {
    return loses;
}

int team::getties() const {
    return ties;
}

int team::getgoals() const {
    return goals;
}

int team::getpenalty() const {
    return penalties;
}

float team::getwinP() const {
    return (wins + 0.5 * ties)/games;
}

float team::getpenP() const {
    return (penalties)/games;
}

void team::win1() {
    wins++;
}

void team::lose1() {
    loses++;
}

void team::tied1() {
    ties++;
}

void team::goal1() {
    goals++;
}

void team::penalty1() {
    penalties++;
}

void team::game1() {
    games++;
}


// returns true or false in order of priority for strongest team
bool strongestt(const team &t1, const team &t2) {
    if (t1.getwinP() > t2.getwinP()){
        return true;
    }
    else if (t1.getwinP() < t2.getwinP()){
        return false;
    }

    if (t1.getgoals() > t2.getgoals()){
        return true;
    }
    else if (t1.getgoals() < t2.getgoals()){
        return false;
    }

    // alphabetical order
    if (t1.gettname() < t2.gettname()){
        return true;
    }
    else if (t1.gettname() > t2.gettname()){
        return false;
    }

    return false;
}

// returns true or false in order of priority for weakest team
bool weakestt(const team &t1, const team &t2) {
    if (t1.getpenalty() > t2.getpenalty()){
        return true;
    }
    else if (t1.getpenalty() < t2.getpenalty()){
        return false;
    }

    if (t1.getgoals() < t2.getgoals()){
        return true;
    }
    else if (t1.getgoals() > t2.getgoals()){
        return false;
    }

    // alphabetical order
    if (t1.gettname() < t2.gettname()){
        return true;
    }
    else if (t1.gettname() > t2.gettname()){
        return false;
    }
    return false;
}
