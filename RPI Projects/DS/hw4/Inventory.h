//
// Created by Jary Chen on 2/13/23.
//

#ifndef HW4_INVENTORY_H
#define HW4_INVENTORY_H
#include <iostream>
#include <string>
#include <list>
#include "Customers.h"

using namespace std;
class Inventory {
private:
    string id;
    string name;
    int quan;
    list<string> whorent;
    list<string> rentamount;
    list<string> whowait;
    list<string> waitamount;
public:

    //Constructor
    Inventory(const string& invID, int quantity, const string& invname){
        id = invID;
        quan = quantity;
        name = invname;
    }

    //getters
    const string& getID() const{
        return id;
    }
    const string& getName() const{
        return name;
    }
    int getQuan() const{
        return quan;
    }
    string printINV(list<Customers>& c);

    //setters
    void minusQuan(int n){
        quan-= n;
    }
    void plusQuan(int n){
        quan+=n;
    }
    void wrent(const string& personid, int quantity);
    void wwait(const string& periodid, int quantity);
    bool theyrent(int quanity);
    void delcust(int quantity, const string& personid);
    string whonext();
    int notwaiting(const string& personid);


};


#endif //HW4_INVENTORY_H
