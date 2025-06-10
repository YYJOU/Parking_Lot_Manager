#include <iostream>
#include "ParkingSystem.h"
using namespace std;

int main() {
    ParkingSystem System;

    cout << "是否要匯入上次的資料？(y/n)：";
    char ans;
    cin >> ans;
    if (ans == 'y' || ans == 'Y') {
        System.importData();
    }
    else {
        System.init();
    }

    int choice;
    do {
        System.menu();
        cin >> choice;
        switch (choice) {
        case 1:
            System.parkIn();
            break;
        case 2:
            System.printslot();
            System.parkOut();
            break;
        case 3:
            System.printslot();
            break;
        case 4:
            System.manager();
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
