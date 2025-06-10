#pragma once
#include "ParkingSlot.h"
#include <vector>
using namespace std;

class ParkingLot {
private:
    int floors, rows, cols;
    vector<vector<vector<ParkingSlot>>> slots;
    vector<vector<vector<ParkingSlot>>>& getAllSlots();

    friend class ParkingSystem;

public:
    ParkingLot();
    
    void init(int f, int r, int c);
    
    int getEmptyCount() const;
    
    bool findEmptySlotByNumber(int slotNum, ParkingSlot*& slot);
    bool findPlate(const string& plate, ParkingSlot*& slot);
    
    void parkCar(ParkingSlot* slot, const string& plate);
    void leaveCar(ParkingSlot* slot);
    
    int getFloors() const;
    int getRows() const;
    int getCols() const;
    
    const vector<vector<vector<ParkingSlot>>>& getAllSlots() const;
};
