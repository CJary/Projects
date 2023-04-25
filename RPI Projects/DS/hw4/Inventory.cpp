//
// Created by Jary Chen on 2/13/23.
//

#include "Inventory.h"
#include "Customers.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

void Inventory::wrent(const string &personid, int quantity) {
    list<string>::iterator wrenti; // whorent index
    if (whorent.empty()){
        whorent.push_back(personid);
    }
    else{
        bool init = false;
        for (wrenti = whorent.begin(); wrenti != whorent.end();wrenti++){
            if (*wrenti == personid){//checks if person was already renting
                init = true;
                break;
            }
        }

        if (init == false){
            wrenti = whorent.begin();
            for (int i = 0;i < whorent.size(); i++){
                if (*wrenti > personid){
                    whorent.insert(wrenti, personid);
                    break;
                }
                else if(i == whorent.size()-1){
                    whorent.push_back(personid);
                    break;
                }
                wrenti++;
            }

        }
    }
    for (int i = 0; i < quantity; i++){//push back the amount of person that rented it
        rentamount.push_back(personid);
    }

}


void Inventory::wwait(const string& personid, int quantity) {
    whowait.push_back(personid); //add to waiting list
    for (int i = 0; i < quantity; i++){
        waitamount.push_back(personid);//adds amount
    }
}


bool Inventory::theyrent(int quanity) {
    if (quan >= quanity){//if requested quantity is less than or equal to total
        return true;
    }
    else{
        return false;
    }
}

void Inventory::delcust(int quantity, const string &personid) {
    list<string>::iterator check;
    int totalamount = 0;
    for (check = rentamount.begin(); check!= rentamount.end();check++){
        if (*check == personid){ // total amount being rented
            totalamount++;
        }
    }

    list<string>::iterator rent = rentamount.begin();
    int q = 0;//amount requested to return
    while (rent!= rentamount.end()){
        if ((*rent == personid) && (q < quantity)){
            rent = rentamount.erase(rent);
            q++;
        }
        else{
            rent++;
        }
    }

    if (totalamount == q){ //if request equal total the person del from list of renters
        list<string>::iterator wrenti = whorent.begin();
        while (wrenti != whorent.end()){
            if (*wrenti == personid){
                wrenti = whorent.erase(wrenti);
            }
            else{
                wrenti++;
            }
        }
    }
}

string Inventory::whonext() {
    if (whowait.empty()){ //no one nexts
        return "empty";
    }
    else{
        //checks for next person if their request can be fullfilled
        int count = 0;
        list<string>::iterator pww;
        list<string>::iterator pwa;
        for (pww = whowait.begin(); pww!=whowait.end();pww++){
            for (pwa = waitamount.begin();pwa != waitamount.end();pwa++){
                if (*pww == *pwa){
                    count++;
                }
            }
            if (count <= quan){
                return *pww;
            }
            count = 0;
        }
    }

}

int Inventory::notwaiting(const string &personid) {
    //erase from the amount of waiting
    list<string>::iterator wait = waitamount.begin();
    int waitc = 0;
    while (wait!= waitamount.end()){
        if (*wait == personid){
            wait = waitamount.erase(wait);
            waitc++;
        }
        else{
            wait++;
        }
    }

    //erase from being in the lsit of waiters
    list<string>::iterator waiti = whowait.begin();
    while (waiti != whowait.end()){
        if (*waiti == personid){
            waiti = whowait.erase(waiti);
        }
        else{
            waiti++;
        }
    }
    return waitc;
}

string Inventory::printINV(list<Customers>& c) {
    string printout = "";
    list<string>::iterator pr;
    list<string>::iterator pra;
    list<Customers>::iterator custm;
    int count = 0;
    if (!whorent.empty()){// prints renting if not empty
        printout += "Rental Customers: ";
        for (pr = whorent.begin(); pr!=whorent.end();pr++){
            for (pra = rentamount.begin(); pra!=rentamount.end(); pra++){
                if(*pr == *pra){
                    count++;
                }
            }
            for (custm = c.begin();custm!=c.end();custm++){
                if (custm->getID()==*pr){
                    printout += *pr + ' ' + custm->getName() +" (" + to_string(count) + ") ";
                    break;
                }
            }
            count = 0;
        }
        printout += "\n";
    }
    if (!whowait.empty()){//prints pending if not empty
        list<string>::iterator pw;
        list<string>::iterator pwa;
        count = 0;
        printout += "Pending Customers: ";
        for (pw = whowait.begin(); pw!=whowait.end();pw++){
            for (pwa =waitamount.begin(); pwa!=waitamount.end(); pwa++){
                if(*pw == *pwa){
                    count++;
                }
            }
            for (custm = c.begin();custm!=c.end();custm++){
                if (custm->getID()==*pw){
                    printout +=*pw + ' ' + custm->getName() +" (" + to_string(count) + ") ";
                    break;
                }
            }
            count = 0;
        }
        printout += "\n";
    }
    printout += "\n";
    return printout;
}









