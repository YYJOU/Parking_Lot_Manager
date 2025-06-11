#pragma once
#include <string>
using namespace std;

class Car {
private:
    string plate;
    bool monthly;
public:
    Car(const string& p, bool m);
    
    string getPlate() const;
    
    bool isMonthly() const;
};
