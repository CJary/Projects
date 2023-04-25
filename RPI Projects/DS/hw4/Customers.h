//
// Created by Jary Chen on 2/13/23.
//

#ifndef HW4_CUSTOMERS_H
#define HW4_CUSTOMERS_H
#include <iostream>
#include <string>
#include <list>
#include "Inventory.h"

using namespace std;
class Customers {
private:
    string id;
    string name;
    string time;
    list<string> irented;
    list<string> ramount;
    list<string> iwait;
    list<string> wamount;
public:

    //Constructor
    Customers(const string& cid, const string& t, const string& n){
        id = cid;
        time = t;
        name = n;
    }

    const string& getID() const{
        return id;
    }
    const string& getName() const{
        return name;
    }
    const string& getTime() const{
        return time;
    }
    string printCUS();

    //setters
    void irent(int quantity, const string& ITEM);
    void iwaiting(int quantity, const string& ITEM);
    void ireturn(int quantity, const string& ITEM);
    bool ihave(const string& ITEM);
    int imnotw(const string& ITEM);


};


#endif //HW4_CUSTOMERS_H
