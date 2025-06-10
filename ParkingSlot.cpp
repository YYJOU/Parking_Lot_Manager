#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(int f, int r, int c): floor(f), row(r), col(c), plate(""), occupied(false) {}

bool ParkingSlot::isOccupied() const { 
	return occupied; 
}
string ParkingSlot::getPlate() const { 
	return plate; 
}
void ParkingSlot::park(const string& p) {
	plate = p; occupied = true; 
}
void ParkingSlot::leave() {
	plate = ""; occupied = false; 
}
int ParkingSlot::getFloor() const { 
	return floor; 
}
int ParkingSlot::getRow() const {
	return row; 
}
int ParkingSlot::getCol() const {
	return col; 
}
