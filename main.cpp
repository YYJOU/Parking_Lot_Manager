#include <iostream>
#include "ParkingSystem.h"
using namespace std;

int main() {
    ParkingSystem system;

    cout << "�O�_�n�פJ�W������ơH(y/n)�G";
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
            cout << "�{�������C\n";
            break;
        default:
            cout << "�п�J���Ŀﶵ�C\n";
        }
    } while (choice != 0);

    return 0;
}
