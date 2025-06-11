#include "ParkingSystem.h"

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
    cout << "設定停車場大小：\n";
    cout << "輸入停車樓層數 (例如2表示B1~B2): ";
    cin >> y;
    cout << "每層樓的列數: ";
    cin >> i;
    cout << "每層樓的的欄位數: ";
    cin >> j;
    lot.init(y, i, j);
    cout << "車場大小已設定為 " << y << " 層樓，每層 " << i << " 列 " << j << " 欄。\n";
}

void ParkingSystem::importData(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "檔案讀取失敗\n\n";
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
    cout << "資料已從 " << filename << " 匯入\n";
}

void ParkingSystem::exportData(const string& filename) const {
    ofstream fout(filename);
    if (!fout) {
        cout << "檔案寫入失敗\n";
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
    cout << "資料已匯出至 " << filename << "\n";
}

void ParkingSystem::menu() const {
    cout << "\n★ 停車場管理系統 ★\n"
        << "1 車輛進場\n"
        << "2 車輛出場\n"
        << "3 顯示車位狀況\n"
        << "4 管理員模式\n"
        << "0 離開\n"
        << "請選: ";
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
                    cout << fixed << setw(8) << slot.getPlate() << "|";
            }
            cout << "\n ";
            for (int i = 0; i < lot.getCols() * 9 - 1; i++) cout << "-";
            cout << "\n";
        }
    }
}

void ParkingSystem::manager() {
    string inputPwd;
    cout << "請輸入管理員密碼：";
    cin >> inputPwd;
    if (inputPwd != adminPassword) {
        cout << "密碼錯誤，無法進入管理員模式。\n";
        return;
    }
    int option;
    do {
        cout << "\n★ 管理員模式 ★\n"
            << "1 顯示盈收資訊\n"
            << "2 新增月租車\n"
            << "3 移除月租車\n"
            << "4 顯示月租車車牌\n"
            << "5 匯入資料\n"
            << "6 匯出資料\n"
            << "0 回主選單\n"
            << "請選: ";
        cin >> option;
        if (option == 1) {
            cout << "目前總盈收：$" << revenue << "\n";
        }
        else if (option == 2) {
            string plate;
            cout << "輸入要登記為月租的車牌號碼：";
            cin >> plate;
            if (addMonthlyPlate(plate)) {
                int fee = 600;
                cout << "已將 " << plate << " 登記為月租車。\n";
                revenue += fee;
                cout << "停車費：$" << fee << "\n";
            }
            else {
                cout << plate << " 已經是月租車。\n";
            }
        }
        else if (option == 3) {
            string plate;
            cout << "輸入要移除的月租車牌號碼：";
            cin >> plate;
            if (removeMonthlyPlate(plate)) {
                cout << "已移除月租車 " << plate << "\n";
            }
            else {
                cout << "查無此月租車。\n";
            }
        }
        else if (option == 4) {
            showMonthlyPlates();
        }
        else if (option == 5) {
            importData();
        }
        else if (option == 6) {
            exportData();
        }
    } while (option != 0);

}

void ParkingSystem::parkIn() {
    string plate;
    cout << "輸入車牌號碼：";
    cin >> plate;

    int emptyCount = lot.getEmptyCount();
    if (emptyCount == 0) {
        cout << "目前無空車位。\n";
        return;
    }

    printslot();
    int slotNum;
    cout << "輸入欲停入的車位編號：";
    cin >> slotNum;
    if (slotNum < 1 || slotNum > emptyCount) {
        cout << "車位編號無效。\n";
        return;
    }
    ParkingSlot* slot = nullptr;
    if (!lot.findEmptySlotByNumber(slotNum, slot)) {
        cout << "找不到對應的空車位。\n";
        return;
    }
    lot.parkCar(slot, plate);
    printslot();
    cout << "車輛 " << plate << " 已成功停入 B" << slot->getFloor() + 1 << "-" << slot->getRow() + 1 << "-" << slot->getCol() + 1;
    if (isMonthlyPlate(plate)) cout << " (月租車)";
    cout << endl;
}

void ParkingSystem::parkOut() {
    printslot();
    string plate;
    cout << "輸入欲出場的車牌號碼：";
    cin >> plate;
    ParkingSlot* slot = nullptr;
    if (!lot.findPlate(plate, slot)) {
        cout << "查無車牌 " << plate << "，請確認是否輸入正確。\n";
        return;
    }
    lot.leaveCar(slot);
    cout << "車輛 " << plate << " 已離場（位置：B" << slot->getFloor() + 1 << "-" << slot->getRow() + 1 << "-" << slot->getCol() + 1 << "）\n";
    if (!isMonthlyPlate(plate)) {
        int fee = 50;
        revenue += fee;
        cout << "停車費：$" << fee << "\n";
    } else {
        cout << "（月租車免收費）\n";
    }
}
void ParkingSystem::showMonthlyPlates() const {
    cout << "月租車車牌清單：\n";
    if (monthlyCars.empty()) {
        cout << "（無月租車）\n";
        return;
    }
    for (const auto& car : monthlyCars) {
        cout << car.getPlate() << "\n";
    }
}

bool ParkingSystem::removeMonthlyPlate(const string& plate) {
    for (auto it = monthlyCars.begin(); it != monthlyCars.end(); ++it) {
        if (it->getPlate() == plate) {
            monthlyCars.erase(it);
            return true;
        }
    }
    return false;
}
void ParkingSystem::printEmptySlotsPerFloor() const {
    for (int b = 0; b < lot.getFloors(); ++b) {
        int empty = 0;
        const auto& slots = lot.getAllSlots()[b];
        for (int r = 0; r < lot.getRows(); ++r) {
            for (int c = 0; c < lot.getCols(); ++c) {
                if (!slots[r][c].isOccupied())
                    ++empty;
            }
        }
        cout << "B" << (b + 1) << " 剩餘車位：" << empty << "\n";
    }
}
