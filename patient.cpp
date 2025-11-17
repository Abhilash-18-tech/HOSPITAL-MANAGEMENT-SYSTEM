#include "patient.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>   // for remove/rename
using namespace std;

// === change this path if your project folder is different ===
const string FILE_PATH = "patients.txt";

// Add new patient (appends to file)
void Patient::addPatient() {
    cout << "Enter Patient ID: ";
    cin >> id;
    cout << "Enter Name (no spaces, or use underscores): ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Disease (no spaces): ";
    cin >> disease;

    ofstream file(FILE_PATH, ios::app);
    if (!file) {
        cout << " Error opening file: " << FILE_PATH << endl;
        return;
    }

    file << id << "," << name << "," << age << "," << disease << "\n";
    file.close();
    cout << " Patient record added successfully!\n";
}

// Display all patients (reads file line by line)
void Patient::displayPatients() {
    ifstream file(FILE_PATH);
    if (!file) {
        cout << " No patient records found (or cannot open file).\n";
        return;
    }

    cout << "\n--- Patient List ---\n";
    string line;
    while (getline(file, line)) {
        if(line.size() == 0) continue;
        cout << line << '\n';
    }
    file.close();
}

// Search patient by ID
void Patient::searchPatientById() {
    int searchID;
    cout << "Enter Patient ID to search: ";
    cin >> searchID;

    ifstream file(FILE_PATH);
    if (!file) {
        cout << " No patient records found (or cannot open file).\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if(line.size() == 0) continue;
        stringstream ss(line);
        int fid, fage;
        char comma;
        string fname, fdisease;

        // parse id,name,age,disease
        if (!(ss >> fid)) continue;
        ss >> comma;
        if (!getline(ss, fname, ',')) continue; // read until next comma
        // fname may include commas/spaces depending — the above reads until comma
        // Now ss currently has "age,disease"
        string rest;
        if (!getline(ss, rest)) continue;
        // rest should be like "age,disease" — parse using another stringstream
        stringstream ss2(rest);
        ss2 >> fage;
        ss2 >> comma;
        if (!getline(ss2, fdisease)) fdisease = "";

        if (fid == searchID) {
            cout << "\n Patient Found:\n";
            cout << "ID: " << fid << "\nName: " << fname << "\nAge: " << fage << "\nDisease: " << fdisease << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << " Patient Not Found!\n";
    file.close();
}

// Update patient by ID
void Patient::updatePatient() {
    int searchID;
    cout << "Enter Patient ID to update: ";
    cin >> searchID;

    ifstream file(FILE_PATH);
    if (!file) {
        cout << " No patient records found (or cannot open file).\n";
        return;
    }

    ofstream temp("temp_patients.txt");
    if (!temp) {
        cout << " Cannot create temporary file.\n";
        file.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if(line.size() == 0) continue;
        stringstream ss(line);
        int fid, fage;
        char comma;
        string fname, fdisease;

        if (!(ss >> fid)) continue;
        ss >> comma;
        if (!getline(ss, fname, ',')) continue;
        string rest;
        if (!getline(ss, rest)) continue;
        stringstream ss2(rest);
        ss2 >> fage;
        ss2 >> comma;
        if (!getline(ss2, fdisease)) fdisease = "";

        if (fid == searchID) {
            found = true;
            cout << "Enter New Name (no spaces): ";
            cin >> fname;
            cout << "Enter New Age: ";
            cin >> fage;
            cout << "Enter New Disease (no spaces): ";
            cin >> fdisease;
        }
        temp << fid << "," << fname << "," << fage << "," << fdisease << "\n";
    }

    file.close();
    temp.close();

    // replace original file with temp
    if (remove(FILE_PATH.c_str()) != 0) {
        // Could not remove original (maybe it didn't exist) — try rename anyway
        // but continue
    }
    rename("temp_patients.txt", FILE_PATH.c_str());

    if (found) cout << " Patient Updated Successfully!\n";
    else cout << " Patient Not Found!\n";
}

// Delete patient by ID
void Patient::deletePatient() {
    int searchID;
    cout << "Enter Patient ID to delete: ";
    cin >> searchID;

    ifstream file(FILE_PATH);
    if (!file) {
        cout << " No patient records found (or cannot open file).\n";
        return;
    }

    ofstream temp("temp_patients.txt");
    if (!temp) {
        cout << " Cannot create temporary file.\n";
        file.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if(line.size() == 0) continue;
        stringstream ss(line);
        int fid, fage;
        char comma;
        string fname, fdisease;

        if (!(ss >> fid)) continue;
        ss >> comma;
        if (!getline(ss, fname, ',')) continue;
        string rest;
        if (!getline(ss, rest)) continue;
        stringstream ss2(rest);
        ss2 >> fage;
        ss2 >> comma;
        if (!getline(ss2, fdisease)) fdisease = "";

        if (fid == searchID) {
            found = true;
            // skip writing this line (delete)
            continue;
        }
        temp << fid << "," << fname << "," << fage << "," << fdisease << "\n";
    }

    file.close();
    temp.close();

    // replace original file
    if (remove(FILE_PATH.c_str()) != 0) {
        // ignore remove error
    }
    rename("temp_patients.txt", FILE_PATH.c_str());

    if (found) cout << " Patient Deleted Successfully!\n";
    else cout << " Patient Not Found!\n";
}
