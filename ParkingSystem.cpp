#include "ParkingSystem.h"
#include <fstream>
using namespace std;

bool ParkingSystem::isMonthlyPlate(const string& plate) const {
    for (const auto& car : monthlyCars)
        if (car.getPlate() == plate) return true;
    return false;
}

bool ParkingSystem::addMonthlyPlate(const string& plate) {
    if (isMonthlyPlate(plate)) return false;
    monthlyCars.emplace_back(plate, true);
    return true;
}

void ParkingSystem::init() {
    int y, i, j;
    cout << "�]�w�������j�p�G\n";
    cout << "��J�����Ӽh�� (�Ҧp2���B1~B2): ";
    cin >> y;
    cout << "�C�h�Ӫ��C��: ";
    cin >> i;
    cout << "�C�h�Ӫ�������: ";
    cin >> j;
    lot.init(y, i, j);
    cout << "�����j�p�w�]�w�� " << y << " �h�ӡA�C�h " << i << " �C " << j << " ��C\n";
}

void ParkingSystem::importData(const std::string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "�ɮ�Ū������\n\n";
        init();
        return;
    }
    int y, i, j;
    fin >> y >> i >> j;
    lot.init(y, i, j);
    string temp;
    for (int b = 0; b < y; ++b)
        for (int r = 0; r < i; ++r)
            for (int c = 0; c < j; ++c) {
                fin >> temp;
                if (temp != "-") {
                    lot.parkCar(&lot.getAllSlots()[b][r][c], temp);
                }
            }
    int m;
    fin >> m;
    monthlyCars.clear();
    for (int k = 0; k < m; ++k) {
        fin >> temp;
        monthlyCars.emplace_back(temp, true);
    }
    fin >> revenue;
    fin.close();
    cout << "��Ƥw�q " << filename << " �פJ\n";
}

void ParkingSystem::exportData(const std::string& filename) const {
    ofstream fout(filename);
    if (!fout) {
        cout << "�ɮ׼g�J����\n";
        return;
    }
    fout << lot.getFloors() << " " << lot.getRows() << " " << lot.getCols() << "\n";
    for (int b = 0; b < lot.getFloors(); ++b)
        for (int r = 0; r < lot.getRows(); ++r)
            for (int c = 0; c < lot.getCols(); ++c) {
                const ParkingSlot& slot = lot.getAllSlots()[b][r][c];
                fout << (slot.isOccupied() ? slot.getPlate() : "-") << "\n";
            }
    fout << monthlyCars.size() << "\n";
    for (const auto& car : monthlyCars)
        fout << car.getPlate() << "\n";
    fout << revenue << "\n";
    fout.close();
    cout << "��Ƥw�ץX�� " << filename << "\n";
}

void ParkingSystem::menu() const {
    cout << "\n=== �������޲z�t�� ===\n"
        << "1 �����i��\n"
        << "2 �����X��\n"
        << "3 ��ܨ��쪬�p\n"
        << "4 �޲z���Ҧ�\n"
        << "0 ���}\n"
        << "�п�: ";
}

void ParkingSystem::printslot() const {
    int num = 1;
    auto& slots = lot.getAllSlots();
    for (int b = 0; b < lot.getFloors(); ++b) {
        cout << "\nB" << b + 1 << ":\n";
        for (int r = 0; r < lot.getRows(); ++r) {
            cout << " ";
            for (int i = 0; i < lot.getCols() * 9 - 1; i++) cout << "-";
            cout << "\n|";
            for (int c = 0; c < lot.getCols(); ++c) {
                const ParkingSlot& slot = slots[b][r][c];
                if (!slot.isOccupied())
                    cout << fixed << setw(8) << num++ << "|";
                else
                    cout << fixed << setw(8) << slot.getPlate() << "|", num++;
            }
            cout << "\n ";
            for (int i = 0; i < lot.getCols() * 9 - 1; i++) cout << "-";
            cout << "\n";
        }
    }
}

void ParkingSystem::manager() {
    int option;
    do {
        cout << "\n=== �޲z���Ҧ� ===\n"
            << "1 ��ܬզ���T\n"
            << "2 �s�W�믲���P��\n"
            << "3 �פJ���\n"
            << "4 �ץX���\n"
            << "0 �^�D���\n"
            << "�п�: ";
        cin >> option;
        if (option == 1) {
            cout << "�ثe�`�զ��G$" << revenue << "\n";
        }
        else if (option == 2) {
            string plate;
            cout << "��J�n�n�O���믲�����P���X�G";
            cin >> plate;
            if (addMonthlyPlate(plate)) {
                cout << "�w�N " << plate << " �n�O���믲���C\n";
            }
            else {
                cout << plate << " �w�g�O�믲���C\n";
            }
        }
        else if (option == 3) {
            importData();
        }
        else if (option == 4) {
            exportData();
        }
    } while (option != 0);
}

void ParkingSystem::parkIn() {
    string plate;
    cout << "��J���P���X�G";
    cin >> plate;

    int emptyCount = lot.getEmptyCount();
    if (emptyCount == 0) {
        cout << "�ثe�L�Ũ���C\n";
        return;
    }

    printslot();
    int slotNum;
    cout << "��J�����J������s���G";
    cin >> slotNum;
    if (slotNum < 1 || slotNum > emptyCount) {
        cout << "����s���L�ġC\n";
        return;
    }
    ParkingSlot* slot = nullptr;
    if (!lot.findEmptySlotByNumber(slotNum, slot)) {
        cout << "�䤣��������Ũ���C\n";
        return;
    }
    lot.parkCar(slot, plate);
    printslot();
    cout << "���� " << plate << " �w���\���J B" << slot->getFloor() + 1 << "-" << slot->getRow() + 1 << "-" << slot->getCol() + 1;
    if (isMonthlyPlate(plate)) cout << " (�믲��)";
    cout << endl;
}

void ParkingSystem::parkOut() {
    printslot();
    string plate;
    cout << "��J���X�������P���X�G";
    cin >> plate;
    ParkingSlot* slot = nullptr;
    if (!lot.findPlate(plate, slot)) {
        cout << "�d�L���P " << plate << "�A�нT�{�O�_��J���T�C\n";
        return;
    }
    lot.leaveCar(slot);
    cout << "���� " << plate << " �w�����]��m�GB" << slot->getFloor() + 1 << "-" << slot->getRow() + 1 << "-" << slot->getCol() + 1 << "�^\n";
    if (!isMonthlyPlate(plate)) {
        int fee = 50;
        revenue += fee;
        cout << "�����O�G$" << fee << "\n";
    } else {
        cout << "�]�믲���K���O�^\n";
    }
}
