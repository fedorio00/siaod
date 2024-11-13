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

<<<<<<< HEAD
void generateUniversityListBySpecialty(const string& inputFilename, int specialtyCode, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Ошибка открытия файла: " << inputFilename << endl;
=======
void generateUniversityListBySpecialty(int specialtyCode, const string& outputFilename) {
    ifstream inputFile("data.dat", ios::binary);
    if (!inputFile) {
        cerr << "Error opening file." << endl;
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
        return;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
<<<<<<< HEAD
        cerr << "Ошибка открытия выходного файла." << endl;
=======
        cerr << "Error opening output file." << endl;
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
        return;
    }

    Specialization specialization;
<<<<<<< HEAD
    bool found = false;
    while (inputFile.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        if (specialization.specialtyCode == specialtyCode) {
            outputFile << specialization.universityName << "\n";
            found = true;
=======
    while (inputFile.read(reinterpret_cast<char*>(&specialization), sizeof(Specialization))) {
        if (specialization.specialtyCode == specialtyCode) {
            outputFile << specialization.universityName << "\n";
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
        }
    }

    if (!found) {
        cerr << "Специальности с кодом " << specialtyCode << " не найдено." << endl;
    }

    inputFile.close();
    outputFile.close();
}

<<<<<<< HEAD
void changeSpecialtyCodeByName(const string& filename, const string& specialtyName, int newCode) {
    ifstream inputFile(filename, ios::binary);
=======
void changeSpecialtyCodeByName(const string& specialtyName, int newCode) {
    ifstream inputFile("data.dat", ios::binary);
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
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
<<<<<<< HEAD
        if (strcmp(specialization.specialtyName, specialtyName.c_str()) == 0) {
=======
        if (specialization.specialtyName == specialtyName) {
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
            specialization.specialtyCode = newCode;
            found = true;
        }
        outputFile.write(reinterpret_cast<char*>(&specialization), sizeof(Specialization));
    }

    inputFile.close();
    outputFile.close();

    if (found) {
<<<<<<< HEAD
        remove(filename.c_str());
        rename("temp.dat", filename.c_str());
        cout << "Specialty code updated successfully." << endl;
    } else {
        cerr << "Specialty with name '" << specialtyName << "' not found." << endl;
        remove("temp.dat");
=======
        remove("data.dat");
        rename("temp.dat", "data.dat");
    } else {
        cerr << "Specialty with name " << specialtyName << " not found." << endl;
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942
    }
}