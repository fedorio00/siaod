#include <iostream>
#include "file_operations.h"
using namespace std;

void showMenu() {
    cout << "1. Display file content" << endl;
    cout << "2. Append to file" << endl;
    cout << "3. Get number by index" << endl;
    cout << "4. Count numbers in file" << endl;
    cout << "5. Create new file by rule" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    if (!fileExists(filename)) {
        cerr << "File does not exist: " << filename << endl;
        return 1;
    }

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayFileContent(filename);
                break;
            case 2: {
                string data;
                cout << "Enter data to append: ";
                cin.ignore();
                getline(cin, data);
                appendToFile(filename, data);
                break;
            }
            case 3: {
                int index;
                cout << "Enter index: ";
                cin >> index;
                int number = getNumberByIndex(filename, index);
                if (number != -1) {
                    cout << "Number at index " << index << ": " << number << endl;
                } else {
                    cout << "Index out of range or file error." << endl;
                }
                break;
            }
            case 4: {
                int count = countNumbersInFile(filename);
                if (count != -1) {
                    cout << "Number of numbers in file: " << count << endl;
                } else {
                    cout << "File error." << endl;
                }
                break;
            }
            case 5: {
                string outputFilename;
                cout << "Enter output filename: ";
                cin >> outputFilename;
                createNewFileByRule(filename, outputFilename);
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}