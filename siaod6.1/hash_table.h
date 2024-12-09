#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <string>
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
    static const int INITIAL_SIZE = 11;  // начальный размер хэш-таблицы
    int TABLE_SIZE;                      // текущий размер таблицы
    int elementCount;                    // количество элементов
    const double LOAD_FACTOR_THRESHOLD = 0.7;  // порог коэффициента загрузки
    HashNode** table;                    // массив указателей

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch);
        }
        return abs(hash % TABLE_SIZE);
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void rehash() {
        int oldSize = TABLE_SIZE;
        HashNode** oldTable = table;
        
        // Находим следующий размер (следующее простое число)
        TABLE_SIZE = nextPrime(TABLE_SIZE * 2);
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }

        // Переносим элементы в новую таблицу
        elementCount = 0;
        for (int i = 0; i < oldSize; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                // Пересчитываем хеш для нового размера таблицы
                int newHash = hashFunction(current->key);
                current->next = table[newHash];
                table[newHash] = current;
                elementCount++;
                current = next;
            }
        }
        delete[] oldTable;
    }

public:
    HashTable() : TABLE_SIZE(INITIAL_SIZE), elementCount(0) {
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(const string& key, int index) {
        // Проверяем, нужно ли выполнить rehashing
        double loadFactor = static_cast<double>(elementCount + 1) / TABLE_SIZE;
        if (loadFactor >= LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
        
        int hash = hashFunction(key);
        HashNode* newNode = new HashNode(key, index);
        newNode->prK = true;

        // Вставляем в начало цепочки
        newNode->next = table[hash];
        table[hash] = newNode;
        elementCount++;
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
        return -1; // элемент не найден
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
        elementCount--;
        return true;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << "Key = " << current->key 
                     << ", University Code = " << current->index 
                     << ", University Name = " << current->prK << " -> "; 
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }

    ~HashTable() {
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
};

#endif