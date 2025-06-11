#include "Car.h"

Car::Car(const string& p, bool m) : plate(p), monthly(m) {}
string Car::getPlate() const { 
	return plate;
}
bool Car::isMonthly() const {
	return monthly; 
}
