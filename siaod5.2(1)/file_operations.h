#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool fileExists(const string& filename);
void displayFileContent(const string& filename);
void appendToFile(const string& filename, const string& data);
int getNumberByIndex(const string& filename, int index);
int countNumbersInFile(const string& filename);
void createNewFileByRule(const string& inputFilename, const string& outputFilename);

#endif // FILE_OPERATIONS_H