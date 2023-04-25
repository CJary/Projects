//
// Created by Jary Chen on 2/13/23.
//

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "Inventory.h"
#include "Customers.h"

using namespace std;
int main(int argc, char *argv[]) {
    ifstream in_str(argv[1]);
    if (!in_str.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }

    //List of Object Inventory
    list <Inventory> invlist;
    list <Customers> cuslist;

    string words;
    string iid;
    bool ID = false;
    bool QUAN = false;
    string INVid = "";
    int INVq = 0;
    string INVname = "";
    list<Inventory>::iterator iiv;
    while (in_str >> words) {
        if ((words[0] == 'T') && (ID == false)){ //checks if first word of that sentence is ID
            INVid = words;
            ID = true;
        }
        else if (QUAN == false && ID){ // if id is false skip
            if (atoi(words.c_str()) > 0){
                INVq = stoi(words);
                QUAN = true;
            }
        }
        else if (ID && QUAN){ // if id is false skip
            INVname = words;
            Inventory item(INVid, INVq, INVname);
            if (invlist.empty()){
                invlist.push_back(item);
            }
            else{
                //sorts
                iiv = invlist.begin();
                for (int i = 0;i < invlist.size(); i++){
                    if (item.getID() < iiv->getID()){
                        invlist.insert(iiv, item);
                        break;
                    }

                    else if(i == invlist.size()-1){
                        invlist.push_back(item);
                        break;
                    }
                    iiv++;
                }
                /*
                if (flag == false){
                    invlist.push_back(item);
                }*/
            }
            //resets
            ID = false;
            QUAN = false;
            INVid = "";
            INVq = 0;
            INVname = "";
        }
        else if (!ID && !QUAN){ // if id is false cerr error
            cerr << "Invalid inventory ID " << words <<" found in the inventory file." << endl;
            string a, b;
            in_str >> a >> b;
        }
    }

    ifstream in_str2(argv[2]);
    if (!in_str2.good()) {
        cerr << "Can't open " << argv[2] << " to read.\n";
        exit(1);
    }
    string words2;
    bool cID = false;
    bool rent = false;
    bool giveb = false;
    bool time = false;
    int count = 0;
    string itemid = "temp";
    string cusid = "";
    string custime = "";
    string cusname = "";
    while (in_str2 >> words2){
        if ((words2[0] == 'C') && (cID == false)){ //checks if first word of that sentence is ID
            cusid = words2;
            cID = true;
        }
        else if (words2 == "rent" && cID){// if id is false skip
            rent = true;
        }
        else if (words2 == "return" && cID){// if id is false skip
            giveb = true;
        }
        else if (time == false && cID){// if id is false skip
            custime = words2;
            time = true;
        }
        else if (count == 0 && cID){// if id is false skip
            if (atoi(words2.c_str())){
                count = stoi(words2);
            }
        }
        else if (itemid == "temp" && cID){// if id is false skip
            itemid = words2;
        }
        else if (cID == true){// if id is false skip
            cusname = words2;
            Customers cust(cusid, custime, cusname);
            list<Customers>::iterator Ccheckid;
            list<Inventory>::iterator Icheckid;

            if (cuslist.empty()){
                cuslist.push_back(cust);
                Ccheckid = cuslist.begin();
            }
            else{
                //sorts
                bool idin = false;
                Ccheckid = cuslist.begin();
                for (; Ccheckid != cuslist.end(); Ccheckid++){
                    if (Ccheckid->getID() == cusid){ //checks if object is already created
                        idin = true;
                        break;
                    }
                }
                if (idin == false){ //if didnt create
                    Ccheckid = cuslist.begin();
                    for (int i = 0;i < cuslist.size(); i++){
                        if (cust.getID() < Ccheckid->getID()) {
                            Ccheckid = cuslist.insert(Ccheckid, cust);
                            break;
                        }
                        else if(i == cuslist.size()-1){
                            cuslist.push_back(cust);
                            Ccheckid = --cuslist.end();
                            break;
                        }
                        Ccheckid++;
                    }
                }
            }

            if (rent == true){ //if rent was set to true
                bool thereisthatitem = false;
                for (Icheckid = invlist.begin(); Icheckid != invlist.end(); Icheckid++){
                    if (Icheckid->getID() == itemid){
                        thereisthatitem = true; // checks if item actually exist
                        if (Icheckid->theyrent(count)){ //function to check if they can even rent it
                            Icheckid->wrent(Ccheckid->getID(), count);//put person in whorent,rentamount
                            Icheckid->minusQuan(count);//function that minus quantity
                            Ccheckid->irent(count, itemid);// put item in irent,ramount
                        }
                        else{
                            Icheckid->wwait(Ccheckid->getID(), count);//put person in whowait, waitamount
                            Ccheckid->iwaiting(count,itemid);//put person in iwait, wamount
                        }
                        break;
                    }
                }
                if (thereisthatitem == false){ // if item dont
                    string cidn = Ccheckid->getID().substr(1,4);
                    string iidn = itemid.substr(1,4);
                    cerr << "Customer C" << cidn << " requested item T" << iidn << " which is not in the inventory." <<endl;
                }
            }

            else if (giveb == true){ //if return sets to true
                bool isitemthere = false;
                for (Icheckid = invlist.begin(); Icheckid != invlist.end(); Icheckid++){
                    if (Icheckid->getID() == itemid){
                        isitemthere = true; //if item return is actually there
                        if (Ccheckid->ihave(itemid)){ //if person actually rented this item before
                            Icheckid->plusQuan(count); // adds to quantity
                            Ccheckid->ireturn(count, itemid);//performs the return function
                            Icheckid->delcust(count, Ccheckid->getID());//performs delcust function
                            if (Icheckid->whonext()!="empty"){//if there is someone in waiting list
                                string tempid = Icheckid->whonext();
                                int x = Icheckid->notwaiting(tempid);
                                Icheckid->wrent(tempid, x);
                                Icheckid->minusQuan(x);

                                list <Customers>::iterator nextcus;
                                for (nextcus = cuslist.begin();nextcus!=cuslist.end();nextcus++){
                                    if (nextcus->getID() == tempid){
                                        break;
                                    }
                                }
                                int y = nextcus->imnotw(Icheckid->getID());
                                nextcus->irent(y, Icheckid->getID());
                            }
                        }
                        else{ //if never rent the item before
                            string cidn = Ccheckid->getID().substr(1,4);
                            string iidn = itemid.substr(1,4);
                            cerr << "Customer C"<< cidn <<" attempted to return item T" << iidn << " which she/he did not rent." <<endl;
                        }
                    }
                }
                if (isitemthere == false){ //if item not there
                    string cidn = Ccheckid->getID().substr(1,4);
                    string iidn = itemid.substr(1,4);
                    cerr << "Customer C"<<cidn<<" attempted to return item T"<<iidn<<" which is not in the inventory." <<endl;
                }

            }
            //resets
            cID = false;
            rent = false;
            giveb = false;
            time = false;
            count = 0;
            itemid = "temp";
            cusid = "";
            custime = "";
            cusname = "";
        }
        else if (cID == false){ // if id is false cerr error
            cerr << "Invalid customer information found for ID " << words2 << " in the customer file." << endl;
            string a, b, c, d, e;
            in_str2 >> a >> b >>c >>d>>e;
        }
    }


    // ALL THE PRINT OUT TO ANOTHER FILE
    ofstream out_str(argv[3]);
    if (!out_str.good()) {
        cerr << "Can't open " << argv[3] << " to write.\n";
        exit(1);
    }
    list<Inventory>::iterator INV; // write to file
    for (INV = invlist.begin(); INV!=invlist.end(); INV++){
        out_str << INV->getID() << ' ' << INV->getQuan() << " available " << INV->getName() << "\n";
        out_str << INV->printINV(cuslist); //print function for inventory
    }


    ofstream out_str2(argv[4]);
    if (!out_str2.good()) {
        cerr << "Can't open " << argv[4] << " to write.\n";
        exit(1);
    }
    list<Customers>::iterator CUS; // write to another file
    for (CUS = cuslist.begin(); CUS!=cuslist.end(); CUS++){
        out_str2 << CUS->printCUS(); // print function for customer
    }

    return 0;
}