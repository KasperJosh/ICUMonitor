#include "PatientManager.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
namespace ICU {
namespace {
bool validId(const std::string& id) {
    if (id.empty()) return false;
    for (unsigned char ch : id)
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
              (ch >= '0' && ch <= '9') || ch == '-' || ch == '_')) return false;
    return true;
}
std::string csvName(const std::string& id) { return "vitals_" + id + ".csv"; }
}
bool PatientManager::addPatient(const std::string& id, const std::string& name, int age) {
    if (!validId(id) || name.empty() || name.find_first_of("\r\n\t,") != std::string::npos ||
        age < 0 || age > 130 || findPatient(id)) return false;
    patients.push_back(std::make_unique<PatientSession>(id, name, age));
    return true;
}
bool PatientManager::removePatient(const std::string& id) {
    auto it = std::find_if(patients.begin(), patients.end(), [&](const auto& p) {
        return p->patient.getPatientID() == id;
    });
    if (it == patients.end()) return false;
    patients.erase(it);
    return true;
}
PatientSession* PatientManager::findPatient(const std::string& id) {
    for (auto& p : patients) if (p->patient.getPatientID() == id) return p.get();
    return nullptr;
}
const PatientSession* PatientManager::findPatient(const std::string& id) const {
    for (const auto& p : patients) if (p->patient.getPatientID() == id) return p.get();
    return nullptr;
}
std::size_t PatientManager::count() const { return patients.size(); }
void PatientManager::displayPatients() const {
    std::cout << "\n===== PATIENT LIST =====\n";
    if (patients.empty()) { std::cout << "No patients registered.\n"; return; }
    std::cout << std::left << std::setw(12) << "ID" << std::setw(22) << "Name"
              << std::setw(7) << "Age" << std::setw(10) << "HR"
              << std::setw(9) << "SpO2" << "History\n";
    for (const auto& p : patients) {
        const auto& v = p->patient.getVitalSigns();
        std::cout << std::setw(12) << p->patient.getPatientID()
                  << std::setw(22) << p->patient.getName().substr(0,21)
                  << std::setw(7) << p->patient.getAge();
        if (p->hasVitals) std::cout << std::setw(10) << v.getHeartRate() << std::setw(9) << v.getSpO2();
        else std::cout << std::setw(10) << "--" << std::setw(9) << "--";
        std::cout << p->history.getReadingCount() << '\n';
    }
}
bool PatientManager::saveAllHistories() const {
    bool ok = true;
    for (const auto& p : patients) {
        // An empty history need not create a CSV file.
        if (p->history.getReadingCount() > 0 &&
            !p->history.saveToCSV(csvName(p->patient.getPatientID()))) ok = false;
    }
    return ok;
}
bool PatientManager::saveRegistry(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    out << "id,name,age\n";
    for (const auto& p : patients)
        out << p->patient.getPatientID() << ',' << p->patient.getName() << ',' << p->patient.getAge() << '\n';
    out.flush();
    return out.good();
}
bool PatientManager::loadRegistry(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    std::string line;
    if (!std::getline(in, line) || line != "id,name,age") return false;
    PatientManager candidate;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream row(line);
        std::string id, name, ageText;
        if (!std::getline(row,id,',') || !std::getline(row,name,',') ||
            !std::getline(row,ageText,',') || row.peek()!=EOF) return false;
        int age = -1;
        try {
            std::size_t parsed = 0;
            age = std::stoi(ageText, &parsed);
            if (parsed != ageText.size()) return false;
        } catch (...) { return false; }
        if (!candidate.addPatient(id,name,age)) return false;
        PatientSession* p = candidate.findPatient(id);
        std::ifstream existing(csvName(id));
        if (existing.good()) {
            if (!p->history.loadFromCSV(csvName(id))) return false;
            p->hasVitals = p->history.restoreLatest(p->patient.getVitalSigns());
        }
    }
    if (in.bad()) return false;
    patients = std::move(candidate.patients);
    return true;
}
}