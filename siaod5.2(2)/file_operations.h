#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Patient {
    int policyNumber;
    char lastName[50];
    char firstName[50];
    char patronymic[50];
    char diseaseCode[10];
    char diagnosisDate[11]; // YYYY-MM-DD
    int doctorCode;
};

bool fileExists(const string& filename);
void convertTextToBinary(const string& inputFilename, const string& outputFilename);
void convertBinaryToText(const string& inputFilename, const string& outputFilename);
void displayBinaryFileContent(const string& filename);
void accessRecordByIndex(const string& filename, int index);
void deleteRecordByKey(const string& filename, int key);
void createPatientListByDiseaseCode(const string& inputFilename, const string& outputFilename, int diseaseCode);
void deletePatientByKey(const string& filename, int key);

#endif // FILE_OPERATIONS_H
