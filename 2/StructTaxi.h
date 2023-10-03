#ifndef UNTITLED3_STRUCTTAXI_H
#define UNTITLED3_STRUCTTAXI_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct TaxiCallRecord {
    int callNumber;
    char driverLastName[50];
    char departureTime[20];
    bool inGarage;
};

void convertTextToBinary(const string& textFilename, const string& binaryFilename) {
    ifstream input(textFilename);
    if (!input) {
        cerr << "Failed to open the input file." << endl;
        return;
    }

    ofstream output(binaryFilename, ios::binary);
    if (!output) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    TaxiCallRecord record;
    while (input >> record.callNumber >> record.driverLastName >> record.departureTime >> record.inGarage) {
        output.write(reinterpret_cast<const char*>(&record), sizeof(TaxiCallRecord));
    }

    input.close();
    output.close();
}

void convertBinaryToText(const string& binaryFilename, const string& textFilename) {
    ifstream input(binaryFilename, ios::binary);
    if (!input) {
        cerr << "Failed to open the input file." << endl;
        return;
    }

    ofstream output(textFilename);
    if (!output) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    TaxiCallRecord record;
    while (input.read(reinterpret_cast<char*>(&record), sizeof(TaxiCallRecord))) {
        output << record.callNumber << "\n" << record.driverLastName << "\n" << record.departureTime << "\n" << record.inGarage << "\n";
    }

    input.close();
    output.close();
}

void displayAllRecords(const string& binaryFilename) {
    ifstream input(binaryFilename, ios::binary);
    if (!input) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    TaxiCallRecord record;
    while (input.read(reinterpret_cast<char*>(&record), sizeof(TaxiCallRecord))) {
        cout << "Call Number: " << record.callNumber << ", Driver Last Name: " << record.driverLastName
                  << ", Departure Time: " << record.departureTime << ", In Garage: " << record.inGarage << endl;
    }

    input.close();
}

TaxiCallRecord getRecordByNumber(const string& binaryFilename, int recordNumber) {
    ifstream input(binaryFilename, ios::binary);
    TaxiCallRecord record;
    record.callNumber = -1; // Initialize to an invalid value

    if (!input) {
        cerr << "Failed to open the file." << endl;
        return record;
    }

    while (input.read(reinterpret_cast<char*>(&record), sizeof(TaxiCallRecord))) {
        if (record.callNumber == recordNumber) {
            input.close();
            return record;
        }
    }

    cerr << "Record not found." << endl;
    input.close();
    return record;
}

bool deleteRecordByCallNumber(const string& binaryFilename, int callNumber) {
    ifstream input(binaryFilename, ios::binary);
    if (!input) {
        cerr << "Failed to open the file." << endl;
        return false;
    }

    ofstream tempOutput("temp.bin", ios::binary);
    if (!tempOutput) {
        cerr << "Failed to create a temporary file." << endl;
        input.close();
        return false;
    }

    TaxiCallRecord record;
    bool recordFound = false;

    while (input.read(reinterpret_cast<char*>(&record), sizeof(TaxiCallRecord))) {
        if (record.callNumber != callNumber) {
            tempOutput.write(reinterpret_cast<const char*>(&record), sizeof(TaxiCallRecord));
        } else {
            recordFound = true;
        }
    }

    input.close();
    tempOutput.close();

    if (recordFound) {
        if (remove(binaryFilename.c_str()) != 0) {
            cerr << "Error deleting the original file." << endl;
            return false;
        }
        if (rename("temp.bin", binaryFilename.c_str()) != 0) {
            cerr << "Error renaming the temporary file." << endl;
            return false;
        }
        cout << "Record with call number " << callNumber << " deleted successfully." << endl;
        return true;
    } else {
        cerr << "Record with call number " << callNumber << " not found." << endl;
        remove("temp.bin");
        return false;
    }
}

void startTaxi(){
    string binaryFilename, textFilename;
    int choice;

    cout << "Enter the binary file name: ";
    cin >> binaryFilename;

    cout << "Enter the text file name: ";
    cin >> textFilename;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Convert text to binary\n";
        cout << "2. Convert binary to text\n";
        cout << "3. Display all records\n";
        cout << "4. Get record by call number\n";
        cout << "5. Delete record by call number\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                convertTextToBinary(textFilename, binaryFilename);
                cout << "Conversion completed.\n";
                break;
            case 2:
                convertBinaryToText(binaryFilename, textFilename);
                cout << "Conversion completed.\n";
                break;
            case 3:
                displayAllRecords(binaryFilename);
                break;
            case 4:
                int recordNumber;
                cout << "Enter the record number: ";
                cin >> recordNumber;
                {
                    TaxiCallRecord record = getRecordByNumber(binaryFilename, recordNumber);
                    cout << "Record found: Call Number: " << record.callNumber << ", Driver Last Name: " << record.driverLastName
                              << ", Departure Time: " << record.departureTime << ", In Garage: " << record.inGarage << "\n";
                }
                break;
            case 5:
                int callNumberToDelete;
                cout << "Enter the call number to delete: ";
                cin >> callNumberToDelete;
                deleteRecordByCallNumber(binaryFilename, callNumberToDelete);
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

#endif //UNTITLED3_STRUCTTAXI_H
