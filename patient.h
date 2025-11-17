#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
private:
    int id;
    std::string name;
    int age;
    std::string disease;

public:
    // CRUD operations
    void addPatient();
    void displayPatients();
    void searchPatientById();
    void updatePatient();
    void deletePatient();
};

#endif // PATIENT_H
