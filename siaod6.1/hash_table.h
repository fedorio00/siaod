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
    bool prK;
    HashNode* next;
    HashNode(string k = "", int idx = -1) : 
        key(k), index(idx), prK(false), next(nullptr) {}
};
class HashTable {
private:
    int TABLE_SIZE;  // размер хэш-таблицы
    HashNode** table;       // динамический массив указателей на цепочки
    int itemCount;         // количество элементов в таблице

    int hashFunction(const string& key) {
        // метод умножения с золотым сечением
        const double A = 0.6180339887; // (sqrt(5) - 1) / 2
        unsigned long long hash = 0;
        
        // Вычисляем хеш строки
        for(char ch : key) {
            hash = hash * 31 + ch;
        }
        
        // Применяем метод умножения
        double temp = hash * A;
        double frac = temp - floor(temp); // Берем дробную часть
        return floor(TABLE_SIZE * frac);
    }

    void rehash() {
        int oldSize = TABLE_SIZE;
        HashNode** oldTable = table;
        
        // Увеличиваем размер таблицы примерно в 2 раза
        TABLE_SIZE = oldSize * 2 + 1;
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
                    HashNode* temp = table[newHash];
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = current;
                }
                current = next;
            }
        }
        delete[] oldTable;
    }

public:
    HashTable() : TABLE_SIZE(11), itemCount(0) {
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

    void insert(const string& key, int index) {
        // Проверяем коэффициент нагрузки
        float loadFactor = (float)(itemCount + 1) / TABLE_SIZE;
        if (loadFactor > 0.7) {
            rehash();
        }

        int hash = hashFunction(key);
        HashNode* newNode = new HashNode(key, index);
        newNode->prK = true;

        if (table[hash] == nullptr) {
            table[hash] = newNode;
        } else {
            HashNode* current = table[hash];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
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
                cout << "Key = " << current->key << ", Index = " << current->index;
                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
            cout << endl;
        }
    }
};
#endif