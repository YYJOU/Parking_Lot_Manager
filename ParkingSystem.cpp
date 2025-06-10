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
    cout << "�]�w�������j�p�G\n";
    cout << "��J�����Ӽh�� (�Ҧp2���B1~B2): ";
    cin >> y;
    cout << "�C�h�Ӫ��C��: ";
    cin >> i;
    cout << "�C�h�Ӫ�������: ";
    cin >> j;
    parking = vector<vector<vector<string>>>(y, vector<vector<string>>(i, vector<string>(j, "")));
    cout << "�����j�p�w�]�w�� " << y << " �h�ӡA�C�h " << i << " �C " << j << " ��C\n";
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
    int slotNum;
    cout << "��J���P���X�G";
    cin >> plate;

    // �p��Ũ���ƶq
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
        cout << "�ثe�L�Ũ���C\n";
        return;
    }

    printslot();
    cout << "��J�����J������s���G";
    cin >> slotNum;

    if (slotNum < 1 || slotNum > emptyCount) {
        cout << "����s���L�ġC\n";
        return;
    }

    // �ھ� slotNum ���������Ũ���
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
        cout << "�䤣��������Ũ���C\n";
        return;
    }

    parking[bFound][rFound][cFound] = plate;
    printslot();
    cout << "���� " << plate << " �w���\���J B" << bFound + 1 << "-" << rFound + 1 << "-" << cFound + 1;
    if (isMonthlyPlate(plate)) {
        cout << " (�믲��)";
    }
    cout << endl;
}


void ParkingSystem::parkOut() {
    printslot();

    string plate;
    cout << "��J���X�������P���X�G";
    cin >> plate;

    for (int b = 0; b < parking.size(); b++) {
        for (int r = 0; r < parking[b].size(); r++) {
            for (int c = 0; c < parking[b][r].size(); c++) {
                if (parking[b][r][c] == plate) {
                    cout << "���� " << plate << " �w�����]��m�GB" << b + 1 << "-" << r + 1 << "-" << c + 1 << "�^\n";
                    parking[b][r][c] = "";

                    if (!isMonthlyPlate(plate)) {
                        int fee = 50;
                        revenue += fee;
                        cout << "�����O�G$" << fee << "\n";
                    }
                    else {
                        cout << "�]�믲���K���O�^\n";
                    }
                    return;
                }
            }
        }
    }

    cout << "�d�L���P " << plate << "�A�нT�{�O�_��J���T�C\n";
}
#include <fstream>

// �ץX���
void ParkingSystem::exportData(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout) {
        std::cout << "�ɮ׼g�J����\n";
        return;
    }
    // �x�s�������j�p
    fout << parking.size() << " " << (parking.empty() ? 0 : parking[0].size()) << " " << (parking.empty() || parking[0].empty() ? 0 : parking[0][0].size()) << "\n";
    // �x�s���������A
    for (const auto& floor : parking)
        for (const auto& row : floor)
            for (const auto& slot : row)
                fout << (slot.empty() ? "-" : slot) << "\n";
    // �x�s�믲���P
    fout << monthlyPlates.size() << "\n";
    for (const auto& plate : monthlyPlates)
        fout << plate << "\n";
    // �x�s�զ�
    fout << revenue << "\n";
    fout.close();
    std::cout << "��Ƥw�ץX�� " << filename << "\n";
}

// �פJ���
void ParkingSystem::importData(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "�ɮ�Ū������\n";
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
    std::cout << "��Ƥw�q " << filename << " �פJ\n";
}
