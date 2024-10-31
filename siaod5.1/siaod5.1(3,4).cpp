#include <iostream>
#include <iomanip>
#include <bitset>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale> // Добавлено для поддержки локали

using namespace std;

void printTable(const string& description, unsigned int value, unsigned int mask, unsigned int result) {
    cout << setw(30) << description << setw(12) << "10 С." << setw(12) << "16 С." << setw(35) << "2 С." << endl;
    cout << string(94, '-') << endl;

    cout << setw(30) << "Исходное значение (x)"
         << setw(12) << dec << value
         << setw(12) << hex << uppercase << value
         << setw(40) << bitset<32>(value)
         << endl;

    cout << setw(30) << "Операнд(512)"
         << setw(12) << dec << 9
         << setw(12) << hex << uppercase << 9
         << setw(40) << bitset<32>(9)
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

 // Третья задача: ввод значения и умножение на 512
    unsigned int originalValue;
    cout << "Введите целое число: ";
    cin >> originalValue;

    unsigned int multiplier = 512; // 2^9
    unsigned int result3 = originalValue << 9; // Сдвиг влево на 9 бит
    unsigned int result4 = originalValue >> 9; // Сдвиг вправо на 9 бит для деления на 512
    
    cout << "Результат 3:" << endl;
    printTable("Обработанное значение с множителем", originalValue, multiplier, result3);

    // Добавлено для результата 4
    cout << "Результат 4:" << endl;
    printTable("Обработанное значение с делителем", originalValue, multiplier, result4);
    

    cout << "Нажмите Enter для завершения программы...";
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
    return 0;
}
