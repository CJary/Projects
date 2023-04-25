//
// Created by Jary Chen on 1/23/23.
//

#include "player.h"

player::player(string pname, string tname) {
    playername = pname;
    teamname = tname;
    goals = 0;
    assists = 0;
    penalties = 0;
}

string player::getpname() const {
    return playername;
}

string player::gettname() const {
    return teamname;
}

int player::getgoals() const {
    return goals;
}

int player::getassists() const {
    return assists;
}

int player::getpenalty() const {
    return penalties;
}

void player::goal1() {
    goals++;
}

void player::assist1() {
    assists++;
}

void player::penalty1() {
    penalties++;
}

// returns true or false in order of priority for the strongest players
bool strongestp(const player &p1, const player &p2) {
    if ((p1.getgoals() + p1.getassists()) > (p2.getgoals() + p2.getassists())){
        return true;
    }
    else if ((p1.getgoals() + p1.getassists()) < (p2.getgoals() + p2.getassists())){
        return false;
    }

    if (p1.getpenalty() < p2.getpenalty()){
        return true;
    }
    else if (p1.getpenalty() > p2.getpenalty()){
        return false;
    }

    // alphabetical order
    if (p1.getpname() < p2.getpname()){
        return true;
    }
    else if (p1.getpname() > p2.getpname()){
        return false;
    }

    return false;
}

// returns true or false in order of priority for the weakest players
bool weakestp(const player &p1, const player &p2) {
    if (p1.getpenalty() > p2.getpenalty()){
        return true;
    }
    else if (p1.getpenalty() < p2.getpenalty()){
        return false;
    }

    if (p1.getgoals() < p2.getgoals()){
        return true;
    }
    else if (p1.getgoals() > p2.getgoals()){
        return false;
    }

    if (p1.getassists() < p2.getassists()){
        return true;
    }
    else if (p1.getassists() > p2.getassists()){
        return false;
    }

    // alphabetical order
    if (p1.getpname() > p2.getpname()){
        return true;
    }
    else if (p1.getpname() < p2.getpname()){
        return false;
    }
    return false;
}
