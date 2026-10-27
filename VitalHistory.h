#ifndef VITALHISTORY_H
#define VITALHISTORY_H

#include <ctime>
#include <vector>
#include <string>
#include "VitalSigns.h"

namespace ICU {

    // Snapshot of all measurements at a particular time.
    struct VitalRecord {
        std::time_t timestamp;
        int heartRate;
        int spo2;
        int systolicBP;
        int diastolicBP;
        int respRate;
        double temperature;
    };

    class VitalHistory {
    private:
        std::vector<VitalRecord> records;

    public:
        void addReading(const VitalSigns& vitals);
        void displayHistory() const;
        void displayHeartRateSummary() const;
        std::size_t getReadingCount() const;
        bool saveToCSV(const std::string& filename) const;
        bool loadFromCSV(const std::string& filename);
        bool restoreLatest(VitalSigns& vitals) const;
    };
}

#endif
