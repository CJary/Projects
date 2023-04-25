//
// Created by Jary Chen on 1/14/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//function that returns the top/bot lines
string printline(int num){
    string line;
    for (int i = 0; i < num; i++){
        line += '-';
    }
    return line;
}

//function that returns the text that is flushleft
string flushleft(int width, string file){
    ifstream in_str(file);
    string output;
    output += printline(width + 4) + "\n"; // outputs the '-' on the top

    string word;
    int lenwords = 0;
    string textline;
    while (in_str >> word){
        // if the next word and the current word is larger than the width
        // it will print the rest of the spaces
        if (lenwords + word.size() > width){
            for (int i = 0; i <= width - lenwords; i++){
                output += ' ';
            }
            output += "|\n";
            lenwords = 0;
        }
        if (lenwords == 0){ // if the lenwords is 0 it means that the sentence ends
            output += "| ";
        }

        lenwords += word.size() + 1; // updates the amount of characters on the line
        output += word + ' '; // outputs words first
    }
    // for the last line
    for (int i = 0; i <= width - lenwords; i++){
        output += ' ';
    }
    output += "|\n";

    output += printline(width + 4); // outputs the '-' on the bottom

    return output;
}

//function that returns the text that is flushright
string flushright(int width, string file){
    ifstream in_str(file);
    string output;
    output += printline(width + 4) + "\n";

    string word;
    int lenwords = 0;
    string textline;
    while (in_str >> word){
        // if the amount of characters on the line + the next word is more
        // than the width it will stop print the spaces first
        if (lenwords + word.size() > width){
            for (int i = 0; i <= width - lenwords; i++){
                output += ' '; // outputs spaces first
            }
            output += ' ' + textline + '|' + "\n";
            lenwords = 0;
            textline.clear();

        }
        if (lenwords == 0){ // if lenwords is 0 the line ends
            output += "|";
        }

        lenwords += word.size() + 1;
        textline += word + ' ';
    }
    // for last line
    for (int i = 0; i <= width - lenwords; i += 1){
        output += ' ';
    }
    output += ' ' + textline + '|' + "\n";
    lenwords = 0;
    textline.clear();

    output += printline(width + 4); // outputs the bottom '-' lines

    return output;
}

//function that returns the text that is fulljustify
string fulljustify(int width, string file){
    ifstream in_str(file);
    string output;
    output += printline(width + 4) + "\n";

    string word;
    int lenwords = 0;
    int wordcount = 0;
    vector <string> linelist; // vector of the words on the current line
    while (in_str >> word){
        // if the words on the line and the next word is too long
        if ((lenwords + word.size() > width) & (word.size() < width)){
            int spacescount;
            spacescount = width - lenwords + wordcount; // extra spaces
            int slots = wordcount - 1;

            // if the spacescount can be divided evenly
            if ((spacescount % (wordcount - 1) == 0) and (wordcount != 1)){
                string spaces;
                spacescount = spacescount/slots;
                for (int i = 0; i < spacescount; i++){ // amount of spaces between each word
                    spaces += ' ';
                }

                output += "| ";
                for (int i = 0; i < linelist.size(); i++){
                    if (i < slots){
                        output += linelist[i] + spaces;
                    }
                    else{
                        output += linelist[i] + " |\n";
                    }
                }
                lenwords = 0;
                linelist.clear();
                wordcount = 0;
            }

            else{ // if it can't be divided evenly
                output += "| ";
                while (spacescount >= 1){ // keeps giving spaces to each word until there is no spaces
                    for (int i = 0; i < slots; i++){
                        if (spacescount >= 1){
                            linelist[i] += ' ';
                            spacescount--;
                        }
                    }
                }
                for (int i =0; i< linelist.size(); i++){ // outputs the last few words
                    output += linelist[i];
                }
                output += " |\n";
                lenwords = 0;
                linelist.clear();
                wordcount = 0;
            }

        }

        // updates each words on each line
        lenwords += word.size() + 1;
        linelist.push_back(word);
        wordcount += 1;

        // if the current word is too long
        if (word.size() > width){
            // if there are mutiple on the line, repeat full justify
            if (linelist.size() > 1){
                // repeat of full justify but with finalline instead of linelist
                vector <string> finalline;
                lenwords = 0;
                wordcount = 0;

                for (int i = 0; i < (linelist.size() - 1); i++){
                    finalline.push_back(linelist[i]);
                    lenwords += (linelist[i].size() + 1);
                    wordcount += 1;
                }

                int spacescount;
                spacescount = width - lenwords + wordcount;
                int slots = wordcount;
                if ((spacescount % (wordcount) == 0) and (wordcount != 1)){
                    string spaces;
                    spacescount = spacescount/slots;
                    for (int i = 0; i < spacescount; i++){
                        spaces += ' ';
                    }

                    output += "| ";
                    for (int i = 0; i < finalline.size(); i++){
                        if (i < slots){
                            output += finalline[i] + spaces;
                        }
                        else{
                            output += finalline[i] + " |\n";
                        }
                    }
                    lenwords = 0;
                    finalline.clear();
                    wordcount = 0;
                }

                else{
                    output += "| ";
                    while (spacescount >= 1){
                        for (int i = 0; i < slots; i++){
                            if (spacescount >= 1){
                                finalline[i] += ' ';
                                spacescount--;
                            }
                        }
                    }
                    for (int i =0; i< finalline.size(); i++){
                        output += finalline[i];
                    }
                    output += " |\n";
                    lenwords = 0;
                    finalline.clear();
                    wordcount = 0;
                }

            }

            // outputs the long word
            string longword = word;
            while (longword.size() > width){
                output += "| " + longword.substr(0, width - 1) + "- |\n";
                longword = longword.substr(width - 1);
            }

            linelist.clear();
            linelist.push_back(longword);
            lenwords = longword.size() + 1;
        }
    }
    // last few words with flush left
    output += "| ";
    for (int i = 0; i < linelist.size(); i++){
        output += linelist[i] + ' ';
        }
    for (int i = 0; i <= (width - lenwords); i++){
        output += ' ';
        }

    output += "|\n";

    output += printline(width + 4);

    return output;
}

//main body of the code
int main(int argc, char* argv[]){
    string f = argv[1];
    ifstream in_str(f);
    int width = stoi(argv[3]); // transformed the string version of the int to a actual int
    string flush_t = argv[4];

    if (!in_str.good()) {
        std::cerr << "Can't open " << f << " to read.\n";
        exit(1);
    }

    ofstream out_str(argv[2]);
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }

    if (flush_t == "flush_left"){
        out_str << flushleft(width, f) << endl;
    }
    else if (flush_t == "flush_right"){
        out_str << flushright(width, f) << endl;
    }
    else if (flush_t == "full_justify"){
        out_str << fulljustify(width, f) << endl;
    }
    return 0;
}