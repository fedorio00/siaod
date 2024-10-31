#include <iostream>
#include <iomanip>
#include <bitset>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale> // ��������� ��� ��������� ������

using namespace std;

void printTable(const string& description, unsigned int value, unsigned int mask, unsigned int result) {
    cout << setw(30) << description << setw(12) << "10 �." << setw(12) << "16 �." << setw(35) << "2 �." << endl;
    cout << string(94, '-') << endl;

    cout << setw(30) << "�������� �������� (x)"
         << setw(12) << dec << value
         << setw(12) << hex << uppercase << value
         << setw(40) << bitset<32>(value)
         << endl;

    cout << setw(30) << "�������(512)"
         << setw(12) << dec << 9
         << setw(12) << hex << uppercase << 9
         << setw(40) << bitset<32>(9)
         << endl;

    cout << setw(30) << "���������"
         << setw(12) << dec << result
         << setw(12) << hex << uppercase << result
         << setw(40) << bitset<32>(result)
         << endl << endl;
}


int main() {
    // ��������� ������ ��� ����������� ����������� ���������
    setlocale(LC_ALL, "Russian");

 // ������ ������: ���� �������� � ��������� �� 512
    unsigned int originalValue;
    cout << "������� ����� �����: ";
    cin >> originalValue;

    unsigned int multiplier = 512; // 2^9
    unsigned int result3 = originalValue << 9; // ����� ����� �� 9 ���
    unsigned int result4 = originalValue >> 9; // ����� ������ �� 9 ��� ��� ������� �� 512
    
    cout << "��������� 3:" << endl;
    printTable("������������ �������� � ����������", originalValue, multiplier, result3);

    // ��������� ��� ���������� 4
    cout << "��������� 4:" << endl;
    printTable("������������ �������� � ���������", originalValue, multiplier, result4);
    

    cout << "������� Enter ��� ���������� ���������...";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
    return 0;
}
