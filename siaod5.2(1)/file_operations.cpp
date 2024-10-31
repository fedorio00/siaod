#include "file_operations.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void displayFileContent(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void appendToFile(const string& filename, const string& data) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    file << " " << data;
    file.close();
}

int getNumberByIndex(const string& filename, int index) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    vector<int> numbers;
    int number;
    while (file >> number) {
        numbers.push_back(number);
    }
    file.close();

    if (index < 0 || index >= numbers.size()) {
        return -1;
    }
    return numbers[index];
}

int countNumbersInFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    int count = 0;
    int number;
    while (file >> number) {
        count++;
    }
    file.close();
    return count;
}

int countLinesInFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }
    file.close();
    return count;
}

void createNewFileByRule(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Error opening file: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error opening file: " << outputFilename << endl;
        return;
    }

    vector<int> numbers;
    int number;
    while (inputFile >> number) {
        numbers.push_back(number);
    }

    inputFile.close();
    int size = numbers.size();
    
    // Подсчет количества строк в файле
    int lineCount = countLinesInFile(inputFilename);
    
    // Проверка на деление на ноль
    if (lineCount == 0) {
        cerr << "Error: No lines in the input file." << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        outputFile << static_cast<double>(numbers[i]) / lineCount << " ";
    }
    outputFile.close();
}