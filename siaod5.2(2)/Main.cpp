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
             << "6. Create patient list by disease code\n"
             << "7. Delete patient by key\n"
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

                cout << "Enter policy number to delete: ";
                cin >> key;
                deleteRecordByKey(filename, key);

                break;
            }
            case 6: {
                string outputFilename;
                int diseaseCode;

                cout << "Enter output filename for patient list: ";
                cin >> outputFilename;

                cout << "Enter disease code: ";

                cin >> diseaseCode;
                createPatientListByDiseaseCode(filename, outputFilename, diseaseCode);

                break;
            }
            case 7: {
                int key;
                cout << "Enter policy number to delete patient: ";
                cin >> key;

                deletePatientByKey(filename, key);
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
