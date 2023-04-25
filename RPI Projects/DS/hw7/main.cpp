//
// Created by Jary Chen on 3/19/23.
//


#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

#include "Fighter.h"
using namespace std;
int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << endl;
		return -1;
	}
	ifstream dbfile(argv[1]);
	if(!dbfile){
		cerr << "Failed to open database " << argv[1] << " for reading." << endl;
	}
	ifstream infile(argv[2]);
	if(!infile){
		cerr << "Failed to open input " << argv[2] << " for reading." << endl;
	}
	ofstream outfile(argv[3]);
	if(!outfile){
		cerr << "Failed to open output " << argv[3] << " for writing." << endl;
	}

	///////Fill in the rest of main below:
	//main maps
	map<string, Fighter> characters; //map that holds a character name and object

    //move's name as key value is another map with key as frames
    //nested map's value is a set of all the player with that frame
    map<string, map<int, set<string> > > MOVES;
    MOVES["jab"];
    MOVES["forward-tilt"];
    MOVES["up-tilt"];
    MOVES["down-tilt"];
    MOVES["forward-smash"];
    MOVES["up-smash"];
    MOVES["down-smash"];

    //formatting for the database
    string db;
    string cname;
    string a,b,c,d,e,f,g,h;
    dbfile >> a >> b >> c >> d >> e >> f >> g >>h; //to get rid of the formatting on top
    while (dbfile >> db){
        cname = db;
        Fighter player(db);
        characters[cname] = player;

        dbfile >> db; //jab
        int tmp = stoi(db);
        characters.find(cname)->second.setFrame("jab", tmp);
        if (MOVES.find("jab")->second.find(tmp) != MOVES.find("jab")->second.end()){
            MOVES.find("jab")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("jab")->second[tmp].insert(cname);
        }

        dbfile >> db; // forward-tilt
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("forward-tilt", tmp);
        if (MOVES.find("forward-tilt")->second.find(tmp) != MOVES.find("forward-tilt")->second.end()){
            MOVES.find("forward-tilt")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("forward-tilt")->second[tmp].insert(cname);
        }

        dbfile >> db; //up-tilt
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("up-tilt", tmp);
        if (MOVES.find("up-tilt")->second.find(tmp) != MOVES.find("up-tilt")->second.end()){
            MOVES.find("up-tilt")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("up-tilt")->second[tmp].insert(cname);
        }

        dbfile >> db; //down-tilt
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("down-tilt", tmp);
        if (MOVES.find("down-tilt")->second.find(tmp) != MOVES.find("down-tilt")->second.end()){
            MOVES.find("down-tilt")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("down-tilt")->second[tmp].insert(cname);
        }

        dbfile >> db; //forward-smash
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("forward-smash", tmp);
        if (MOVES.find("forward-smash")->second.find(tmp) != MOVES.find("forward-smash")->second.end()){
            MOVES.find("forward-smash")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("forward-smash")->second[tmp].insert(cname);
        }

        dbfile >> db; //up-smash
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("up-smash", tmp);
        if (MOVES.find("up-smash")->second.find(tmp) != MOVES.find("up-smash")->second.end()){
            MOVES.find("up-smash")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("up-smash")->second[tmp].insert(cname);
        }

        dbfile >> db; //down-smash
        tmp = stoi(db);
        characters.find(cname)->second.setFrame("down-smash", tmp);
        if (MOVES.find("down-smash")->second.find(tmp) != MOVES.find("down-smash")->second.end()){
            MOVES.find("down-smash")->second.find(tmp)->second.insert(cname);
        }
        else{
            MOVES.find("down-smash")->second[tmp].insert(cname);
        }
    }


    //formatting for the input file
    string command;
    while (infile >> command){
        string b, c;
        infile >> b >> c;

        if (command == "-q"){ //q
            if (characters.find(b) != characters.end()){
                if (MOVES.find(c) != MOVES.end() || c == "all"){
                    if (c == "all"){
                        outfile << b << " down-smash: " << characters.find(b)->second.getFrame("down-smash") << endl;
                        outfile << b << " down-tilt: " << characters.find(b)->second.getFrame("down-tilt") << endl;
                        outfile << b << " forward-smash: " << characters.find(b)->second.getFrame("forward-smash") << endl;
                        outfile << b << " forward-tilt: " << characters.find(b)->second.getFrame("forward-tilt") << endl;
                        outfile << b << " jab: " << characters.find(b)->second.getFrame("jab") << endl;
                        outfile << b << " up-smash: " << characters.find(b)->second.getFrame("up-smash") << endl;
                        outfile << b << " up-tilt: " << characters.find(b)->second.getFrame("up-tilt") << endl;
                    }
                    else{ //if not all
                        outfile << b << ' ' << c << ": " << characters.find(b)->second.getFrame(c) << endl;
                    }
                }
                else{
                    outfile << "Invalid move name: " << c << endl;
                }
            }
            else{
                outfile << "Invalid character name: " << b << endl;
            }

            outfile << endl;
        }

        else if (command == "-f"){ //fastest
            if (MOVES.find(b) != MOVES.end()){
                outfile << "-f " << b << ' ' << c << endl;

                int tmp = 0;
                bool finish = false;

                if (stoi(c) != 0){
                    map<int, set<string> >::iterator i = MOVES.find(b)->second.begin();
                    for (; i != MOVES.find(b)->second.end(); i++){
                        for (set<string>::iterator p = i->second.begin(); p != i->second.end(); p++){
                            outfile << *p << ' ' << i->first << endl;
                            tmp++;

                            //if limit is reached break
                            if (tmp == stoi(c)){
                                finish = true;
                                break;
                            }
                        }
                        if (finish){
                            break;
                        }
                    }
                }

            }
            else{
                outfile << "Invalid move name: " << b << endl;
            }

            outfile << endl;
        }

        else if (command == "-s"){ //slowest
            if (MOVES.find(b) != MOVES.end()){
                outfile << "-s " << b << ' ' << c << endl;
                int tmp = 0;
                bool finish = false;

                //loop backwards because of set ordering
                map<int, set<string> >::reverse_iterator i = MOVES.find(b)->second.rbegin();
                for (; i != MOVES.find(b)->second.rend(); i++){
                    for (set<string>::iterator p = i->second.begin(); p != i->second.end(); p++){
                        outfile << *p << ' ' << i->first << endl;
                        tmp++;

                        //if limit is reached break
                        if (tmp == stoi(c)){
                            finish = true;
                            break;
                        }
                    }
                    if (finish){
                        break;
                    }
                }
            }
            else{
                outfile << "Invalid move name: " << b << endl;
            }

            outfile << endl;
        }

        else if (command == "-d"){ //d
            if (MOVES.find(b) != MOVES.end()){
                outfile << "-d " << b << ' ' << c << endl;

                set<string>::iterator i = MOVES.find(b)->second.find(stoi(c))->second.begin();
                for (;i != MOVES.find(b)->second.find(stoi(c))->second.end(); i++){
                    outfile << *i << endl;
                }
            }
            else{
                outfile << "Invalid move name: " << b << endl;
            }

            outfile << endl;
        }

    }

	return 0;
}
