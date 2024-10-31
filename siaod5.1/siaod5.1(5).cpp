#include <iostream>
#include <iomanip>
#include <bitset>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale> // ��������� ��� ��������� ������

using namespace std;

// ������� ��� ������ ������� ������
void printTable(const string& description, unsigned int value, unsigned int mask, unsigned int result) {
    cout << setw(30) << description << setw(12) << "10 �." << setw(12) << "16 �." << setw(40) << "2 �." << endl;
    cout << string(94, '-') << endl;

    cout << setw(30) << "�������� �������� (x)"
         << setw(12) << dec << value
         << setw(12) << hex << uppercase << value
         << setw(40) << bitset<32>(value)
         << endl;

    cout << setw(30) << "�����"
         << setw(12) << dec << mask
         << setw(12) << hex << uppercase << mask
         << setw(40) << bitset<32>(mask)
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
    
    // �������� ��������
    unsigned int originalValue1 = 0xFFFFFFFF;
    unsigned int originalValue2 = 0x00000000;

    unsigned int inputValue;
    cout << "������� ����� �����: ";
    cin >> inputValue;

    // ������������� ����� � �������� � ������� �������
    unsigned int mask = 0b00000000000000000000000000000101; // 18, 15, 2 ����
    mask = mask | (1 << 18) | (1 << 15) | (1 << 2); // ��������� ����� 18, 15, 2

    
    // �������� ����� � �����
    unsigned int modifiedValue = inputValue ^ mask;
    printTable("��������� ��������", inputValue, mask, modifiedValue);
    cout << "������� Enter ��� ���������� ���������...";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
    return 0;
}
