#include <iostream>
#include "ParkingSystem.h"
using namespace std;

int main() {
    ParkingSystem system;

    cout << "是否要匯入上次的資料？(y/n)：";
    char ans;
    cin >> ans;
    if (ans == 'y' || ans == 'Y') {
        system.importData();
    }
    else {
        cout << "\n";
        system.init();
    }

    int choice;
    do {
        system.menu();
        cin >> choice;
        switch (choice) {
        case 1:
            system.parkIn();
            break;
        case 2:
            system.printslot();
            system.parkOut();
            break;
        case 3:
            system.printslot();
            break;
        case 4:
            system.manager();
            break;
        case 0:
            cout << "程式結束。\n";
            break;
        default:
            cout << "請輸入有效選項。\n";
        }
    } while (choice != 0);

    return 0;
}
