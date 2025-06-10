#include "ParkingLot.h"

ParkingLot::ParkingLot() : floors(0), rows(0), cols(0) {}

void ParkingLot::init(int f, int r, int c) {
    floors = f; rows = r; cols = c;
    slots.clear();
    slots.resize(floors);
    for (int b = 0; b < floors; ++b) {
        slots[b].resize(rows);
        for (int r_ = 0; r_ < rows; ++r_) {
            slots[b][r_].resize(cols);
            for (int c_ = 0; c_ < cols; ++c_) {
                slots[b][r_][c_] = ParkingSlot(b, r_, c_);
            }
        }
    }
}

int ParkingLot::getEmptyCount() const {
    int count = 0;
    for (const auto& floor : slots)
        for (const auto& row : floor)
            for (const auto& slot : row)
                if (!slot.isOccupied()) count++;
    return count;
}

bool ParkingLot::findEmptySlotByNumber(int slotNum, ParkingSlot*& slot) {
    int current = 0;
    for (int b = 0; b < floors; ++b)
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (!slots[b][r][c].isOccupied()) {
                    current++;
                    if (current == slotNum) {
                        slot = &slots[b][r][c];
                        return true;
                    }
                }
    return false;
}

bool ParkingLot::findPlate(const string& plate, ParkingSlot*& slot) {
    for (int b = 0; b < floors; ++b)
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (slots[b][r][c].isOccupied() && slots[b][r][c].getPlate() == plate) {
                    slot = &slots[b][r][c];
                    return true;
                }
    return false;
}

void ParkingLot::parkCar(ParkingSlot* slot, const string& plate) {
    if (slot) slot->park(plate);
}

void ParkingLot::leaveCar(ParkingSlot* slot) {
    if (slot) slot->leave();
}

int ParkingLot::getFloors() const { return floors; }
int ParkingLot::getRows() const { return rows; }
int ParkingLot::getCols() const { return cols; }
const vector<vector<vector<ParkingSlot>>>& ParkingLot::getAllSlots() const { return slots; }
vector<vector<vector<ParkingSlot>>>& ParkingLot::getAllSlots() {
    return slots;
}
