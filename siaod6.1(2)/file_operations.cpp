#include "file_operations.h"
#include <string>
using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void convertTextToBinary(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Error opening file: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile) {
        cerr << "Error opening file: " << outputFilename << endl;
        return;
    }

    Specialization specialization;
    while (inputFile >> specialization.specialtyCode >> specialization.universityName >> specialization.specialtyName) {
        outputFile.write(reinterpret_cast<char*>(&specialization), sizeof(Specialization));
    }

    inputFile.close();
    outputFile.close();
}

void convertBinaryToText(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Error opening file: " << inputFilename << endl;
        return;
    }
    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error opening file: " << outputFilename << endl;
        return;
    }

    Specialization specialization;
    while (inputFile.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        outputFile << "Specialty Code: " << specialization.specialtyCode << "\n"
                   << "University Name: " << specialization.universityName << "\n"
                   << "Specialty Name: " << specialization.specialtyName << "\n\n";
    }

    inputFile.close();
    outputFile.close();
}

void displayBinaryFileContent(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    Specialization specialization;
    while (file.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        cout << "Specialty Code: " << specialization.specialtyCode << "\n"
             << "University Name: " << specialization.universityName << "\n"
             << "Specialty Name: " << specialization.specialtyName << "\n\n";
    }

    file.close();
}

void accessRecordByIndex(const string& filename, int index) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file.seekg(index * sizeof(Specialization), ios::beg);
    Specialization specialization;
    if (file.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        cout << "Specialty Code: " << specialization.specialtyCode << "\n"
             << "University Name: " << specialization.universityName << "\n"
             << "Specialty Name: " << specialization.specialtyName << "\n";
    } else {
        cerr << "Record not found at index: " << index << endl;
    }

    file.close();
}

void deleteRecordByKey(const string& filename, int key) {
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
    } else {
        cerr << "Record with key " << key << " not found." << endl;
    }
}

void generateUniversityListBySpecialty(const string& inputFilename, int specialtyCode, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Ошибка открытия файла: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Ошибка открытия выходного файла." << endl;
        return;
    }

    Specialization specialization;
    bool found = false;
    while (inputFile.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        if (specialization.specialtyCode == specialtyCode) {
            outputFile << specialization.universityName << "\n";
            found = true;
        }
    }

    if (!found) {
        cerr << "Специальности с кодом " << specialtyCode << " не найдено." << endl;
    }

    inputFile.close();
    outputFile.close();
}

void changeSpecialtyCodeByName(const string& filename, const string& specialtyName, int newCode) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cerr << "Error opening file." << endl;
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
        if (strcmp(specialization.specialtyName, specialtyName.c_str()) == 0) {
            specialization.specialtyCode = newCode;
            found = true;
        }
        outputFile.write(reinterpret_cast<char*>(&specialization), sizeof(Specialization));
    }

    inputFile.close();
    outputFile.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.dat", filename.c_str());
        cout << "Specialty code updated successfully." << endl;
    } else {
        cerr << "Specialty with name '" << specialtyName << "' not found." << endl;
        remove("temp.dat");
    }
}

void testBinFile() {
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
}