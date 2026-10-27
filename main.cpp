#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <fstream>
#include <cmath>
#include "PatientManager.h"

namespace {
const std::string REGISTRY = "patients.csv";

bool readInt(const std::string& prompt, int& value) {
    std::cout << prompt;
    if (std::cin >> value) return true;
    if (!std::cin.eof()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Invalid numeric input.\n";
    return false;
}
bool readDouble(const std::string& prompt, double& value) {
    std::cout << prompt;
    if (std::cin >> value) return true;
    if (!std::cin.eof()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Invalid numeric input.\n";
    return false;
}
void menu(const ICU::PatientSession* selected) {
    std::cout << "\n===== ICU PATIENT MONITOR =====\n"
              << "Selected: " << (selected ? selected->patient.getPatientID() : "None") << '\n'
              << "1. Enter Vital Signs\n2. Display Vital Signs\n3. Display Assessment\n"
              << "4. Display Calculations\n5. Display Vital Signs History\n"
              << "6. Display Patient Information\n7. Display Active Alarms\n"
              << "8. List Patients\n9. Add Patient\n10. Select Patient\n"
              << "11. Remove Patient\n12. Save Data\n13. Exit\n";
}
void inputVitals(ICU::PatientSession& p) {
    int sys{}, dia{}, hr{}, spo{}, rr{}; double t{};
    std::cout << "\n===== ENTER VITAL SIGNS =====\n";
    if (!readInt("Systolic BP: ",sys) || !readInt("Diastolic BP: ",dia) ||
        !readInt("Heart Rate: ",hr) || !readInt("SpO2: ",spo) ||
        !readInt("Respiratory Rate: ",rr) || !readDouble("Temperature: ",t)) return;
    ICU::VitalSigns candidate(hr,spo,sys,dia,rr,t);
    if (!candidate.isValidHeartRate() || !candidate.isValidSpO2() ||
        !candidate.isValidBloodPressure() || !candidate.isValidRR() ||
        !candidate.isValidTemp() || !std::isfinite(t) || sys <= dia) {
        std::cout << "Invalid measurements. No changes saved.\n";
        return;
    }
    p.patient.getVitalSigns() = candidate;
    p.hasVitals = true;
    p.history.addReading(p.patient.getVitalSigns());
    p.alarms.evaluate(p.patient.getVitalSigns());
    std::cout << "Readings updated. Active alarms: " << p.alarms.getAlarmCount() << '\n';
    if (!p.history.saveToCSV("vitals_" + p.patient.getPatientID() + ".csv"))
        std::cerr << "WARNING: Failed to autosave this patient history.\n";
}
void assessment(const ICU::VitalSigns& v) {
    std::cout << "\n===== ASSESSMENT =====\n" << std::left;
    v.checkBP(); v.checkHeartRate(); v.checkSpO2(); v.checkRespRate(); v.checkTemperature();
}
void calculations(const ICU::VitalSigns& v) {
    std::cout << "\n===== CALCULATIONS =====\n"
              << "MAP: " << v.calculateMAP() << " mmHg\n"
              << "Pulse Pressure: " << v.calculatePulsePressure() << " mmHg\n"
              << "Shock Index: " << v.calculateShockIndex() << '\n';
}
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string result;
    std::getline(std::cin >> std::ws, result);
    return result;
}
void addPatient(ICU::PatientManager& manager, std::string& selectedID) {
    auto id = readLine("New patient ID (letters/numbers/-/_): ");
    auto name = readLine("Patient display name: ");
    int age;
    if (!readInt("Age: ", age)) return;
    if (manager.addPatient(id,name,age)) {
        selectedID = id;
        std::cout << "Patient created and selected.\n";
    } else std::cout << "Could not create patient (invalid, duplicate or previously used ID).\n";
}
bool saveAll(const ICU::PatientManager& manager) {
    // Save each history before writing the registry.
    bool ok = manager.saveAllHistories();
    if (ok) ok = manager.saveRegistry(REGISTRY);
    std::cout << (ok ? "Patient registry and histories saved.\n" : "ERROR saving patient data.\n");
    return ok;
}
}
int main() {
    ICU::PatientManager manager;
    const bool registryExists = static_cast<bool>(std::ifstream(REGISTRY));
    if (registryExists && !manager.loadRegistry(REGISTRY)) {
        std::cerr << "ERROR: patients.csv is damaged or a patient history cannot be loaded.\n"
                  << "No files have been overwritten. Restore from backup first.\n";
        return 1;
    }
    if (registryExists) {
        std::cout << "Saved patients and their histories loaded.\n";
    } else {
        // Migration: preserve the existing P001 history if it exists.
        manager.addPatient("P001", "Patient A", 65, true);
        auto* p = manager.findPatient("P001");
        if (std::ifstream("vitals_P001.csv").good()) {
            if (!p->history.loadFromCSV("vitals_P001.csv")) {
                std::cerr << "ERROR: Invalid legacy P001 history.\n";
                return 1;
            }
            p->hasVitals = p->history.restoreLatest(p->patient.getVitalSigns());
            if (p->hasVitals) p->alarms.evaluate(p->patient.getVitalSigns());
        }
        std::cout << "Started with P001. Previous history loaded if available.\n";
    }
    std::string selectedID = manager.findPatient("P001") ? "P001" : "";
    std::cout << std::fixed << std::setprecision(2);
    while (true) {
        ICU::PatientSession* p = manager.findPatient(selectedID);
        menu(p);
        int choice{};
        if (!readInt("Choice: ",choice)) {
            if (std::cin.eof()) break;
            continue;
        }
        if (choice == 13) { return saveAll(manager) ? 0 : 1; }
        switch (choice) {
            case 8: manager.displayPatients(); break;
            case 9: addPatient(manager, selectedID);
                    if (!saveAll(manager)) std::cerr << "WARNING: Patient registry not saved.\n";
                    break;
            case 10: {
                auto id = readLine("Patient ID to select: ");
                if (manager.findPatient(id)) { selectedID=id; std::cout << "Selected " << id << '\n'; }
                else std::cout << "Patient not found.\n";
                break;
            }
            case 11: {
                auto id = readLine("Patient ID to remove: ");
                // Delete persisted file only after an explicit separate manual cleanup;
                // deleting registry membership does not erase historical CSV files.
                if (manager.removePatient(id)) {
                    if (selectedID==id) selectedID="";
                    std::cout << "Patient removed from active roster (CSV retained).\n";
                    if (!saveAll(manager)) std::cerr << "WARNING: Removal not saved.\n";
                } else std::cout << "Patient not found.\n";
                break;
            }
            case 12: saveAll(manager); break;
            default:
                if (choice < 1 || choice > 7) { std::cout << "Invalid menu option.\n"; break; }
                if (!p) { std::cout << "Select or add a patient first.\n"; break; }
                if (choice == 1) { inputVitals(*p); break; }
                if (choice == 6) { p->patient.displayPatientInfo(); break; }
                if (choice == 5) { p->history.displayHistory(); p->history.displayHeartRateSummary(); break; }
                if (!p->hasVitals) { std::cout << "Enter vital signs for this patient first.\n"; break; }
                switch (choice) {
                    case 2: p->patient.getVitalSigns().displayVitalSigns(); break;
                    case 3: assessment(p->patient.getVitalSigns()); break;
                    case 4: calculations(p->patient.getVitalSigns()); break;
                    case 7:
                        p->alarms.evaluate(p->patient.getVitalSigns());
                        p->alarms.displayAlarms();
                        std::cout << "Total Active Alarms: " << p->alarms.getAlarmCount() << '\n';
                        break;
                }
        }
        if (std::cin.eof()) break;
    }
    return saveAll(manager) ? 0 : 1;
}
