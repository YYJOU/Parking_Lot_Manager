#ifndef ParkingSystem_h
#define ParkingSystem_h
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ParkingSystem {
private:
    vector<vector<vector<string>>> parking;
    vector<string> monthlyPlates;
    int revenue = 0;

    bool isMonthlyPlate(const string& plate) const;
    bool addMonthlyPlate(const string& plate);

public:
    void init();
    void menu() const;
    void printslot() const;
    void manager();
    void parkIn();
    void parkOut();
    void exportData(const std::string& filename = "parking_data.txt") const;
    void importData(const std::string& filename = "parking_data.txt");

};
#endif