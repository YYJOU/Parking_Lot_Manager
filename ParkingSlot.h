#pragma once
#include <string>
using namespace std;

class ParkingSlot {
private:
    int floor, row, col;
    string plate;
    bool occupied;
public:
    ParkingSlot(int f = 0, int r = 0, int c = 0);
    
    bool isOccupied() const;
    
    string getPlate() const;
    
    void park(const string& p);
    void leave();
    
    int getFloor() const;
    int getRow() const;
    int getCol() const;
};
