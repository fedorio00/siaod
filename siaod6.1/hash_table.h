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
<<<<<<< HEAD
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
=======
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
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
    }

    void rehash() {
        int oldSize = TABLE_SIZE;
        HashNode** oldTable = table;
        
<<<<<<< HEAD
        // Находим следующий размер (следующее простое число)
        TABLE_SIZE = nextPrime(TABLE_SIZE * 2);
        table = new HashNode*[TABLE_SIZE];
=======
        // Увеличиваем размер таблицы примерно в 2 раза
        TABLE_SIZE = oldSize * 2 + 1;
        table = new HashNode*[TABLE_SIZE];
        
        // Инициализируем новую таблицу
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }

<<<<<<< HEAD
        // Переносим элементы в новую таблицу
        elementCount = 0;
=======
        // Перехешируем все элементы
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
        for (int i = 0; i < oldSize; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                HashNode* next = current->next;
<<<<<<< HEAD
                // Пересчитываем хеш для нового размера таблицы
                int newHash = hashFunction(current->key);
                current->next = table[newHash];
                table[newHash] = current;
                elementCount++;
=======
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
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
                current = next;
            }
        }
        delete[] oldTable;
    }

public:
<<<<<<< HEAD
    HashTable() : TABLE_SIZE(INITIAL_SIZE), elementCount(0) {
=======
    HashTable() : TABLE_SIZE(11), itemCount(0) {
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
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
<<<<<<< HEAD
        // Проверяем, нужно ли выполнить rehashing
        double loadFactor = static_cast<double>(elementCount + 1) / TABLE_SIZE;
        if (loadFactor >= LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
        
=======
        // Проверяем коэффициент нагрузки
        float loadFactor = (float)(itemCount + 1) / TABLE_SIZE;
        if (loadFactor > 0.7) {
            rehash();
        }

>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
        int hash = hashFunction(key);
        HashNode* newNode = new HashNode(key, index);
        newNode->prK = true;

<<<<<<< HEAD
        // Вставляем в начало цепочки
        newNode->next = table[hash];
        table[hash] = newNode;
        elementCount++;
=======
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
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
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
<<<<<<< HEAD
        elementCount--;
=======
        itemCount--;
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
        return true;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
<<<<<<< HEAD
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
=======
                cout << "Key = " << current->key << ", Index = " << current->index;
                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
            cout << endl;
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
        }
        delete[] table;
    }
};
<<<<<<< HEAD

=======
>>>>>>> 996662dc697ea53a2765ed54ea983c2135eaf2da
#endif