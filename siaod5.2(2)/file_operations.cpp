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

    Patient patient;
    while (inputFile >> patient.policyNumber >> patient.lastName >> patient.firstName >> patient.patronymic >>
           patient.diseaseCode >> patient.diagnosisDate >> patient.doctorCode) {
        outputFile.write(reinterpret_cast<char*>(&patient), sizeof(Patient));
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

    Patient patient;
    while (inputFile.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        outputFile << "Policy Number: " << patient.policyNumber << "\n"
                   << "Last Name: " << patient.lastName << "\n"
                   << "First Name: " << patient.firstName << "\n"
                   << "Patronymic: " << patient.patronymic << "\n"
                   << "Disease Code: " << patient.diseaseCode << "\n"
                   << "Diagnosis Date: " << patient.diagnosisDate << "\n"
                   << "Doctor Code: " << patient.doctorCode << "\n\n";
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

    Patient patient;
    while (file.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        cout << "Policy Number: " << patient.policyNumber << "\n"
             << "Last Name: " << patient.lastName << "\n"
             << "First Name: " << patient.firstName << "\n"
             << "Patronymic: " << patient.patronymic << "\n"
             << "Disease Code: " << patient.diseaseCode << "\n"
             << "Diagnosis Date: " << patient.diagnosisDate << "\n"
             << "Doctor Code: " << patient.doctorCode << "\n\n";
    }

    file.close();
}

void accessRecordByIndex(const string& filename, int index) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file.seekg(index * sizeof(Patient), ios::beg);
    Patient patient;
    if (file.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        cout << "Policy Number: " << patient.policyNumber << "\n"
             << "Last Name: " << patient.lastName << "\n"
             << "First Name: " << patient.firstName << "\n"
             << "Patronymic: " << patient.patronymic << "\n"
             << "Disease Code: " << patient.diseaseCode << "\n"
             << "Diagnosis Date: " << patient.diagnosisDate << "\n"
             << "Doctor Code: " << patient.doctorCode << "\n";
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

    Patient patient;
    bool found = false;
    while (inputFile.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        if (patient.policyNumber != key) {
            outputFile.write(reinterpret_cast<char*>(&patient), sizeof(Patient));
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

void createPatientListByDiseaseCode(const string& inputFilename, const string& outputFilename, int diseaseCode) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Error opening file: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile) {
        cerr << "Error opening file: " << outputFilename << endl;
        return;
    }

    Patient patient;
    while (inputFile.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        if (strcmp(patient.diseaseCode, to_string(diseaseCode).c_str()) == 0) {
            outputFile.write(reinterpret_cast<char*>(&patient), sizeof(Patient));
        }
    }

    inputFile.close();
    outputFile.close();
}

void deletePatientByKey(const string& filename, int key) {
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

    Patient patient;
    while (inputFile.read(reinterpret_cast<char*>(&patient), sizeof(Patient))) {
        if (patient.policyNumber != key) {
            outputFile.write(reinterpret_cast<char*>(&patient), sizeof(Patient));
        }
    }

    inputFile.close();
    outputFile.close();

    remove(filename.c_str());
    rename("temp.dat", filename.c_str());
}
