//
// Created by Jary Chen on 4/10/23.
//

#ifndef ds_hashset_h_
#define ds_hashset_h_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

template < typename HashFunc >
class ds_hashset {
private:
    // =================================================================
    // HASH SET REPRESENTATION
    vector<pair<string, vector<int> > > m_table;  // actual table
    HashFunc m_hash;                            // hash function
    int m_size;                                 // number of keys
    float occupancy;

public:
    // =================================================================
    // HASH SET IMPLEMENTATION
    ds_hashset(unsigned int init_size = 100, float og_Occ = 0.5) :
            m_table(init_size), m_size(0), occupancy(og_Occ){}

    // Copy constructor just uses the member function copy constructors.
    ds_hashset(HashFunc& old)
            : m_table(old.m_table), m_size(old.m_size), occupancy(old.occupancy) {}

    ~ds_hashset() {}

    ds_hashset& operator=(HashFunc& old) {
        if (&old != this) {
            this->m_table = old.m_table;
            this->m_size = old.m_size;
            this->m_hash = old.m_hash;
            this->occupancy = old.occupancy;
        }
        return *this;
    }

    //getters
    int getSize() const {
        return m_size;
    }
    float getOcc() const{
        return occupancy;
    }

    //setters
    void setSize(int i){
        m_size = i;
    }
    void setOcc(float f){
        occupancy = f;
    }

    //member function
    void insert(const string& key, int pos);
    vector<int> getPos(const string& str);
    void resize_table(int new_size);

};

//insert
template<typename HashFunc>
void ds_hashset<HashFunc>::insert(const string &key, int pos) {
    // Resize the hash table if the occupancy exceeds a certain threshold
    float occ = this->getSize()/m_table.size();
    if (occ > this->getOcc()){
        this->resize_table(2 * m_table.size());
    }

    // Compute the hash index for the key and find the corresponding bucket
    int hash_index = m_hash(key) % m_table.size();
    if (m_table[hash_index].first.size() == 0){
        // If the bucket is empty, add a new key-value pair to it
        vector<int> second;
        second.push_back(pos);
        m_table[hash_index] = make_pair(key, second);
        m_size++;
        return;
    }
    else{
        //if that index is a duplicate add pos to vector
        if (m_table[hash_index].first == key){
            m_table[hash_index].second.push_back(pos);
            return;
        }
        else{
            //linear probing to search for empty spots
            for (int i = 0; i < m_table.size(); i++){
                if (m_table[i].first.size() == 0){
                    vector<int> second;
                    second.push_back(pos);
                    m_table[i] = make_pair(key, second);
                    m_size++;
                    return;
                }

                //checks if the index is duplicate
                else if (m_table[i].first == key){
                    m_table[i].second.push_back(pos);
                    return;
                }
            }
        }
    }

    return;
}


//return pos in the genome
template<typename HashFunc>
vector<int> ds_hashset<HashFunc>::getPos(const string &str) {

    //calculate hash_index
    int hash_index = m_hash(str) % m_table.size();
    if (m_table[hash_index].first == str){
        return m_table[hash_index].second;
    }
    else{

        //loop through all index of the vector to check
        for (int i = 0; i < m_table.size(); i++){
            if (m_table[i].first == str){
                return m_table[i].second;
            }
        }

    }

    //nothing get return means no such str in the vector
    return vector<int>();
}


//resize function
template<typename HashFunc>
void ds_hashset<HashFunc>::resize_table(int new_size) {
    //base case if the table is empty
    if (m_table.size() == 0){
        return;
    }

    //create a new table with the new size
    vector<pair<string, vector<int> > > new_table(new_size);

    //loop through each element in the original vector
    for (int x = 0; x < m_table.size(); x++){
        if (m_table[x].first.size() != 0){
            string key = m_table[x].first;

            int hash_index = m_hash(key) % new_table.size();

            if (new_table[hash_index].first.size() == 0){
                new_table[hash_index] = m_table[x];
            }
            else{
                for (int y = 0; y < new_table.size(); y++){
                    if (new_table[y].first.size() == 0){
                        new_table[y] = m_table[x];
                        break;
                    }
                }
            }
        }
    }

    //make the old table become the new one
    this->m_table = new_table;
}


//none member function that calculates the difference between two strings
int diff(const string& str1, const string& str2){

    //base case if string different size
    if (str1.size() != str2.size()){
        return 0;
    }

    int count = 0;
    for (int i = 0; i < str1.size(); i++){
        if (str1[i] != str2[i]){
            count++;
        }
    }
    return count;
}


#endif //HW9_DS_HASHSET_H
