#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "hash_table.h"
#include "file_operations.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>

class FileManager {
private:
    HashTable& hashTable;
    string filename;

    double measureSearchTime(int key) {
        auto start = chrono::high_resolution_clock::now();
        
        string keyStr = to_string(key);
        int index = hashTable.search(keyStr);
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> duration = end - start;
        return duration.count();
    }

public:
    FileManager(HashTable& ht, const string& fname) : hashTable(ht), filename(fname) {}

    void readRecordAndInsertToTable(int key) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        Specialization specialization;
        file.seekg(key * sizeof(Specialization), ios::beg);
        if (file.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
            // Вставляем запись в хеш-таблицу
            string keyStr = to_string(specialization.specialtyCode);
            hashTable.insert(keyStr, key, specialization.universityName, specialization.specialtyName);
            cout << "Record inserted successfully.\n";
        } else {
            cerr << "Record not found at key: " << key << endl;
        }
        file.close();
    }

    void deleteRecordFromTableAndFile(int key) {
        // Сначала удаляем из хеш-таблицы
        string keyStr = to_string(key);
        if (!hashTable.remove(keyStr)) {
            cerr << "Record not found in hash table.\n";
            return;
        }

        // Затем удаляем из файла
        ifstream inputFile(filename, ios::binary);
        if (!inputFile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        ofstream outputFile("temp.dat", ios::binary);
        if (!outputFile) {
            cerr << "Error opening temporary file." << endl;
            return;
        }

        Specialization specialization;
        bool found = false;
        while (inputFile.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
            if (specialization.specialtyCode != key) {
                outputFile.write(reinterpret_cast<char*>(&specialization), sizeof(Specialization));
            } else {
                found = true;
            }
        }

        inputFile.close();
        outputFile.close();

        if (found) {
            remove(filename.c_str());
            rename("temp.dat", filename.c_str());
            cout << "Record deleted successfully.\n";
        } else {
            remove("temp.dat");
            cerr << "Record not found in file.\n";
        }
    }

    void findRecordByKey(int key) {
        // Сначала ищем в хеш-таблице
        string keyStr = to_string(key);
        int index = hashTable.search(keyStr);
        if (index == -1) {
            cerr << "Record not found in hash table.\n";
            return;
        }

        // Затем читаем из файла
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        Specialization specialization;
        file.seekg(index * sizeof(Specialization), ios::beg);
        if (file.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
            cout << "Record found:\n";
            cout << "Specialty Code: " << specialization.specialtyCode << "\n";
            cout << "University: " << specialization.universityName << "\n";
            cout << "Specialty: " << specialization.specialtyName << "\n";
        } else {
            cerr << "Error reading record from file.\n";
        }
        file.close();
    }

    void loadAllRecords() {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        Specialization spec;
        int index = 0;
        while (file.read(reinterpret_cast<char*>(&spec), sizeof(Specialization))) {
            string keyStr = to_string(spec.specialtyCode);
            hashTable.insert(keyStr, index++, spec.universityName, spec.specialtyName);
        }

        file.close();
        cout << "All records loaded into hash table.\n";
    }

    bool testSearchTime() {
        // Проверяем, есть ли записи в таблице
        if (hashTable.isEmpty()) {
            return false;
        }

        // Получаем количество записей
        int recordCount = hashTable.getSize();
        if (recordCount == 0) {
            return false;
        }

        // Тестируем первую запись
        int firstKey = 1; // Предполагаем, что ключи начинаются с 1
        double firstTime = measureSearchTime(firstKey);
        cout << "Time to find first record (key=" << firstKey << "): " << firstTime << " ms\n";

        // Тестируем запись в середине
        int middleKey = recordCount / 2;
        double middleTime = measureSearchTime(middleKey);
        cout << "Time to find middle record (key=" << middleKey << "): " << middleTime << " ms\n";

        // Тестируем последнюю запись
        int lastKey = recordCount;
        double lastTime = measureSearchTime(lastKey);
        cout << "Time to find last record (key=" << lastKey << "): " << lastTime << " ms\n";

        return true;
    }
};

#endif // FILE_MANAGEMENT_H
