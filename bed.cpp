#include "bed.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const string BEDS_FILE = "beds.txt";
const string PATIENTS_FILE = "patients.txt";

static void ensureBedsFile() {
    ifstream f(BEDS_FILE);
    if (!f) {
        ofstream o(BEDS_FILE);
        if (o) {
            o << 50 << "," << 0 << "\n"; // default: 50 total, 0 occupied
            o.close();
        }
    } else {
        f.close();
    }
}

void BedManager::showBeds() {
    ensureBedsFile();
    ifstream file(BEDS_FILE);
    if (!file) {
        cout << "Cannot read beds file.\n";
        return;
    }
    int total, occupied;
    char comma;
    if (!(file >> total)) { file.close(); cout << "Invalid beds file.\n"; return; }
    file >> comma;
    if (!(file >> occupied)) occupied = 0;
    file.close();

    cout << "\n--- Bed Availability ---\n";
    cout << "Total Beds: " << total << "\n";
    cout << "Occupied Beds: " << occupied << "\n";
    cout << "Available Beds: " << (total - occupied) << "\n";
}

void BedManager::admitPatientWithBed() {
    ensureBedsFile();
    
    // Ask for patient info
    int patientID;
    string patientName, age_str, disease;
    int age;
    
    cout << "Enter Patient ID: ";
    cin >> patientID;
    cout << "Enter Patient Name (no spaces, or use underscores): ";
    cin >> patientName;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Disease (no spaces): ";
    cin >> disease;
    
    // Check bed availability
    ifstream bedfile(BEDS_FILE);
    int total, occupied;
    char comma;
    bedfile >> total;
    bedfile >> comma;
    bedfile >> occupied;
    bedfile.close();
    
    if (occupied >= total) {
        cout << "No beds available to admit patient.\n";
        return;
    }
    
    // Occupy a bed
    occupied++;
    ofstream bedout(BEDS_FILE);
    bedout << total << "," << occupied << "\n";
    bedout.close();
    
    // Add patient to patients.txt
    ofstream patfile(PATIENTS_FILE, ios::app);
    if (!patfile) {
        cout << " Error opening patients file.\n";
        return;
    }
    patfile << patientID << "," << patientName << "," << age << "," << disease << "\n";
    patfile.close();
    
    cout << " Patient admitted to bed. ID: " << patientID << ", Name: " << patientName << "\n";
    cout << "   Occupied Beds: " << occupied << "/" << total << "\n";
}

void BedManager::dischargePatientWithBed() {
    ensureBedsFile();
    
    int patientID;
    cout << "Enter Patient ID to discharge: ";
    cin >> patientID;
    
    // Check if patient exists in patients.txt
    ifstream patfile(PATIENTS_FILE);
    if (!patfile) {
        cout << " No patient records found.\n";
        return;
    }
    
    ofstream tempfile("temp_patients.txt");
    if (!tempfile) {
        cout << " Cannot create temporary file.\n";
        patfile.close();
        return;
    }
    
    string line;
    bool found = false;
    while (getline(patfile, line)) {
        if (line.size() == 0) continue;
        stringstream ss(line);
        int fid;
        if (!(ss >> fid)) continue;
        
        if (fid == patientID) {
            found = true;
            // Skip writing this line (discharge/remove from beds)
            continue;
        }
        tempfile << line << "\n";
    }
    
    patfile.close();
    tempfile.close();
    
    if (!found) {
        cout << " Patient not found.\n";
        remove("temp_patients.txt");
        return;
    }
    
    // Update beds.txt (free a bed)
    ifstream bedfile(BEDS_FILE);
    int total, occupied;
    char comma;
    bedfile >> total;
    bedfile >> comma;
    bedfile >> occupied;
    bedfile.close();
    
    if (occupied > 0) occupied--;
    
    ofstream bedout(BEDS_FILE);
    bedout << total << "," << occupied << "\n";
    bedout.close();
    
    // Replace patients file with temp
    remove(PATIENTS_FILE.c_str());
    rename("temp_patients.txt", PATIENTS_FILE.c_str());
    
    cout << " Patient discharged. ID: " << patientID << "\n";
    cout << "   Occupied Beds: " << occupied << "/" << total << "\n";
}
