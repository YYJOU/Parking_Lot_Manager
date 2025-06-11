#pragma once
#include "ParkingLot.h"
#include "Car.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ParkingSystem {
private:
    ParkingLot lot;
    vector<Car> monthlyCars;
    int revenue = 0;
    
    bool isMonthlyPlate(const string& plate) const;
    bool addMonthlyPlate(const string& plate);
    
    string adminPassword = "0000";

public:
    void init();
    
    void importData(const string& filename = "parking_data.txt");
    void exportData(const string& filename = "parking_data.txt") const;
    
    void menu() const;
    void manager();
    
    void parkIn();
    void parkOut();
    
    void printslot() const;
    
    void showMonthlyPlates() const;
    bool removeMonthlyPlate(const std::string& plate);
    void printEmptySlotsPerFloor() const;

};
