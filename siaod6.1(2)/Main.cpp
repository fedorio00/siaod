#include "file_operations.h"
#include "file_operations.cpp"
#include "hash_table.h"
#include "file_management.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
    testBinFile();
    cout << "\n----------------------------------------------------\nSecond part:\n";
    
    string filename;
    cout << "Enter the binary file name: ";
    cin >> filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    HashTable hashTable;
    FileManager manager(hashTable, filename);
    
    int choice;
    do {
        cout << "\nHash Table Operations:\n";
        cout << "1. Load all records into hash table\n";
        cout << "2. Find record by key\n";
        cout << "3. Remove record\n";
        cout << "4. Display hash table\n";
        cout << "5. Test search time for different positions\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int key;
        switch (choice) {
            case 1:
                manager.loadAllRecords();
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                manager.findRecordByKey(key);
                break;
            case 3:
                cout << "Enter key to remove: ";
                cin >> key;
                manager.deleteRecordFromTableAndFile(key);
                break;
            case 4:
                hashTable.display();
                break;
            case 5: {
                // Тестирование времени поиска
                if (!manager.testSearchTime()) {
                    cout << "Please load records first (option 1)\n";
                }
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
