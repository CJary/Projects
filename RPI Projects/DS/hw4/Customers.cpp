//
// Created by Jary Chen on 2/13/23.
//

#include "Inventory.h"
#include "Customers.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

void Customers::irent(int quantity, const string &ITEM) {
    list<string>::iterator irenti; // rent index
    if (irented.empty()){
        irented.push_back(ITEM);
    }
    else{
        bool init = false;
        for (irenti = irented.begin(); irenti != irented.end(); irenti++){
            if (*irenti == ITEM){//checks if person already renting that item
                init = true;
                break;
            }
        }
        if (init == false){
            irenti = irented.begin();
            for (int i = 0;i < irented.size(); i++){
                if (*irenti > ITEM){
                    irented.insert(irenti, ITEM);
                    break;
                }
                else if (i == irented.size()-1){
                    irented.push_back(ITEM);
                    break;
                }
                irenti++;
            }
        }
    }
    for (int i = 0; i < quantity; i++){//adds the amount of item being rented
        ramount.push_back(ITEM);
    }
}


void Customers::iwaiting(int quantity, const string &ITEM) {
    list<string>::iterator iwaiti; // rent index
    if (iwait.empty()){
        iwait.push_back(ITEM);
    }
    else{
        //sorts
        iwaiti = iwait.begin();
        for (int i = 0;i < iwait.size(); i++){
            if (*iwaiti < ITEM){
                iwait.insert(iwaiti, ITEM);
                break;
            }
            else if(i == iwait.size()-1){
                iwait.push_back(ITEM);
                break;
            }
            iwaiti++;
        }
    }

    for (int i = 0; i < quantity; i++){//adds the amount of items person is waiting for
        wamount.push_back(ITEM);
    }
}


void Customers::ireturn(int quantity, const string &ITEM) {
    list<string>::iterator check;
    int totalamount = 0;
    for (check = ramount.begin(); check!= ramount.end();check++){
        if (*check == ITEM){//total amount of items being return
            totalamount++;
        }
    }

    list<string>::iterator ramoni = ramount.begin();
    int q = 0;
    while (ramoni != ramount.end()){
        if ((*ramoni == ITEM) && (q < quantity)){
            ramoni = ramount.erase(ramoni);
            q++;
        }
        else{
            ramoni++;
        }
    }

    if (totalamount == q){//if amount being return is equal to total amount erase iteam from irent
        list<string>::iterator irenti = irented.begin();
        while (irenti != irented.end()){
            if (*irenti == ITEM){
                irenti = irented.erase(irenti);
            }
            else{
                irenti++;
            }
        }
    }
}

bool Customers::ihave(const string &ITEM) { //checks if person is even renting that item
    list<string>::iterator ihavei;
    for (ihavei = irented.begin(); ihavei != irented.end(); ihavei++){
        if (*ihavei == ITEM){
            return true;
        }
    }
    return false;
}

int Customers::imnotw(const string &ITEM) { //erase item from being rented
    list<string>::iterator w = wamount.begin();
    int waitc = 0;
    while (w!= wamount.end()){
        if (*w == ITEM){
            w = wamount.erase(w);
            waitc++;
        }
        else{
            w++;
        }
    }

    list<string>::iterator iw = iwait.begin();
    while (iw != iwait.end()){
        if (*iw== ITEM){
            iw = iwait.erase(iw);
        }
        else{
            iw++;
        }
    }
    return waitc;
}

string Customers::printCUS() {
    string printout = "";
    list<string>::iterator pr;
    list<string>::iterator pra;
    int count = 0;
    if (!irented.empty()){ //prints out rentals if not empty
        printout += id + ' ' + name;
        printout += "\nRentals: ";
        for (pr = irented.begin(); pr!=irented.end();pr++){
            for (pra = ramount.begin(); pra!=ramount.end(); pra++){
                if(*pr == *pra){
                    count++;
                }
            }
            printout +=*pr+" (" + to_string(count) + ") ";
            count = 0;
        }
        printout += "\n\n";

    }
    if (!iwait.empty()){//prints out pending if not empty
        list<string>::iterator pw;
        list<string>::iterator pwa;
        count = 0;
        printout += id + ' ' + name;
        printout += "\nPending: ";
        for (pw = iwait.begin(); pw!=iwait.end();pw++){
            for (pwa =wamount.begin(); pwa!=wamount.end(); pwa++){
                if(*pw == *pwa){
                    count++;
                }
            }
            printout +=*pw+" (" + to_string(count) + ") ";
            count = 0;
        }
        printout += "\n\n";
    }
    return printout;
}




