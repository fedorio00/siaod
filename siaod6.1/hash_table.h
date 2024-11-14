#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <string>
using namespace std;

// Структура для исходных данных
struct Record {
    string universityCode; // код специальности
    string universityName;  // название вуза
    string specialtyName;   // название специальности
};

// Структура элемента хэш-таблицы
struct HashNode {
    string key;        // ключ записи
    int index;        // индекс в исходном массиве
    bool prK;         // признак включения ключа
    HashNode* next;   // указатель на следующий элемент (для цепочки)
    
    HashNode(string k = "", int idx = -1) : 
        key(k), index(idx), prK(false), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 11;  // размер хэш-таблицы
    HashNode* table[TABLE_SIZE];       // массив указателей на цепочки

    // Хэш-функция
    int hashFunction(const string& key) {
        // Простой хэш на основе суммы символов
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() {
        // Инициализация таблицы пустыми указателями
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Вставка элемента в хэш-таблицу
    void insert(const string& key, int index) {
        int hash = hashFunction(key);
        
        HashNode* newNode = new HashNode(key, index);
        newNode->prK = true;

        // Если ячейка пуста
        if (table[hash] == nullptr) {
            table[hash] = newNode;
        }
        // Если есть коллизия
        else {
            HashNode* current = table[hash];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Поиск элемента по ключу
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

    // Удаление элемента
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
        return true;
    }

    // Вывод таблицы
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << "[Key: " << current->key 
                     << ", Index: " << current->index << "] -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }

    // Деструктор
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

#endif 