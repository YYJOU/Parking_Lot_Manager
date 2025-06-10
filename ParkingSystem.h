#pragma once
#include "ParkingLot.h"
#include "Car.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class ParkingSystem {
private:
    ParkingLot lot;
    std::vector<Car> monthlyCars;
    int revenue = 0;
    bool isMonthlyPlate(const std::string& plate) const;
    bool addMonthlyPlate(const std::string& plate);

public:
    void init();
    void importData(const std::string& filename = "parking_data.txt");
    void exportData(const std::string& filename = "parking_data.txt") const;
    void menu() const;
    void manager();
    void parkIn();
    void parkOut();
    void printslot() const; // Moved from private to public
};
