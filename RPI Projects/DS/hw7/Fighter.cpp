//
// Created by Jary Chen on 3/19/23.
//

#include "Fighter.h"

//returns the frame for a certain move
int Fighter::getFrame(const string &move) const {
    return fMoves.find(move)->second;
}

//create a move and set the frame to the move
void Fighter::setFrame(const string &move, int f) {
    fMoves[move] = f;
}



