
#include <iostream>
#include <iomanip>
#include <limits>

#include "VitalSigns.h"
#include "Patient.h"
#include "AlarmManager.h"

int main()
{
    // =====================================================
    // 1. CREATE PATIENT AND MONITORING OBJECTS
    // =====================================================

    ICU::Patient patient("P001", "Patient A", 65);

    // Reference to the VitalSigns object owned by Patient
    ICU::VitalSigns& patientVitals = patient.getVitalSigns();

    // Create alarm manager
    ICU::AlarmManager alarmManager;

    // Initialize sample measurements
    patientVitals.setHeartRate(80);
    patientVitals.setSpO2(90);
    patientVitals.setSystolicBP(120);
    patientVitals.setDiastolicBP(80);
    patientVitals.setRespRate(16);
    patientVitals.setTemperature(37.0);

    // Sample vital signs already exist
    bool vitalsEntered = true;

    // Display initial patient information
    patient.displayPatientInfo();
    patientVitals.displayVitalSigns();

    // =====================================================
    // 2. VARIABLES FOR USER INPUT
    // =====================================================

    int systolicBP{};
    int diastolicBP{};
    int heartRate{};
    int spo2{};
    int respRate{};
    double temperature{};

    int choice = 0;

    // Format decimal calculations
    std::cout << std::fixed << std::setprecision(2);

    // =====================================================
    // 3. MAIN MENU
    // =====================================================

    do {
        std::cout << "\n===== ICU PATIENT MONITOR =====\n";
        std::cout << "1. Enter Vital Signs\n";
        std::cout << "2. Display Vital Signs\n";
        std::cout << "3. Display Assessment\n";
        std::cout << "4. Display Calculations\n";
        std::cout << "5. Display Heart Rate History\n";
        std::cout << "6. Display Patient Information\n";
        std::cout << "7. Display Active Alarms\n";
        std::cout << "8. Exit\n";
        std::cout << "Choice: ";

        // Validate menu input
        if (!(std::cin >> choice)) {

            if (std::cin.eof()) {
                break;
            }

            std::cout << "Invalid input. Enter a number.\n";

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            continue;
        }

        // =================================================
        // OPTION 1 - ENTER VITAL SIGNS
        // =================================================

        if (choice == 1) {

            std::cout << "\n===== ENTER VITAL SIGNS =====\n";

            std::cout << "Enter Systolic BP: ";
            std::cin >> systolicBP;

            if (std::cin) {
                std::cout << "Enter Diastolic BP: ";
                std::cin >> diastolicBP;
            }

            if (std::cin) {
                std::cout << "Enter Heart Rate: ";
                std::cin >> heartRate;
            }

            if (std::cin) {
                std::cout << "Enter SpO2: ";
                std::cin >> spo2;
            }

            if (std::cin) {
                std::cout << "Enter Respiratory Rate: ";
                std::cin >> respRate;
            }

            if (std::cin) {
                std::cout << "Enter Temperature: ";
                std::cin >> temperature;
            }

            // Check input failure
            if (!std::cin) {

                if (std::cin.eof()) {
                    break;
                }

                std::cout << "Invalid numeric input.\n";
                std::cout << "No changes saved.\n";

                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );

                continue;
            }

            // Create temporary candidate for validation
            ICU::VitalSigns candidate(
                heartRate,
                spo2,
                systolicBP,
                diastolicBP,
                respRate,
                temperature
            );

            bool valid =
                candidate.isValidHeartRate() &&
                candidate.isValidSpO2() &&
                candidate.isValidBloodPressure() &&
                candidate.isValidRR() &&
                candidate.isValidTemp() &&
                systolicBP > diastolicBP;

            // Reject invalid measurements
            if (!valid) {
                std::cout << "\nInvalid vital signs.\n";
                std::cout << "No changes saved.\n";
                continue;
            }

            // Update patient's actual measurements
            patientVitals.setSystolicBP(systolicBP);
            patientVitals.setDiastolicBP(diastolicBP);
            patientVitals.setHeartRate(heartRate);
            patientVitals.setSpO2(spo2);
            patientVitals.setRespRate(respRate);
            patientVitals.setTemperature(temperature);

            // Save valid heart rate to history
            patientVitals.addHeartRateReading(heartRate);

            vitalsEntered = true;

            std::cout << "\nVital signs updated successfully!\n";

            // Evaluate alarms after updating
            alarmManager.evaluate(patientVitals);

            if (alarmManager.getAlarmCount() > 0) {
                std::cout << "\nWARNING: "
                          << alarmManager.getAlarmCount()
                          << " active alarm(s) detected.\n";
            }
            else {
                std::cout << "No active alarms.\n";
            }
        }

        // =================================================
        // OPTION 2 - DISPLAY VITAL SIGNS
        // =================================================

        else if (choice == 2) {

            if (vitalsEntered) {
                patientVitals.displayVitalSigns();
            }
            else {
                std::cout << "Please enter vital signs first.\n";
            }
        }

        // =================================================
        // OPTION 3 - DISPLAY ASSESSMENT
        // =================================================

        else if (choice == 3) {

            if (vitalsEntered) {

                std::cout << "\n===== ASSESSMENT =====\n";
                std::cout << std::left;

                // Blood Pressure
                if (patientVitals.isValidBloodPressure() &&
                    patientVitals.getSystolicBP() >
                    patientVitals.getDiastolicBP()) {

                    patientVitals.checkBP();
                }
                else {
                    std::cout << "Invalid Blood Pressure\n";
                }

                // Heart Rate
                if (patientVitals.isValidHeartRate()) {
                    patientVitals.checkHeartRate();
                }
                else {
                    std::cout << "Invalid Heart Rate\n";
                }

                // Oxygen Saturation
                if (patientVitals.isValidSpO2()) {
                    patientVitals.checkSpO2();
                }
                else {
                    std::cout << "Invalid SpO2\n";
                }

                // Respiratory Rate
                if (patientVitals.isValidRR()) {
                    patientVitals.checkRespRate();
                }
                else {
                    std::cout << "Invalid Respiratory Rate\n";
                }

                // Temperature
                if (patientVitals.isValidTemp()) {
                    patientVitals.checkTemperature();
                }
                else {
                    std::cout << "Invalid Temperature\n";
                }
            }
            else {
                std::cout << "Please enter vital signs first.\n";
            }
        }

        // =================================================
        // OPTION 4 - DISPLAY CALCULATIONS
        // =================================================

        else if (choice == 4) {

            if (vitalsEntered) {

                std::cout << "\n===== CALCULATIONS =====\n";

                std::cout << std::left;

                if (patientVitals.isValidBloodPressure() &&
                    patientVitals.getSystolicBP() >
                    patientVitals.getDiastolicBP()) {

                    std::cout << std::setw(20)
                              << "MAP: "
                              << patientVitals.calculateMAP()
                              << " mmHg\n";

                    std::cout << std::setw(20)
                              << "Pulse Pressure: "
                              << patientVitals.calculatePulsePressure()
                              << " mmHg\n";
                }
                else {
                    std::cout << "BP calculations unavailable.\n";
                }

                if (patientVitals.isValidHeartRate() &&
                    patientVitals.isValidBloodPressure() &&
                    patientVitals.getSystolicBP() >
                    patientVitals.getDiastolicBP()) {

                    std::cout << std::setw(20)
                              << "Shock Index: "
                              << patientVitals.calculateShockIndex()
                              << '\n';
                }
                else {
                    std::cout << "Shock Index unavailable.\n";
                }
            }
            else {
                std::cout << "Please enter vital signs first.\n";
            }
        }

        // =================================================
        // OPTION 5 - HEART RATE HISTORY
        // =================================================

        else if (choice == 5) {

            patientVitals.displayHeartRateHistory();

            std::cout << std::fixed << std::setprecision(2);

            std::cout << "Average HR: "
                      << patientVitals.calculateAverageHeartRate()
                      << " bpm\n";
        }

        // =================================================
        // OPTION 6 - PATIENT INFORMATION
        // =================================================

        else if (choice == 6) {

            patient.displayPatientInfo();
        }

        // =================================================
        // OPTION 7 - ACTIVE ALARMS
        // =================================================

        else if (choice == 7) {

            if (vitalsEntered) {

                alarmManager.evaluate(patientVitals);

                alarmManager.displayAlarms();

                std::cout << "\nTotal Active Alarms: "
                          << alarmManager.getAlarmCount()
                          << '\n';
            }
            else {
                std::cout << "Please enter vital signs first.\n";
            }
        }

        // =================================================
        // OPTION 8 - EXIT
        // =================================================

        else if (choice == 8) {

            std::cout << "\nExiting ICU Monitor...\n";
        }

        // =================================================
        // INVALID MENU CHOICE
        // =================================================

        else {

            std::cout << "Invalid menu option.\n";
        }

    } while (choice != 8);

    return 0;
}
