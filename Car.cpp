#include "Car.h"

Car::Car(const std::string& p, bool m) : plate(p), monthly(m) {}
std::string Car::getPlate() const { return plate; }
bool Car::isMonthly() const { return monthly; }
