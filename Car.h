#pragma once
#include <string>

class Car {
private:
    std::string plate;
    bool monthly;
public:
    Car(const std::string& p, bool m);
    std::string getPlate() const;
    bool isMonthly() const;
};
