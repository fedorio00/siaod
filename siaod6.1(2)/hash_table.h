#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <string>
#include <cmath> // для floor
using namespace std;
struct Record {
    string universityCode;
    string universityName;
    string specialtyName;
};
struct HashNode {
    string key;
    int index;
    string universityName;
    string specialtyName;
    bool prK;
    HashNode* next;
    HashNode(string k = "", int idx = -1, string uName = "", string sName = "") : 
        key(k), index(idx), universityName(uName), specialtyName(sName), prK(false), next(nullptr) {}
};
class HashTable {
private:
    int TABLE_SIZE;  // размер хэш-таблицы
    HashNode** table;       // динамический массив указателей на цепочки
    int itemCount;         // количество элементов в таблице
    const double LOAD_FACTOR_THRESHOLD = 0.5;

    int hashFunction(const string& key) {
        int numericKey = stoi(key);
        const double A = 0.618033988749895;  // 1/φ, где φ - золотое сечение
        double temp = numericKey * A;
        double fractional = temp - floor(temp);  // берём дробную часть
        return floor(TABLE_SIZE * fractional);
    }

    void rehash() {
        int oldSize = TABLE_SIZE;
        HashNode** oldTable = table;
        
        // Находим следующее простое число после oldSize * 2
        TABLE_SIZE = getNextPrime(oldSize * 2);
        table = new HashNode*[TABLE_SIZE];
        
        // Инициализируем новую таблицу
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }

        // Перехешируем все элементы
        for (int i = 0; i < oldSize; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                // Вычисляем новый хеш для элемента
                int newHash = hashFunction(current->key);
                current->next = nullptr;
                
                // Вставляем элемент в новую позицию
                if (table[newHash] == nullptr) {
                    table[newHash] = current;
                } else {
                    current->next = table[newHash];
                    table[newHash] = current;
                }
                current = next;
            }
        }
        
        delete[] oldTable;
        cout << "Rehashed: new size = " << TABLE_SIZE << endl;
    }

    // Вспомогательная функция для проверки, является ли число простым
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Находит следующее простое число после n
    int getNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

public:
    HashTable() : TABLE_SIZE(23), itemCount(0) { 
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        // Очистка памяти
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }

    void insert(string key, int index, string universityName, string specialtyName) {
        // Проверяем коэффициент заполнения
        if ((double)itemCount / TABLE_SIZE > LOAD_FACTOR_THRESHOLD) {
            rehash();
        }

        int hashIndex = hashFunction(key);
        HashNode* newNode = new HashNode(key, index, universityName, specialtyName);
        
        // Вставляем в начало списка (более эффективно)
        newNode->next = table[hashIndex];
        table[hashIndex] = newNode;
        
        itemCount++;
    }
    
    int search(const string& key) {
        int hash = hashFunction(key);
        HashNode* current = table[hash];
        
        while (current != nullptr) {
            if (current->key == key) {
                return current->index;
            }
            current = current->next;
        }
        return -1;
    }
    
    bool remove(const string& key) {
        int hash = hashFunction(key);
        if (table[hash] == nullptr) {
            return false;
        }
        HashNode* current = table[hash];
        HashNode* prev = nullptr;
        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            return false;
        }
        if (prev == nullptr) {
            table[hash] = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        itemCount--;
        return true;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << "Key = " << current->key << ", Index = " << current->index << ", University = " << current->universityName << ", Specialty = " << current->specialtyName;
                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
            cout << endl;
        }
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

    int getSize() const {
        return itemCount;
    }
};
#endif