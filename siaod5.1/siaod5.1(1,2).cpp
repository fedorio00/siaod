#include <iostream>
#include <iomanip>
#include <bitset>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale> // Добавлено для поддержки локали

using namespace std;

// Функция для вывода таблицы данных
void printTable(const string& description, unsigned int value, unsigned int mask, unsigned int result) {
    cout << setw(30) << description << setw(12) << "10 С." << setw(12) << "16 С." << setw(40) << "2 С." << endl;
    cout << string(94, '-') << endl;

    cout << setw(30) << "Исходное значение (x)"
         << setw(12) << dec << value
         << setw(12) << hex << uppercase << value
         << setw(40) << bitset<32>(value)
         << endl;

    cout << setw(30) << "Маска"
         << setw(12) << dec << mask
         << setw(12) << hex << uppercase << mask
         << setw(40) << bitset<32>(mask)
         << endl;

    cout << setw(30) << "Результат"
         << setw(12) << dec << result
         << setw(12) << hex << uppercase << result
         << setw(40) << bitset<32>(result)
         << endl << endl;
}

int main() {
    // Установка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    // Исходные значения
    unsigned int originalValue1 = 0xFFFFFFFF;
    unsigned int originalValue2 = 0x00000000;

    // Маска 1
    unsigned int mask1 = 0xF0000000;
    unsigned int result1 = originalValue1 & ~mask1;

    // Маска 2
    unsigned int mask2 = 0xF0000000;
    unsigned int result2 = originalValue2 | mask2;
    cout << "Результат 1:" << endl;
    printTable("Обработанное значение с маской", originalValue1, mask1, result1);
    cout << "Результат 2:" << endl;
    printTable("Исходное значение с маской", originalValue2, mask2, result2);
    cout << "Нажмите Enter для завершения программы...";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
    return 0;
}
