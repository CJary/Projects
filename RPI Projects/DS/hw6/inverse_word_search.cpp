//
// Created by Jary Chen on 3/13/23.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

bool checkw(const vector<vector<char> >& grid, const string& word, int r, int c, int dr, int dc) {
    int maxR = grid.size();
    int maxC = grid[0].size();
    if (r < 0 || c < 0 || r + (word.size() - 1) * dr >= maxR || c + (word.size() - 1) * dc >= maxC) {
        return false;
    }

    if (grid[r][c] != word[0]) {
        return false;
    }

    for (int i = 1; i < word.size(); i++, r += dr, c += dc) {
        if (grid[r + dr][c + dc] != word[i]) {
            return false;
        }
    }
    return true;
}

bool checkno(const vector<vector<char> >& grid, const vector<string>& wwords){

    for (int ww = 0; ww < wwords.size(); ww++){

        for (int row = 0; row < grid.size(); row++){
            for (int col = 0; col < grid[0].size(); col++){
                if (checkw(grid, wwords[ww], row, col, 1, 0) ||
                    checkw(grid, wwords[ww], row, col, 0, 1) ||
                    checkw(grid, wwords[ww], row, col, -1, 0) ||
                    checkw(grid, wwords[ww], row, col, 0, -1) ||
                    checkw(grid, wwords[ww], row, col, 1, 1) ||
                    checkw(grid, wwords[ww], row, col, -1, 1) ||
                    checkw(grid, wwords[ww], row, col, -1, -1) ||
                    checkw(grid, wwords[ww], row, col, 1, -1)) {
                    return false;
                }
            }

        }

    }
    return true;
}

bool checkyes(const vector<vector<char> >& grid, const vector<string>& cwords, const set<char>& usedl){

    set<char> boardl;
    for (int r = 0; r < grid.size(); r++){
        for (int c = 0; c < grid[0].size(); c++){
            boardl.insert(grid[r][c]);
        }
    }
    if (boardl != usedl){
        return false;
    }

    for (int cw = 0; cw < cwords.size(); cw++){
        bool found = false;

        for (int row = 0; row < grid.size() && !found; row++){
            for (int col = 0; col < grid[0].size() && !found; col++){
                if (checkw(grid, cwords[cw], row, col, 1, 0) ||
                    checkw(grid, cwords[cw], row, col, 0, 1) ||
                    checkw(grid, cwords[cw], row, col, -1, 0) ||
                    checkw(grid, cwords[cw], row, col, 0, -1) ||
                    checkw(grid, cwords[cw], row, col, 1, 1) ||
                    checkw(grid, cwords[cw], row, col, -1, 1) ||
                    checkw(grid, cwords[cw], row, col, -1, -1) ||
                    checkw(grid, cwords[cw], row, col, 1, -1)) {
                    found = true;
                    break;
                }

            }
            if (found){
                break;
            }
        }
        if (!found) {
            return false;
        }

    }

    return true;
}

void make_grid(set<vector<vector<char> > >& solution_grids, vector<vector<char> >& grid,
               int row, int col, bool oneS, const vector<string>& cwords, const vector<string>& wwords,
               const set<char>& usedl){

    int gr = grid.size();
    int gc = grid[0].size();
    if (row == gr){

        if (checkyes(grid, cwords, usedl) && checkno(grid, wwords)){
            solution_grids.insert(grid);
            if (oneS){
                return;
            }
        }
        return;
    }

    if (col == gc){
        make_grid(solution_grids, grid, row + 1, 0, oneS, cwords, wwords, usedl);
        return;
    }

    //all used letters
    for (set<char>::iterator i = usedl.begin(); i!= usedl.end(); i++) {
        grid[row][col] = *i;
        make_grid(solution_grids, grid, row, col + 1, oneS, cwords, wwords, usedl);

        if (oneS && !solution_grids.empty()) {
            return;
        }
    }

}

int main(int argc, char *argv[]){
    ifstream in_str(argv[1]);
    if (!in_str.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }

    ofstream out_str(argv[2]);
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }

    string thing;
    vector<string> all;
    while (in_str >> thing){
        all.push_back(thing);
    }

    int row = stoi(all[0]);
    int col = stoi(all[1]);
    vector<vector<char> > grid(col, vector<char>(row)); //grid

    bool pos = false;
    bool neg = false;
    vector <string> correct_words;
    vector <string> wrong_words;
    vector<string> allwords;
    int longestw = 0;
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
            if (all[i].size() > longestw){
                longestw = all[i].size();
            }

            allwords.push_back(all[i]);
            pos = false;
        }
        else if (neg){
            if (!(all[i].size() == 1)){
                wrong_words.push_back(all[i]);
                allwords.push_back(all[i]);
            }
            neg = false;
        }
    }

//    for (int i = 0; i < wrong_words.size(); i++){
//        cout << wrong_words[i] << ' ';
//    }

    bool oneS = true;
    string s3 = argv[3];
    if (s3 == "all_solutions"){
        oneS = false;
    }

    //only track used letters
    set<char> used_let;
    for (int i = 0; i < allwords.size();i++){
        for (int l = 0; l < allwords[i].size(); l++){
            used_let.insert(allwords[i][l]);
        }
    }

    set<vector<vector<char> > > solution_grids;
    make_grid(solution_grids, grid, 0, 0, oneS,
              correct_words, wrong_words, used_let);

    //cout << solution_grids.size();
    if (solution_grids.size() != 1){
        out_str << solution_grids.size() << " solution(s)" << endl;
    }
    if (solution_grids.size() == 0){
        out_str << "No solutions found";
    }
    for (set<vector<vector<char> > >::iterator i = solution_grids.begin(); i != solution_grids.end(); i++) {
        out_str << "Board: " << endl;
        for (int r = 0; r < i->size(); r++) {
            out_str << "  ";

            for (int c = 0; c < (*i)[0].size(); c++) {
                out_str << (*i)[r][c];
            }
            out_str << endl;
        }
    }
    return 0;
}