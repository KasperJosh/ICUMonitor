#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H
#include <memory>
#include <string>
#include <vector>
#include <set>
#include "Patient.h"
#include "VitalHistory.h"
#include "AlarmManager.h"
namespace ICU {
struct PatientSession {
    Patient patient;
    VitalHistory history;
    AlarmManager alarms;
    bool hasVitals = false;
    PatientSession(const std::string& id, const std::string& name, int age)
        : patient(id, name, age) {}
};
class PatientManager {
private:
    std::vector<std::unique_ptr<PatientSession>> patients;
    std::set<std::string> retiredIDs;
public:
    bool addPatient(const std::string& id, const std::string& name, int age, bool legacyImport = false);
    bool removePatient(const std::string& id);
    PatientSession* findPatient(const std::string& id);
    const PatientSession* findPatient(const std::string& id) const;
    void displayPatients() const;
    bool saveRegistry(const std::string& filename) const;
    bool loadRegistry(const std::string& filename);
    bool saveAllHistories() const;
    std::size_t count() const;
};
}
#endif
