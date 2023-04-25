// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

#include <iostream>
#include <string>
#include <vector>

std::vector<TrainCar*> ShipFreight(TrainCar *&all_engines, TrainCar *&all_freight, int min_speed, int max_cars);

void Separate(TrainCar *&head1, TrainCar *&head2, TrainCar *&head3);
int numofcars(TrainCar *head); //created to return number of totalcarts in train
int numofeng(TrainCar *head); //created to return number of totalengines in train
TrainCar *removeEng(TrainCar *&head, int side);//to remove a engine
TrainCar *removeF(TrainCar *&head, int side);//to remove a freight car
void PushBack(TrainCar *&head, TrainCar *node);
void PushFront(TrainCar *&head, TrainCar *node); //like pushback just in the front

void DeleteAllCars(TrainCar *&head);
void TotalWeightAndCountCars(TrainCar *head,int &total_weight, int &num_engines, int &num_freight_cars,
                             int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars);
float CalculateSpeed(TrainCar *head);
float CalculateSpeedWithAnotherWeight(TrainCar *head, int weight); //calculate speed with an extra weight
float AverageDistanceToDiningCar(TrainCar *head);
int ClosestEngineToSleeperCar(TrainCar *head);

