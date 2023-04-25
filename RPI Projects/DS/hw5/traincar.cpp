// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

std::vector<TrainCar*> ShipFreight(TrainCar *&all_engines, TrainCar *&all_freight, int min_speed, int max_cars) {

    std::vector<TrainCar*> v;
    while (all_engines != NULL && all_freight != NULL){
        int countcar = 0;
        TrainCar *trainhead = NULL; //new head of the train
        TrainCar *tempeng =  NULL;

        if (all_engines->next != NULL){
            tempeng = all_engines->next;
            all_engines->next = NULL;
            tempeng->prev = NULL;
        }
        else{// if there is only one engine left
            all_engines->next = NULL;
            all_engines->prev = NULL;
        }
        PushBack(trainhead, all_engines);
        all_engines = tempeng;
        countcar++;

        while (CalculateSpeed(trainhead) >= min_speed && countcar <=max_cars && all_freight != NULL) {
            TrainCar *tempfcar = all_freight->next;

            // checks if it can pushback that weight
            if (CalculateSpeedWithAnotherWeight(trainhead, all_freight->getWeight()) >= min_speed && countcar+1 <=max_cars){
                if (all_freight->next != NULL){
                    tempfcar = all_freight->next;
                    all_freight->next = NULL;
                    tempfcar->prev = NULL;
                }
                else{
                    all_freight->next = NULL;
                    all_freight->prev = NULL;
                }
                PushBack(trainhead, all_freight);
                all_freight = tempfcar;
                countcar++;
            }

            //if there is still engines left and can hold engine+car
            else if (all_engines !=NULL && countcar+2 <=max_cars){
                tempeng = all_engines;
                all_engines = all_engines->next;
                PushBack(trainhead, tempeng);

                tempfcar = all_freight;
                all_freight = all_freight->next;
                PushBack(trainhead,tempfcar);
                countcar+=2;
            }
            else{ //if it can't break and then pushback the train
                break;
            }
        }
        v.push_back(trainhead);
    }
    // when either all_engines or all_freight run out set the prev to NULL
    if (all_engines!=NULL){
        all_engines->prev = NULL;
    }
    if (all_freight !=NULL){
        all_freight->prev = NULL;
    }
    return v;
}

void Separate(TrainCar *&head1, TrainCar *&head2, TrainCar *&head3) {
    int i = 0;
    TrainCar *split = head1;
    while (i<=(numofcars(head1)/2)-1){
        split = split->next;
        i++;
    }
    head2 = head1;
    TrainCar *x = split->prev;
    split->prev->next = NULL;
    split->prev = NULL;
    head3 = split;

    if (numofeng(head2) == numofeng(head3)){ // checks if first split is perfect
        head1 = NULL;
        return;
    }

    //repair break
    x->next = split;
    split->prev = x;
    head2=NULL;
    split = head1;
    i = 0;
    while (i<=(numofcars(head1)/2)){
        split = split->next;
        i++;
    }
    head2 = head1;
    x = split->prev;
    split->prev->next = NULL;
    split->prev = NULL;
    head3 = split;
    if (numofeng(head2) == numofeng(head3)){ //checks if second split is perfect
        head1 = NULL;
        return;
    }

    //repair
    x->next = split;
    split->prev = x;
    head2=NULL;
    split = head1;
    i = 0;
    while (i<=(numofcars(head1)/2)-1){
        split = split->next;
        i++;
    }
    head2 = head1;
    split->prev->next = NULL;
    split->prev = NULL;
    head3 = split;


    // !(if head2's eng > head3's eng and if engine is balanced odd)
    if (numofeng(head2) > numofeng(head3) && !((numofeng(head2) - numofeng(head3))==1)){
        int left = 1;
        int right = 2;
        while (!(numofeng(head2) == numofeng(head3)) || !((numofeng(head2) - numofeng(head3))==1)) {
            PushFront(head3, removeEng(head2, right));
            PushBack(head2, removeF(head3, left));
            if ((numofeng(head2) == numofeng(head3)) || ((numofeng(head2) - numofeng(head3))==1)){
                break;
            }
        }
    }

    // !(if head2's eng < head3's eng and if engine is balanced odd)
    else if (numofeng(head2) < numofeng(head3) && !((numofeng(head3) - numofeng(head2))==1)){
        int left = 1;
        int right = 2;
        while (!(numofeng(head2) == numofeng(head3)) || !((numofeng(head3) - numofeng(head2))==1)){
            PushBack(head2, removeEng(head3, left));
            PushFront(head3, removeF(head2,right));
            if ((numofeng(head2) == numofeng(head3)) || ((numofeng(head3) - numofeng(head2))==1)){
                break;
            }
        }

    }
    head1 = NULL;
}

