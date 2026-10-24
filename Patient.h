
#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include "VitalSigns.h"

namespace ICU {

    class Patient {
    private:
        std::string patientID;
        std::string name;
        int age;
        VitalSigns vitalSigns;

    public:
        // Constructors
        Patient();
        Patient(const std::string& patientID,
                const std::string& name,
                int age);

        // Getters
        std::string getPatientID() const;
        std::string getName() const;
        int getAge() const;

        // Access the patient's vital signs
        VitalSigns& getVitalSigns();
        const VitalSigns& getVitalSigns() const;

        // Display patient information
        void displayPatientInfo() const;
    };
}

#endif
