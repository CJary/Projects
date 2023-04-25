#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "team.h"
#include "player.h"

using namespace std;
int main(int argc, char *argv[]){
    string stats = argv[3]; // team, player, or custom
    string file = argv[1]; // in stream file
    ifstream in_str(file);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[3] << " to read.\n";
        exit(1);
    }

    ofstream out_str(argv[2]); // out stream file
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }

    // vector containing all the words of the file
    string word;
    vector <string> allwords;
    while (in_str >> word){
        allwords.push_back(word);
    }


    vector <team> teams;
    vector <player> players;
    vector <string> assistsp; // vector containing players that assisted
    vector <string> pentype; // vector containing penalty types
    int t1i; // team 1 index
    int t2i; // team 2 index
    int pi; // player index
    for (int i = 0; i < allwords.size(); i++){

        // at and vs. are keywords to record the teams objects
        if ((allwords[i] == "at") or (allwords[i] == "vs.")){
            team t1(allwords[i-1]);
            team t2(allwords[i+1]);
            bool t1p = true;
            bool t2p = true;

            //checks if the team object are already made
            for (int ii = 0; ii < teams.size(); ii++){
                if (teams[ii].gettname() == allwords[i-1]){
                    t1p = false;
                    t1i = ii; // keeps track of the index of the team
                }
                if (teams[ii].gettname() == allwords[i+1]){
                    t2p = false;
                    t2i = ii;
                }
            }

            // if not made it adds to team vector
            if (t1p == true){
                t1i = teams.size();
                teams.push_back(t1);
            }
            if (t2p == true){
                t2i = teams.size();
                teams.push_back(t2);
            }
            teams[t1i].game1();
            teams[t2i].game1();
        }

        // keyword penalty
        if (allwords[i] == "penalty"){
            if (allwords[i-1] == teams[t1i].gettname()){
                teams[t1i].penalty1();
            }
            else if (allwords[i-1] == teams[t2i].gettname()){
                teams[t2i].penalty1();
            }

            // checks if the penaltized player is already created
            player p(allwords[i+1], allwords[i-1]);
            bool pp = true;
            for (int ii = 0; ii < players.size(); ii++){
                if ((players[ii].getpname() == allwords[i+1]) && (allwords[i+1] != "BENCH")){
                    pp = false;
                    pi = ii;
                }
            }

            if ((pp == true) && (allwords[i+1] != "BENCH")){
                pi = players.size();
                players.push_back(p);
            }
            if (allwords[i+1] != "BENCH"){
                players[pi].penalty1();
                pentype.push_back(allwords[i+3]);
            }
        }

        // keyword goal
        if (allwords[i] == "goal"){
            if (allwords[i-1] == teams[t1i].gettname()){
                teams[t1i].goal1();
            }
            else if (allwords[i-1] == teams[t2i].gettname()){
                teams[t2i].goal1();
            }

            // checks if the player that scored is already created
            player p(allwords[i+1], allwords[i-1]);
            bool pp = true;
            for (int ii = 0; ii < players.size(); ii++){
                if (players[ii].getpname() == allwords[i+1]){
                    pp = false;
                    pi = ii;
                }
            }

            if (pp == true){
                pi = players.size();
                players.push_back(p);
            }
            players[pi].goal1();
        }

        // keyword (
        if (allwords[i] == "("){

            // loops everything in between ( to )
            for (int ia = (i + 1); ia < allwords.size(); ia++){
                if (allwords[ia] == ")"){
                    break;
                }
                else{
                    assistsp.push_back(allwords[ia]);
                }
            }

            // checks if the players that assisted are created
            for (int ix = 0; ix < assistsp.size(); ix++){
                player p(assistsp[ix], allwords[i-3]);
                bool pp = true;
                for (int ii = 0; ii < players.size(); ii++){
                    if (players[ii].getpname() == assistsp[ix]){
                        pp = false;
                        pi = ii;
                    }
                }

                if (pp == true){
                    pi = players.size();
                    players.push_back(p);
                }
                players[pi].assist1();
            }
            assistsp.clear();
        }

        // keyword FINAL
        if (allwords[i] == "FINAL"){
            int x = stoi(allwords[i+2]);
            int y = stoi(allwords[i+4]);

            if (x > y){
                teams[t1i].win1();
                teams[t2i].lose1();
            }
            else if (x < y){
                teams[t2i].win1();
                teams[t1i].lose1();
            }
            else if (x == y){
                teams[t1i].tied1();
                teams[t2i].tied1();
            }
        }


    }

    sort(teams.begin(), teams.end(), strongestt);
    vector <int> hightname; // checks the highest size of a team name for formatting
    for (int i = 0; i < teams.size(); i++){
        hightname.push_back(teams[i].gettname().size());
    }
    int maxt = *max_element(hightname.begin(), hightname.end());

    sort(players.begin(), players.end(), strongestp);
    vector <int> highpname; // checks the highest size of a player name for formatting
    for (int i = 0; i < players.size(); i++){
        highpname.push_back(players[i].getpname().size());
    }
    int maxp = *max_element(highpname.begin(), highpname.end());

    if (stats == "--team_stats"){

        // formatting
        out_str << setw(maxt+4) << left << "Team Name";
        out_str << right << "W";
        out_str << setw(4) << right << "L";
        out_str << setw(4) << right << "T";
        out_str << setw(7) << right << "Win%";
        out_str << setw(7) << right << "Goals";
        out_str << setw(11) << right << "Penalties" << "\n";
        for (int i = 0; i < teams.size(); i++){
            out_str << setw(maxt+4) << left << teams[i].gettname();
            out_str << right << teams[i].getwins();
            out_str << setw(4) << right << teams[i].getloses();
            out_str << setw(4) << right << teams[i].getties();
            out_str << setw(7) << right << fixed << setprecision(2) << teams[i].getwinP();
            out_str << setw(7) << right << teams[i].getgoals();
            out_str << setw(11) << right << teams[i].getpenalty() << "\n";
        }
    }

    if (stats == "--player_stats"){

        //formatting
        out_str << setw(maxp+2) << left << "Player Name";
        out_str << setw(maxt+3) << left << "Team";
        out_str << right << "Goals";
        out_str << setw(9) << right << "Assists";
        out_str << setw(11) << right << "Penalties" << "\n";
        for (int i = 0; i < players.size(); i++){
            out_str << setw(maxp+2) << left << players[i].getpname();
            out_str << setw(maxt+7) << left << players[i].gettname();
            out_str << right << players[i].getgoals();
            out_str << setw(9) << right << players[i].getassists();
            out_str << setw(11) << right << players[i].getpenalty() << "\n";
        }
    }

    if (stats == "--custom_stats"){

        // sorts teams and players by weakest
        sort(players.begin(), players.end(), weakestp);
        sort(teams.begin(), teams.end(), weakestt);

        // calculates each teams highest penalty player
        vector <player> penplayers;
        for (int i = 0; i < teams.size(); i++){
            for (int ii = 0; ii < players.size(); ii++){
                if (teams[i].gettname() == players[ii].gettname()){
                    penplayers.push_back(players[ii]);
                    break;
                }
            }
        }

        // formatting
        out_str << setw(maxt+5) << left << "Team Name";
        out_str << right << "W";
        out_str << setw(10) << right << "L";
        out_str << setw(10) << right << "T";
        out_str << setw(10) << right << "Win%";
        out_str << setw(10) << right << "Pen%";
        out_str << setw(10) << right << "Goals";
        out_str << setw(12) << right << "Penalties";
        out_str << setw(maxp) << right << "Player Name";
        out_str << setw(11) << right << "Penalties" << "\n";
        for (int i = 0; i < teams.size(); i++){
            out_str << setw(maxt+5) << left << teams[i].gettname();
            out_str << right << teams[i].getwins();
            out_str << setw(10) << right << teams[i].getloses();
            out_str << setw(10) << right << teams[i].getties();
            out_str << setw(10) << right << fixed << setprecision(2) << teams[i].getwinP(); // round 2nd place
            out_str << setw(10) << right << fixed << setprecision(2) << teams[i].getpenP();
            out_str << setw(10) << right << teams[i].getgoals();
            out_str << setw(12) << right << teams[i].getpenalty();
            out_str << setw(maxp) << right << players[i].getpname();
            out_str << setw(11) << right << players[i].getpenalty() << "\n";
        }

        // find the penalty type that occurs the most
        int maxc = 0;
        string pen;
        for (int i = 0; i < pentype.size(); i++){
            int c = 0;
            for (int ii = 0; ii < pentype.size(); ii++){
                if (pentype[i] == pentype[ii]){
                    c++;
                }
            }

            if (c > maxc){
                maxc = c;
                pen = pentype[i];
            }
        }
        if (pen.size() > 0){
            out_str << "The most common penalty type is >>" << pen << "<<.";
        }
        else{
            out_str << "These matches players played perfect no penalty";
        }

    }

    return 0;
}
