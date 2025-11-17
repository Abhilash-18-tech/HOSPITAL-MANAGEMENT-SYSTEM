#include <iostream>
#include "patient.h"
#include "doctor.h"
#include "bed.h"
#include <fstream>
using namespace std;

int main() {
    Patient p;
    int choice;

    while (true) {
        cout << "\n--- Hospital System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Update Patient\n";
        cout << "5. Delete Patient\n";
        cout << "6. Doctor Availability\n";
        cout << "7. Join Doctor\n";
        cout << "8. Leaving Doctor\n";
        cout << "9. Bed Availability\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        DoctorManager dm;
        BedManager bm;

        switch (choice) {
            case 1: p.addPatient(); break;
            case 2: p.displayPatients(); break;
            case 3: p.searchPatientById(); break;
            case 4: p.updatePatient(); break;
            case 5: p.deletePatient(); break;
            case 6: dm.showDoctors(); break;
            case 7: dm.addDoctor(); break;
            case 8: dm.removeDoctor(); break;
            case 9: {
                int sub;
                while (true) {
                    cout << "\n--- Bed Menu ---\n";
                    cout << "1. Show Beds\n";
                    cout << "2. Admit Patient with Bed\n";
                    cout << "3. Discharge Patient from Bed\n";
                    cout << "4. Back\n";
                    cout << "Enter choice: ";
                    if (!(cin >> sub)) { cin.clear(); cin.ignore(10000,'\n'); cout << "Invalid input\n"; continue; }
                    if (sub == 1) bm.showBeds();
                    else if (sub == 2) bm.admitPatientWithBed();
                    else if (sub == 3) bm.dischargePatientWithBed();
                    else if (sub == 4) break;
                    else cout << "Invalid choice.\n";
                }
            } break;
            case 10: cout << " Thank you! Exiting...\n"; return 0;
            default: cout << " Invalid Choice! Try again.\n";
        }
    }

    return 0;
}
