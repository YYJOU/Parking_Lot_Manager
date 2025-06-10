#pragma once
#include "ParkingSlot.h"
#include <vector>

class ParkingLot {
private:
    int floors, rows, cols;
    std::vector<std::vector<std::vector<ParkingSlot>>> slots;
    std::vector<std::vector<std::vector<ParkingSlot>>>& getAllSlots();

    // Grant access to ParkingSystem
    friend class ParkingSystem;

public:
    ParkingLot();
    void init(int f, int r, int c);
    int getEmptyCount() const;
    bool findEmptySlotByNumber(int slotNum, ParkingSlot*& slot);
    bool findPlate(const std::string& plate, ParkingSlot*& slot);
    void parkCar(ParkingSlot* slot, const std::string& plate);
    void leaveCar(ParkingSlot* slot);
    int getFloors() const;
    int getRows() const;
    int getCols() const;
    const std::vector<std::vector<std::vector<ParkingSlot>>>& getAllSlots() const;
};
