//
// Created by Jary Chen on 3/16/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//bool function to check if a word can be placed in a certain direction
bool can_add(const string& word, int row, int col, int dr, int dc,
                  const vector<vector<char> >& grid, int ROW, int COL ) {

    if (row + dr * (word.length() - 1) < 0 ||
        row + dr * (word.length() - 1) >= ROW ||
        col + dc * (word.length() - 1) < 0 ||
        col + dc * (word.length() - 1) >= COL) {

        return false;
    }

    //increamenting the direction by dx and dy
    for (int i = 0; i < word.length(); i++) {
        if (grid[row + i*dr][col + i*dc] != '.' &&
            grid[row + i*dr][col + i*dc] != word[i]) {

            return false;
        }
    }

    return true;
}

//places the work at a certain position in a certain direction
void add_word(const string& word, int row, int col, int dr,
              int dc, vector<vector<char> >& grid) {

    //increaments the word direction by dr and dc
    for (int i = 0; i < word.length(); i++) {
        grid[row + i*dr][col + i*dc] = word[i];
    }
}

//function that checks if a wrong word is detected in a direction
bool checkWWORDS(const vector<vector<char> >& grid, const string& word,
                 int row, int col, int dr, int dc){

    int ROW = grid.size();
    int COL = grid[0].size();
    bool found = false;

    //increament in a direction by dr and dc
    for (int i = 0; i < word.length(); i++) {
        if (row + i*dr < 0 || row + i*dr >= ROW ||
            col + i*dc < 0 || col + i*dc >= COL ||
            grid[row + i*dr][col + i*dc] != word[i]) {
            found = true;
            break;
        }
    }
    if (found) {
        return false;
    }

    return true;
}

// function that checks if a grid contains wrong words
bool is_correct(const vector<vector<char> >& grid, const vector<string>& wrong_words, int ROW, int COL) {
    for (int ww = 0; ww < wrong_words.size(); ww++) {
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {

                //in 8 possible direction
                if (checkWWORDS(grid, wrong_words[ww], row, col, 1, 0) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, 0, 1) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, -1, 0) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, 0, -1) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, 1, 1) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, -1, 1) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, -1, -1) ||
                    checkWWORDS(grid, wrong_words[ww], row, col, 1, -1)) {
                    return false;
                }
            }
        }
    }

    return true;
}

// fills a empty spot if not all position are used
void fill_grid(vector<vector<char> >& grid, int ROW, int COL,
               vector<vector<string> > &solutions, const vector<string>& wrong_words){

    bool isEmpty = false;
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            if (grid[row][col] == '.'){
                isEmpty = true;
            }
        }

    }

    //if grid is not empty and is correct pushback the grid
    if (!isEmpty && is_correct(grid, wrong_words, ROW, COL)){
        vector<string> t(ROW);
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++){
                t[row] += grid[row][col];
            }
        }

        //if grid is unique it will pushback
        if (find(solutions.begin(), solutions.end(), t) == solutions.end())
            solutions.push_back(t);

        return;
    }

    //it's not correct
    else if (isEmpty){
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {
                if (grid[row][col] == '.') {
                    for (char c = 'a'; c <= 'z'; c++) {
                        grid[row][col] = c;
                        if (is_correct(grid, wrong_words, ROW, COL))
                            fill_grid(grid, ROW, COL, solutions, wrong_words);

                        //backtrack
                        grid[row][col] = '.';
                    }
                }
            }
        }
    }
}

// create the grids recursively
void make_grid(int wi, vector<vector<char> > grid, const vector<string>& correct_words,
                    const vector<string>& wrong_words, vector<vector<string> > &solutions,
                    int ROW, int COL) {

    bool isEmpty = false;
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            if (grid[row][col] == '.'){
                isEmpty = true;
            }
        }
    }

    //base case if all correct words got put into the grid
    if (wi == correct_words.size()) {
        if (is_correct(grid, wrong_words, ROW, COL)) {
            if (isEmpty){
                fill_grid((grid), ROW, COL, solutions, wrong_words);
            }
            else {
                vector<string> t(ROW);
                for (int row = 0; row < ROW; row++) {
                    for (int col = 0; col < COL; col++){
                        t[row] += grid[row][col];
                    }
                }

                //if the grid is unique it will pushback
                if (find(solutions.begin(), solutions.end(), t) == solutions.end())
                    solutions.push_back(t);
            }
        }
    }
    else {
        string word = correct_words[wi];
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {

                //generate the grids in all 8 possible direction
                if (can_add(word, row, col, 1, 0, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, 1, 0,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, 0, 1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, 0, 1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, -1, 0, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, -1, 0,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, 0, -1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, 0, -1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, 1, 1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, 1, 1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, -1, 1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, -1, 1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, -1, -1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, -1, -1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
                if (can_add(word, row, col, 1, -1, grid, ROW, COL)) {
                    vector<vector<char> > tempG = grid;
                    add_word(word, row, col, 1, -1,tempG);
                    make_grid((wi+1), tempG, correct_words, wrong_words,solutions, ROW, COL);
                }
            }
        }

    }
}


int main(int argc, const char * argv[]){

    // argv files
    ifstream in_str(argv[1]);
    ofstream out_str(argv[2]);
    bool ALLS = false;
    string s3 = argv[3];
    if (s3 == "all_solutions"){
        ALLS = true;
    }

    if (!in_str.good()) {
        cerr << "Can't open " << argv[1] << " to write.\n";
        exit(1);
    }
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }

    vector<vector<string> > solutions; // List of valid grids

    string thing;
    vector<string> all;
    while (in_str >> thing){
        all.push_back(thing);
    }

    int row = stoi(all[0]);
    int col = stoi(all[1]);
    vector<vector<char> > grid(col, vector<char>(row, '.')); //grid

    bool pos = false;
    bool neg = false;
    vector <string> correct_words;
    vector <string> wrong_words;
    for (int i = 2; i < all.size(); i++){
        if (all[i] == "+"){
            pos = true;
            continue;
        }
        else if (all[i] == "-"){
            neg = true;
            continue;
        }
        else if (pos){
            correct_words.push_back(all[i]);
            pos = false;
        }
        else if (neg){
            wrong_words.push_back(all[i]);
            neg = false;
        }
    }

    make_grid(0, grid, correct_words, wrong_words, solutions, col, row);

    // Prints all solutions
    if (solutions.size() != 0){
        if (ALLS) {
            out_str << solutions.size() <<" solution(s)"<< endl;
            for (int i = 0; i < solutions.size(); i++) {
                out_str<<"Board:"<<endl;
                for (int j = 0; j < solutions[i].size(); j++) {
                    out_str <<"  "<< solutions[i][j] << endl;
                }
            }
        }

            // Prints First Solution
        else{
            out_str<< "Board:" <<endl;
            for (int col = 0; col < solutions[0].size(); col++) {
                out_str <<"  " << solutions[0][col] << endl;
            }
        }
    }
    else{
        out_str << "No solution found" << endl;
    }

    return 0;
}


