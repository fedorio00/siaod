#include "file_operations.h"
#include <iostream>

using namespace std;

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;
    int choice;
    do {

        cout << "1. Convert text to binary\n"
             << "2. Convert binary to text\n"
             << "3. Display binary file content\n"
             << "4. Access record by index\n"
             << "5. Delete record by key\n"
             << "6. Generate university list by specialty\n"
             << "7. Change specialty code by name\n"
             << "0. Exit\n"
             << "Choose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string outputFilename;
                cout << "Enter output filename for binary: ";
                cin >> outputFilename;
                convertTextToBinary(filename, outputFilename);
                break;
            }
            case 2: {
                string outputFilename;
                cout << "Enter output filename for text: ";
                cin >> outputFilename;
                convertBinaryToText(filename, outputFilename);
                break;
            }
            case 3:
                displayBinaryFileContent(filename);
                break;
            case 4: {

                int index;
                cout << "Enter index: ";
                cin >> index;
                accessRecordByIndex(filename, index);
                break;

            }

            case 5: {
                int key;
                cout << "Enter  number to delete: ";
                cin >> key;
                deleteRecordByKey(filename, key);

                break;
            }
            case 6: {
                int specialtyCode;
                cout << "Enter specialty code: ";
                cin >> specialtyCode;
                string outputFilename;
                cout << "Enter output filename for university list: ";
                cin >> outputFilename;
                generateUniversityListBySpecialty(filename, specialtyCode, outputFilename);
                break;
            }
            case 7: {
                string specialtyName;
                int newCode;
                cout << "Enter specialty name: ";
                cin >> specialtyName;
                cout << "Enter new specialty code: ";
                cin >> newCode;
                changeSpecialtyCodeByName(filename, specialtyName, newCode);
                break;
            }
            case 0:
                cout << "Exiting program.\n";

                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
