#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Specialization {
    int specialtyCode;
    char universityName[50];
    char specialtyName[50];
};

bool fileExists(const string& filename);
void convertTextToBinary(const string& inputFilename, const string& outputFilename);
void convertBinaryToText(const string& inputFilename, const string& outputFilename);
void displayBinaryFileContent(const string& filename);
void accessRecordByIndex(const string& filename, int index);
void deleteRecordByKey(const string& filename, int key);
<<<<<<< HEAD
void generateUniversityListBySpecialty(const string& inputFilename, int specialtyCode, const string& outputFilename);
void changeSpecialtyCodeByName(const string& filename, const string& specialtyName, int newCode);
=======
void generateUniversityListBySpecialty(int specialtyCode, const string& outputFilename);
void changeSpecialtyCodeByName(const string& specialtyName, int newCode);
>>>>>>> 777ce26fb592fade697eeabedea7d997d75bb942

#endif // FILE_OPERATIONS_H