TrainCar *removeEng(TrainCar *&head, int side) {
    TrainCar *currentcar = head;
    if (side==2){ //determine which engine to remove backward
        while (currentcar->next!=NULL){
            currentcar = currentcar->next;
        }
    }

    while (currentcar != NULL){
        if (currentcar->isEngine()){
            if (currentcar == head){ //case 1 if engine is at the head
                TrainCar *nextone = currentcar->next;
                currentcar->next = NULL;
                nextone->prev = NULL;
                head = nextone;
                break;
            }
            else if (currentcar->next == NULL){ //case 2 if engine is at the end
                currentcar->prev->next = NULL;
                currentcar->prev = NULL;
                break;
            }
            else{ //case 3 if engine not at start or end
                currentcar->next->prev = currentcar->prev;
                currentcar->prev->next = currentcar->next;
                currentcar->next = NULL;
                currentcar->prev = NULL;
                break;
            }
        }
        else{
            if (side==2){ //go backward to find engine
                currentcar = currentcar->prev;
            }
            else{
                currentcar = currentcar->next;
            }
        }
    }
    return currentcar;
}

TrainCar *removeF(TrainCar *&head, int side) {
    TrainCar *currentcar = head;
    if (side==2){ //determine which side to take a freight to reduce cost
        while (currentcar->next!=NULL){
            currentcar = currentcar->next;
        }
    }

    while (currentcar !=NULL){
        if (!currentcar->isEngine()){
            if (currentcar == head){ //case 1 if the head is a freight
                TrainCar *nextone = currentcar->next;
                currentcar->next = NULL;
                nextone->prev = NULL;
                head = nextone;
                break;
            }
            else if (currentcar->next == NULL){ //case 2 if the end is a freight
                currentcar->prev->next = NULL;
                currentcar->prev = NULL;
                break;
            }
            else{ //case 3 if freight is not at start or end
                currentcar->next->prev = currentcar->prev;
                currentcar->prev->next = currentcar->next;
                currentcar->next = NULL;
                currentcar->prev = NULL;
                break;
            }
        }
        else{
            if (side==2){ //go backward to find freight
                currentcar = currentcar->prev;
            }
            else{
                currentcar = currentcar->next;
            }
        }
    }
    return currentcar;
}

int numofcars(TrainCar *head) { //function to find how many cars are on a train
    int count = 0;
    TrainCar *currentcar = head;
    while (currentcar!=NULL){
        count++;
        currentcar = currentcar->next;
    }
    return count;
}

int numofeng(TrainCar *head) { //function to find how many engs are on a train
    int count = 0;
    TrainCar *currentcar = head;
    while (currentcar!=NULL){
        if (currentcar->isEngine()){
            count++;
        }
        currentcar = currentcar->next;
    }
    return count;
}

void PushBack(TrainCar *&head, TrainCar *node) {
    if (head == NULL){
        head = node;
        node -> prev = NULL;
    }
    else{
        TrainCar *currentcar = head;
        while (currentcar->next != NULL){
            currentcar = currentcar->next;
        }
        currentcar->next = node;
        node->prev = currentcar;
        node->next = NULL;
    }
}

