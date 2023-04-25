//
// Created by Jary Chen on 4/10/23.
//

#include "ds_hashset.h"

using namespace std;

//HASH FUNCTION COPIED FROM LAB
class hash_string_obj {
public:
    unsigned int operator() ( const std::string& key ) const {
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        //
        //  This is a general-purpose, very good hash function for strings.
        unsigned int hash = 1315423911;
        for(unsigned int i = 0; i < key.length(); i++)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));

        return hash;
    }

};

//function to create the table
typedef ds_hashset<hash_string_obj> hash_set;
void makeTable(hash_set& table, const string& genome, int kmer){
    for (int i = 0; i <= genome.size() - kmer; i++){
        string tmp = genome.substr(i,kmer);
        table.insert(tmp, i);
    }
}

int main(){
    hash_set table;
    string genome;
    string thing;
    int kmer;
    int miss_match;

    while (cin >> thing){
        if (thing == "genome"){
            cin >> thing;
            ifstream in_str(thing);
            if (!in_str.good()) {
                std::cerr << "Can't open " << thing << " to read." << std::endl;
                exit(1);
            }

            while (in_str >> thing){
                genome += thing;
            }
        }
        else if (thing == "table_size"){
            cin >> thing;
            int tmp = stoi(thing);
            table.setSize(tmp);
        }
        else if (thing == "occupancy"){
            cin >> thing;
            float tmp = stof(thing);
            table.setOcc(tmp);
        }
        else if (thing == "kmer"){
            cin >> thing;
            kmer = stoi(thing);
            makeTable(table, genome, kmer);
        }
        else if (thing == "query"){
            cin >> thing;
            miss_match = stoi(thing);

            cin >> thing;
            int qSize = thing.size();

            cout << "Query: " << thing << endl;
            vector<int> tmp = table.getPos(thing.substr(0, kmer));
            bool yes = false;
            if (tmp.empty()){
                cout << "No Match" << endl;
            }
            else{
                // loops through each pos in the tmp
                for (int i = 0; i < tmp.size()
                && tmp[i] <= (genome.size() - qSize); i++){
                    string str2 = genome.substr(tmp[i], qSize);

                    //if the diff is less than or equal to it will print
                    if (diff(thing, str2) <= miss_match){
                        cout << tmp[i] << ' ' << diff(thing, str2) << ' ' << str2 << endl;
                        yes = true;
                    }
                }

                //if all the pos has a diff more than the required
                if (!yes){
                    cout << "No Match" << endl;
                }
            }

        }
        else if (thing == "quit"){
            break;
        }

        //random commend break
        else{
            break;
        }
    }


    return 0;
}

