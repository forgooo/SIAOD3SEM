#ifndef UNTITLED3_FILESFUNCS_H
#define UNTITLED3_FILESFUNCS_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

void createFile(const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.is_open() && file.good()) {
        for (int i = 1; i <= 10; ++i) {
            file << i << "\n";
        }
        std::cout << "File created successfully.\n";
        file.close();
    }
    else {
        std::cout << "Unable to create file.\n";
    }
}

void displayFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    if (file.is_open() && file.good()) {
        std::cout << "File contents:\n";
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file or read its contents.\n";
    }
}

void addRecord(const std::string& fileName, int number) {
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open() && file.good()) {
        file << number << "\n";
        std::cout << "Record added successfully.\n";
        file.close();
    }
    else {
        std::cout << "Unable to open file for adding a record.\n";
    }
}

int readNumberAtPosition(const std::string& fileName, int position) {
    std::ifstream file(fileName);
    int number;
    int currentPosition = 0;

    if (file.is_open() && file.good()) {
        while (currentPosition < position && file >> number) {
            ++currentPosition;
        }

        file.close();

        if (currentPosition == position) {
            return number;
        }
        else {
            std::cout << "Invalid position or unable to read number.\n";
            return -1;
        }
    }
    else {
        std::cout << "Unable to open file or read number.\n";
        return -1;
    }
}

int countNumbers(const std::string& fileName) {
    std::ifstream file(fileName);
    int count = 0;
    int number;

    if (file.is_open() && file.good()) {
        while (file >> number) {
            ++count;
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file.\n";
    }

    return count;
}

void copyFileWithCount(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Unable to open files.\n";
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        int count = 0;

        while (iss >> number) {
            count++;
        }

        outputFile << count << " ";
        iss.clear();
        iss.seekg(0);
        while (iss >> number) {
            outputFile << number << " ";
        }
        outputFile << "\n";
    }

    std::cout << "New file created successfully.\n";

    inputFile.close();
    outputFile.close();
}

std::string getFileName() {
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    return fileName;
}

void start() {
    int choice = -1;

    while (choice) {
        std::cout << "Menu:\n";
        std::cout << "1. Create a new file\n";
        std::cout << "2. Display file contents\n";
        std::cout << "3. Add a record\n";
        std::cout << "4. Read a number at a position\n";
        std::cout << "5. Count numbers in the file\n";
        std::cout << "6. Copy with count\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string fileName = getFileName();
                if (!fileExists(fileName)) {
                    createFile(fileName);
                } else {
                    std::cout << "File already exists. Choose another name.\n";
                }
                break;
            }
            case 2: {
                std::string fileName = getFileName();
                if (fileExists(fileName)) {
                    displayFile(fileName);
                } else {
                    std::cout << "File not found.\n";
                }
                break;
            }
            case 3: {
                int number;
                std::string fileName = getFileName();
                if (fileExists(fileName)) {
                    std::cout << "Enter the number to add: ";
                    std::cin >> number;
                    addRecord(fileName, number);
                } else {
                    std::cout << "File not found.\n";
                }
                break;
            }
            case 4: {
                int position, number;
                std::string fileName = getFileName();
                if (fileExists(fileName)) {
                    std::cout << "Enter the position: ";
                    std::cin >> position;
                    number = readNumberAtPosition(fileName, position);
                    if (number != -1)
                        std::cout << "Number at position " << position << ": " << number << "\n";
                } else {
                    std::cout << "File not found.\n";
                }
                break;
            }
            case 5: {
                std::string fileName = getFileName();
                if (fileExists(fileName)) {
                    std::cout << "Number of numbers in the file: " << countNumbers(fileName) << "\n";
                } else {
                    std::cout << "File not found.\n";
                }
                break;
            }
            case 6:{
                std::string file, newFile;
                std::cout << "Enter exsisting file name: ";
                std::cin >> file;
                std::cout << "Enter new file name: ";
                std::cin >> newFile;
                copyFileWithCount(file, newFile);
                std::cout << "done\n";
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}

#endif