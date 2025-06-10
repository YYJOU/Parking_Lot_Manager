#pragma once
#include <string>

class ParkingSlot {
private:
    int floor, row, col;
    std::string plate;
    bool occupied;
public:
    ParkingSlot(int f = 0, int r = 0, int c = 0);
    bool isOccupied() const;
    std::string getPlate() const;
    void park(const std::string& p);
    void leave();
    int getFloor() const;
    int getRow() const;
    int getCol() const;
};
