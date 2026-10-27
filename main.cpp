#include <iostream>
#include <iomanip>
#include <limits>

#include "Patient.h"
#include "AlarmManager.h"
#include "VitalHistory.h"

// Console interface helpers. All clinical rules remain in VitalSigns/AlarmManager.
void displayMenu() {
    std::cout << "\n===== ICU PATIENT MONITOR =====\n"
              << "1. Enter Vital Signs\n"
              << "2. Display Vital Signs\n"
              << "3. Display Assessment\n"
              << "4. Display Calculations\n"
              << "5. Display Vital Signs History\n"
              << "6. Display Patient Information\n"
              << "7. Display Active Alarms\n"
              << "8. Exit\n"
              << "Choice: ";
}

// Returns false when input cannot be read as an integer.
bool readMenuChoice(int& choice) {
    if (std::cin >> choice) {
        return true;
    }
    if (std::cin.eof()) {
        return false;
    }
    std::cout << "Invalid input. Enter a number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

// Small input helpers stop at the first invalid measurement.
bool readInt(const char* prompt, int& value) {
    std::cout << prompt;
    return static_cast<bool>(std::cin >> value);
}

bool readDouble(const char* prompt, double& value) {
    std::cout << prompt;
    return static_cast<bool>(std::cin >> value);
}

// Read a complete set before changing the patient's actual measurements.
void enterVitalSigns(ICU::VitalSigns& vitals, ICU::AlarmManager& alarms,
                     ICU::VitalHistory& history) {
    int systolicBP{};
    int diastolicBP{};
    int heartRate{};
    int spo2{};
    int respRate{};
    double temperature{};

    std::cout << "\n===== ENTER VITAL SIGNS =====\n";
    bool inputOK =
        readInt("Enter Systolic BP: ", systolicBP) &&
        readInt("Enter Diastolic BP: ", diastolicBP) &&
        readInt("Enter Heart Rate: ", heartRate) &&
        readInt("Enter SpO2: ", spo2) &&
        readInt("Enter Respiratory Rate: ", respRate) &&
        readDouble("Enter Temperature: ", temperature);

    if (!inputOK) {
        std::cout << "Invalid numeric input. No changes saved.\n";
        if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return;
    }

    ICU::VitalSigns candidate(heartRate, spo2, systolicBP,
                              diastolicBP, respRate, temperature);
    bool valid = candidate.isValidHeartRate() &&
                 candidate.isValidSpO2() &&
                 candidate.isValidBloodPressure() &&
                 candidate.isValidRR() &&
                 candidate.isValidTemp() &&
                 systolicBP > diastolicBP;

    if (!valid) {
        std::cout << "Invalid vital signs. No changes saved.\n";
        return;
    }

    vitals.setSystolicBP(systolicBP);
    vitals.setDiastolicBP(diastolicBP);
    vitals.setHeartRate(heartRate);
    vitals.setSpO2(spo2);
    vitals.setRespRate(respRate);
    vitals.setTemperature(temperature);
    history.addReading(vitals);

    alarms.evaluate(vitals);
    std::cout << "\nVital signs updated successfully!\n";
    if (alarms.getAlarmCount() > 0) {
        std::cout << "WARNING: " << alarms.getAlarmCount()
                  << " active alarm(s) detected.\n";
    } else {
        std::cout << "No active alarms.\n";
    }
}

void displayAssessment(const ICU::VitalSigns& vitals) {
    std::cout << "\n===== ASSESSMENT =====\n" << std::left;

    if (vitals.isValidBloodPressure() &&
        vitals.getSystolicBP() > vitals.getDiastolicBP()) {
        vitals.checkBP();
    } else {
        std::cout << "Invalid Blood Pressure\n";
    }

    if (vitals.isValidHeartRate()) vitals.checkHeartRate();
    else std::cout << "Invalid Heart Rate\n";

    if (vitals.isValidSpO2()) vitals.checkSpO2();
    else std::cout << "Invalid SpO2\n";

    if (vitals.isValidRR()) vitals.checkRespRate();
    else std::cout << "Invalid Respiratory Rate\n";

    if (vitals.isValidTemp()) vitals.checkTemperature();
    else std::cout << "Invalid Temperature\n";
}

void displayCalculations(const ICU::VitalSigns& vitals) {
    std::cout << "\n===== CALCULATIONS =====\n" << std::left;
    bool bpValid = vitals.isValidBloodPressure() &&
                   vitals.getSystolicBP() > vitals.getDiastolicBP();

    if (bpValid) {
        std::cout << std::setw(20) << "MAP: "
                  << vitals.calculateMAP() << " mmHg\n";
        std::cout << std::setw(20) << "Pulse Pressure: "
                  << vitals.calculatePulsePressure() << " mmHg\n";
    } else {
        std::cout << "BP calculations unavailable.\n";
    }

    if (bpValid && vitals.isValidHeartRate()) {
        std::cout << std::setw(20) << "Shock Index: "
                  << vitals.calculateShockIndex() << '\n';
    } else {
        std::cout << "Shock Index unavailable.\n";
    }
}

void displayVitalHistory(const ICU::VitalHistory& history) {
    history.displayHistory();
    history.displayHeartRateSummary();
}

void displayActiveAlarms(const ICU::VitalSigns& vitals,
                         ICU::AlarmManager& alarms) {
    alarms.evaluate(vitals);
    alarms.displayAlarms();
    std::cout << "\nTotal Active Alarms: " << alarms.getAlarmCount() << '\n';
}

int main() {
    ICU::Patient patient("P001", "Patient A", 65);
    ICU::VitalSigns& patientVitals = patient.getVitalSigns();
    ICU::AlarmManager alarmManager;
    ICU::VitalHistory history;

    // Demonstration readings: the program begins with valid sample measurements.
    patientVitals.setHeartRate(80);
    patientVitals.setSpO2(90);
    patientVitals.setSystolicBP(120);
    patientVitals.setDiastolicBP(80);
    patientVitals.setRespRate(16);
    patientVitals.setTemperature(37.0);
    history.addReading(patientVitals); // Record the initial demonstration values

    std::cout << std::fixed << std::setprecision(2);
    patient.displayPatientInfo();
    patientVitals.displayVitalSigns();

    while (true) {
        displayMenu();
        int choice = 0;
        if (!readMenuChoice(choice)) {
            if (std::cin.eof()) break;
            continue;
        }

        switch (choice) {
            case 1: enterVitalSigns(patientVitals, alarmManager, history); break;
            case 2: patientVitals.displayVitalSigns(); break;
            case 3: displayAssessment(patientVitals); break;
            case 4: displayCalculations(patientVitals); break;
            case 5: displayVitalHistory(history); break;
            case 6: patient.displayPatientInfo(); break;
            case 7: displayActiveAlarms(patientVitals, alarmManager); break;
            case 8:
                std::cout << "\nExiting ICU Monitor...\n";
                return 0;
            default: std::cout << "Invalid menu option.\n";
        }
        if (std::cin.eof()) break;
    }
    return 0;
}
