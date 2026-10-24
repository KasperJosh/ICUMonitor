
#include "Patient.h"
#include <iostream>

namespace ICU {

    Patient::Patient()
        : patientID("Unknown"),
          name("Unknown"),
          age(0),
          vitalSigns()
    {
    }

    Patient::Patient(
        const std::string& patientID,
        const std::string& name,
        int age)
        : patientID(patientID),
          name(name),
          age(age),
          vitalSigns()
    {
    }

    std::string Patient::getPatientID() const {
        return patientID;
    }

    std::string Patient::getName() const {
        return name;
    }

    int Patient::getAge() const {
        return age;
    }

    VitalSigns& Patient::getVitalSigns() {
        return vitalSigns;
    }

    const VitalSigns& Patient::getVitalSigns() const {
        return vitalSigns;
    }

    void Patient::displayPatientInfo() const {
        std::cout << "\n===== PATIENT INFORMATION =====\n";
        std::cout << "Patient ID: " << patientID << '\n';
        std::cout << "Name: " << name << '\n';
        std::cout << "Age: " << age << '\n';
    }
}