void PushFront(TrainCar *&head, TrainCar *node) {
    if (head == NULL){
        head = node;
        head->prev = NULL;
        head->next = NULL;
    }
    else{
        node->prev = NULL;
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void DeleteAllCars(TrainCar *&head) {
    if (head == NULL){ //if nothing to delete
        return;
    }
    else{
        TrainCar *currentcar = head;
        TrainCar *nextcar;
        while (currentcar != NULL){
            nextcar = currentcar->next;
            delete currentcar;
            currentcar = nextcar;
        }
        head = NULL;
    }
}

void TotalWeightAndCountCars(TrainCar *head, int &total_weight, int &num_engines, int &num_freight_cars,
                             int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars) {
    TrainCar *currentcar = head;

    //initalized all the ints
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    while (currentcar!= NULL){
        if (currentcar->isEngine()){
            total_weight += currentcar->getWeight();
            num_engines++;
        }
        else if (currentcar->isFreightCar()){
            total_weight += currentcar->getWeight();
            num_freight_cars++;
        }
        else if (currentcar->isPassengerCar()){
            total_weight += currentcar->getWeight();
            num_passenger_cars++;
        }
        else if (currentcar->isDiningCar()){
            total_weight += currentcar->getWeight();
            num_dining_cars++;
        }
        else if (currentcar->isSleepingCar()){
            total_weight += currentcar->getWeight();
            num_sleeping_cars++;
        }
        currentcar = currentcar->next;
    }

}

float CalculateSpeed(TrainCar *head) {
    float speed;
    int num_engines = 0;
    int total_weight = 0;
    TrainCar *currentcar = head;

    while (currentcar != NULL){
        if (currentcar->isEngine()){
            num_engines++;
        }
        total_weight += currentcar->getWeight();
        currentcar = currentcar->next;
    }

    long long int big = 3000;
    speed = (num_engines * big * 550 * 3600)/float(20 * 2 * 5280 * total_weight);
    return speed;
}

float CalculateSpeedWithAnotherWeight(TrainCar *head, int weight) {
    float speed;
    int num_engines = 0;
    int total_weight = 0;
    TrainCar *currentcar = head;

    while (currentcar!= NULL){
        if (currentcar->isEngine()){
            num_engines++;
        }
        total_weight += currentcar->getWeight();
        currentcar = currentcar->next;
    }

    total_weight += weight; //with an extra weight
    long long int big = 3000;
    speed = (num_engines * big * 550 * 3600) /float(20 * 2 * 5280 * total_weight);
    return speed;
}

float AverageDistanceToDiningCar(TrainCar *head) {
    TrainCar *currentcar = head;
    int totalsteps = 0;
    int totalpass = 0;

    while (currentcar!=NULL){
        if (currentcar->isPassengerCar()){
            totalpass++;
            int steps = 0;

            //case 1 if it's at the start
            if (currentcar == head){
                TrainCar *foward = currentcar;
                while (foward!=NULL){
                    if (!foward->isPassengerCar() || !foward->isSleepingCar()){
                        if (foward->isEngine()){
                            return -1.0;
                        }
                        else if (foward->isDiningCar()){
                            break;
                        }
                    }
                    steps++;
                    foward = foward->next;
                }
                totalsteps += steps;
            }

            // case 2 if it's at the end
            else if (currentcar->next == NULL){
                TrainCar *backward = currentcar;
                while (backward!=NULL){
                    if (!backward->isPassengerCar() || !backward->isSleepingCar()){
                        if (backward->isEngine()){
                            return -1.0;
                        }
                        else if (backward->isDiningCar()){
                            break;
                        }
                    }
                    steps++;
                    backward = backward->prev;
                }
                totalsteps += steps;
            }

            //case 3 if not start or end
            else{
                int stepleft = 0;
                int stepright = 0;
                bool backno = false;
                bool rightno = false;

                //find dining forwards
                TrainCar *foward = currentcar;
                while (foward!=NULL){
                    if (!foward->isPassengerCar() || !foward->isSleepingCar()){
                        if (foward->isEngine()){
                            rightno = true;
                            break;
                        }
                        else if (foward->isDiningCar()){
                            break;
                        }
                    }
                    steps++;
                    foward = foward->next;
                }
                stepright = steps;
                steps = 0;


                //find dining backwards
                TrainCar *backward = currentcar;
                while (backward!=NULL){
                    if (!backward->isPassengerCar() || !backward->isSleepingCar()){
                        if (backward->isEngine()){
                            backno = true;
                            break;
                        }
                        else if (backward->isDiningCar()){
                            break;
                        }
                    }
                    steps++;
                    backward = backward->prev;
                }
                stepleft = steps;


                //if both sides have engines blocking return INF
                if (backno && rightno){
                    return -1.0;
                }
                else{
                    //determine which side is closest
                    if (!backno && !rightno){
                        if (stepleft < stepright){
                            totalsteps += stepleft;
                        }
                        else if (stepleft > stepright){
                            totalsteps += stepright;
                        }
                        else if (stepleft == stepright){
                            totalsteps += totalsteps;
                        }
                    }
                    else if (backno && !rightno){
                        totalsteps += stepright;
                    }
                    else if (!backno && rightno){
                        totalsteps += stepleft;
                    }
                }
            }
        }

        currentcar = currentcar->next;
    }
    float avgDIS = float(totalsteps)/float(totalpass);
    return avgDIS;
}

int ClosestEngineToSleeperCar(TrainCar *head) {
    TrainCar *currentcar = head;

    int closest_to_sleep = 999;
    while (currentcar != NULL){
        if (currentcar->isSleepingCar()){
            //case 1 if the sleeping is the start of the train
            if (currentcar == head){
                TrainCar *forward = currentcar;
                int steps = 0;
                while (forward!=NULL){
                    if (forward->isEngine()){
                        break;
                    }
                    steps++;
                    forward = forward->next;
                }
                if (steps < closest_to_sleep){
                    closest_to_sleep = steps;
                }
            }

            //case 2 if the sleeping is at the end of the train
            else if (currentcar->next == NULL){
                TrainCar *backward = currentcar;

                int steps = 0;
                while (backward!=NULL){
                    if (backward->isEngine()){
                        break;
                    }
                    steps++;
                    backward = backward->prev;
                }
                if (steps < closest_to_sleep){
                    closest_to_sleep = steps;
                }
            }

            //case 3 if not start or end
            else {
                //forward to find engine
                TrainCar *forward = currentcar;
                int steps = 0;
                while (forward!=NULL){
                    if (forward->isEngine()){
                        break;
                    }
                    steps++;
                    forward = forward->next;
                }
                if (steps < closest_to_sleep){
                    closest_to_sleep = steps;
                }


                //backwards to find engine
                TrainCar *backward = currentcar;
                steps = 0;
                while (backward!=NULL){
                    if (backward->isEngine()){
                        break;
                    }
                    steps++;
                    backward = backward->prev;
                }
                if (steps < closest_to_sleep){
                    closest_to_sleep = steps;
                }
            }
        }
        currentcar = currentcar->next;
    }
    return closest_to_sleep;
}




















