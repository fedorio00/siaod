#include "hash_table.h"
#include <vector>
#include <iostream>
using namespace std;

// Функция тестирования хэш-таблицы
void testHashT() {
    // Создаем исходный массив из 20 записей
    vector<Record> records = {
        {"1", "MIREA", "Computer Science"},
        {"2", "MGIMO", "English Literature"},
        {"3", "BAUMAN", "Mathematics"},
        {"4", "ITMO", "Biology"},
        {"5", "BAUMAN", "Chemistry"},
        {"6", "ITMO", "Physics"},
        {"7", "BAUMAN", "History"},
        {"8", "MIREA", "Art"},
        {"9", "ITMO", "Music"},
        {"10", "ITMO", "Psychology"},
        {"11", "MIREA", "Sociology"},
        {"12", "MGIMO", "Philosophy"},
        {"13", "MIREA", "Economics"},
        {"14", "ITMO", "Statistics"},
        {"15", "MIREA", "Geography"},
        {"16", "BAUMAN", "Literature"},
        {"17", "MGIMO", "Medicine"},
        {"18", "BAUMAN", "Engineering"},
        {"19", "MIREA", "Architecture"},
        {"20", "MGIMO", "Nursing"}
    };

    HashTable hashTable;

    // Тест 1: Вставка без коллизий
    cout << "Test 1: Inserting elements\n";
    for (int i = 0; i < records.size(); i++) {
        hashTable.insert(records[i].universityCode, i);
    }
    hashTable.display();

    // Тест 2: Поиск существующего элемента
    cout << "\nTest 2: Searching for existing element\n";
    int index = hashTable.search("19");
    if (index != -1) {
        cout << "Found key 19 at index " << index << endl;
    }

    // Тест 3: Поиск несуществующего элемента
    cout << "\nTest 3: Searching for non-existing element\n";
    index = hashTable.search("NONEXISTENTKEY");
    if (index == -1) {
        cout << "Key NONEXISTENTKEY not found\n";
    }

    // Тест 4: Удаление элемента
    cout << "\nTest 4: Removing element\n";
    hashTable.remove("MATH303");
    hashTable.display();
}

int main() {
    testHashT();
    // Ожидание ввода от пользователя перед закрытием
    cout << "\nPress Enter to exit...";
    cin.get(); // Ожидание нажатия клавиши Enter
    return 0;
} 