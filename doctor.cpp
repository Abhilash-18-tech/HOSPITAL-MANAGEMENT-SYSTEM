#include "doctor.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const string DOCTORS_FILE = "doctors.txt";

void DoctorManager::showDoctors() {
    ifstream file(DOCTORS_FILE);
    if (!file) {
        cout << "No doctors found.\n";
        return;
    }

    cout << "\n--- Doctor Availability ---\n";
    string line;
    int idx = 1;
    while (getline(file, line)) {
        if (line.size() == 0) continue;
        stringstream ss(line);
        string name, spec, avail;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, spec, ',')) spec = "";
        if (!getline(ss, avail)) avail = "1";
        cout << idx++ << ". " << name << " - " << spec << " - " << (avail == "1" ? "Available ✅" : "Not Available ❌") << "\n";
    }
    file.close();
}

void DoctorManager::addDoctor() {
    string name, spec;
    cout << "Enter Doctor Name (use underscores for spaces): ";
    cin >> name;
    cout << "Enter Specialty (no spaces): ";
    cin >> spec;

    ofstream file(DOCTORS_FILE, ios::app);
    if (!file) {
        cout << "Error opening doctors file.\n";
        return;
    }
    file << name << "," << spec << ",1\n"; // default to available
    file.close();
    cout << " Doctor added and marked Available.\n";
}

void DoctorManager::removeDoctor() {
    string target;
    cout << "Enter Doctor Name to remove (exact, use underscores if used): ";
    cin >> target;

    ifstream file(DOCTORS_FILE);
    if (!file) {
        cout << "No doctors file found.\n";
        return;
    }
    ofstream temp("temp_doctors.txt");
    if (!temp) {
        cout << "Cannot create temporary file.\n";
        file.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.size() == 0) continue;
        stringstream ss(line);
        string name;
        if (!getline(ss, name, ',')) continue;
        if (name == target) {
            found = true;
            continue; // skip (remove)
        }
        temp << line << "\n";
    }

    file.close();
    temp.close();

    // replace file
    remove(DOCTORS_FILE.c_str());
    rename("temp_doctors.txt", DOCTORS_FILE.c_str());

    if (found) cout << " Doctor removed successfully.\n";
    else cout << "Doctor not found.\n";
}
