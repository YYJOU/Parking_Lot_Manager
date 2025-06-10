#include "ParkingSystem.h"

bool ParkingSystem::isMonthlyPlate(const string& plate) const {
    for (const auto& p : monthlyPlates) {
        if (p == plate) return true;
    }
    return false;
}

bool ParkingSystem::addMonthlyPlate(const string& plate) {
    if (isMonthlyPlate(plate)) return false;
    monthlyPlates.push_back(plate);
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
    parking = vector<vector<vector<string>>>(y, vector<vector<string>>(i, vector<string>(j, "")));
    cout << "車場大小已設定為 " << y << " 層樓，每層 " << i << " 列 " << j << " 欄。\n";
}

void ParkingSystem::menu() const {
    cout << "\n=== 停車場管理系統 ===\n"
        << "1 車輛進場\n"
        << "2 車輛出場\n"
        << "3 顯示車位狀況\n"
        << "4 管理員模式\n"
        << "0 離開\n"
        << "請選: ";
}

void ParkingSystem::printslot() const {
    int num = 1;
    for (int b = 0; b < parking.size(); b++) {
        cout << "\nB" << b + 1 << ":\n";
        for (int row = 0; row < parking[b].size(); row++) {
            cout << " ";
            for (int i = 0; i < parking[b][row].size() * 9 - 1; i++) cout << "-";
            cout << "\n|";
            for (int col = 0; col < parking[b][row].size(); col++) {
                string plate = parking[b][row][col];
                if (plate.empty()) {
                    cout << fixed << setw(8) << num++ << "|";
                }
                else {
                    cout << fixed << setw(8) << plate << "|";
                    num++;
                }
            }
            cout << "\n ";
            for (int i = 0; i < parking[b][row].size() * 9 - 1; i++) cout << "-";
            cout << "\n";
        }
    }
}

void ParkingSystem::manager() {
    int option;
    do {
        cout << "\n=== 管理員模式 ===\n"
            << "1 顯示盈收資訊\n"
            << "2 新增月租車牌號\n"
            << "3 匯入資料\n"
            << "4 匯出資料\n"
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
                cout << "已將 " << plate << " 登記為月租車。\n";
            }
            else {
                cout << plate << " 已經是月租車。\n";
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
    int slotNum;
    cout << "輸入車牌號碼：";
    cin >> plate;

    // 計算空車位數量
    int emptyCount = 0;
    for (int b = 0; b < parking.size(); b++) {
        for (int r = 0; r < parking[b].size(); r++) {
            for (int c = 0; c < parking[b][r].size(); c++) {
                if (parking[b][r][c].empty()) {
                    emptyCount++;
                }
            }
        }
    }

    if (emptyCount == 0) {
        cout << "目前無空車位。\n";
        return;
    }

    printslot();
    cout << "輸入欲停入的車位編號：";
    cin >> slotNum;

    if (slotNum < 1 || slotNum > emptyCount) {
        cout << "車位編號無效。\n";
        return;
    }

    // 根據 slotNum 找到對應的空車位
    int current = 0;
    int bFound = -1, rFound = -1, cFound = -1;
    for (int b = 0; b < parking.size(); b++) {
        for (int r = 0; r < parking[b].size(); r++) {
            for (int c = 0; c < parking[b][r].size(); c++) {
                if (parking[b][r][c].empty()) {
                    current++;
                    if (current == slotNum) {
                        bFound = b;
                        rFound = r;
                        cFound = c;
                        break;
                    }
                }
            }
            if (bFound != -1) break;
        }
        if (bFound != -1) break;
    }

    if (bFound == -1) {
        cout << "找不到對應的空車位。\n";
        return;
    }

    parking[bFound][rFound][cFound] = plate;
    printslot();
    cout << "車輛 " << plate << " 已成功停入 B" << bFound + 1 << "-" << rFound + 1 << "-" << cFound + 1;
    if (isMonthlyPlate(plate)) {
        cout << " (月租車)";
    }
    cout << endl;
}


void ParkingSystem::parkOut() {
    printslot();

    string plate;
    cout << "輸入欲出場的車牌號碼：";
    cin >> plate;

    for (int b = 0; b < parking.size(); b++) {
        for (int r = 0; r < parking[b].size(); r++) {
            for (int c = 0; c < parking[b][r].size(); c++) {
                if (parking[b][r][c] == plate) {
                    cout << "車輛 " << plate << " 已離場（位置：B" << b + 1 << "-" << r + 1 << "-" << c + 1 << "）\n";
                    parking[b][r][c] = "";

                    if (!isMonthlyPlate(plate)) {
                        int fee = 50;
                        revenue += fee;
                        cout << "停車費：$" << fee << "\n";
                    }
                    else {
                        cout << "（月租車免收費）\n";
                    }
                    return;
                }
            }
        }
    }

    cout << "查無車牌 " << plate << "，請確認是否輸入正確。\n";
}
#include <fstream>

// 匯出資料
void ParkingSystem::exportData(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout) {
        std::cout << "檔案寫入失敗\n";
        return;
    }
    // 儲存停車場大小
    fout << parking.size() << " " << (parking.empty() ? 0 : parking[0].size()) << " " << (parking.empty() || parking[0].empty() ? 0 : parking[0][0].size()) << "\n";
    // 儲存停車場狀態
    for (const auto& floor : parking)
        for (const auto& row : floor)
            for (const auto& slot : row)
                fout << (slot.empty() ? "-" : slot) << "\n";
    // 儲存月租車牌
    fout << monthlyPlates.size() << "\n";
    for (const auto& plate : monthlyPlates)
        fout << plate << "\n";
    // 儲存盈收
    fout << revenue << "\n";
    fout.close();
    std::cout << "資料已匯出至 " << filename << "\n";
}

// 匯入資料
void ParkingSystem::importData(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "檔案讀取失敗\n";
        return;
    }
    int y, i, j;
    fin >> y >> i >> j;
    parking = std::vector<std::vector<std::vector<std::string>>>(y, std::vector<std::vector<std::string>>(i, std::vector<std::string>(j, "")));
    std::string temp;
    for (int b = 0; b < y; ++b)
        for (int r = 0; r < i; ++r)
            for (int c = 0; c < j; ++c) {
                fin >> temp;
                parking[b][r][c] = (temp == "-") ? "" : temp;
            }
    int m;
    fin >> m;
    monthlyPlates.clear();
    for (int k = 0; k < m; ++k) {
        fin >> temp;
        monthlyPlates.push_back(temp);
    }
    fin >> revenue;
    fin.close();
    std::cout << "資料已從 " << filename << " 匯入\n";
}
