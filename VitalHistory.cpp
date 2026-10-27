#include "VitalHistory.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <string>

namespace ICU {

    void VitalHistory::addReading(const VitalSigns& vitals) {
        // Only save complete, valid sets of measurements.
        if (!vitals.isValidHeartRate() || !vitals.isValidSpO2() ||
            !vitals.isValidBloodPressure() || !vitals.isValidRR() ||
            !vitals.isValidTemp() ||
            vitals.getSystolicBP() <= vitals.getDiastolicBP()) {
            std::cout << "Invalid vital signs: history not updated.\n";
            return;
        }

        records.push_back({
            std::time(nullptr),
            vitals.getHeartRate(),
            vitals.getSpO2(),
            vitals.getSystolicBP(),
            vitals.getDiastolicBP(),
            vitals.getRespRate(),
            vitals.getTemperature()
        });
    }

    std::size_t VitalHistory::getReadingCount() const {
        return records.size();
    }

    void VitalHistory::displayHistory() const {
        std::cout << "\n===== VITAL SIGNS HISTORY =====\n";
        if (records.empty()) {
            std::cout << "No recorded measurements.\n";
            return;
        }

        std::cout << std::left
                  << std::setw(21) << "Date / Time"
                  << std::setw(7)  << "HR"
                  << std::setw(7)  << "SpO2"
                  << std::setw(13) << "BP"
                  << std::setw(7)  << "RR"
                  << "Temp\n";

        for (const VitalRecord& record : records) {
            // std::localtime() uses the system's local timezone.
            std::tm* local = std::localtime(&record.timestamp);
            if (local) {
                std::cout << std::put_time(local, "%Y-%m-%d %H:%M:%S");
            } else {
                std::cout << "Unknown time        ";
            }
            std::cout << "  " << std::setw(7) << record.heartRate
                      << std::setw(7) << record.spo2
                      << std::setw(13) << (std::to_string(record.systolicBP) + "/" +
                                           std::to_string(record.diastolicBP))
                      << std::setw(7) << record.respRate
                      << std::fixed << std::setprecision(1)
                      << record.temperature << '\n';
        }
    }

    void VitalHistory::displayHeartRateSummary() const {
        if (records.empty()) {
            std::cout << "No readings available for analysis.\n";
            return;
        }

        int minHR = records.front().heartRate;
        int maxHR = records.front().heartRate;
        long long totalHR = 0;

        for (const VitalRecord& record : records) {
            minHR = std::min(minHR, record.heartRate);
            maxHR = std::max(maxHR, record.heartRate);
            totalHR += record.heartRate;
        }

        std::cout << "\n===== HEART RATE SUMMARY =====\n"
                  << "Readings: " << records.size() << '\n'
                  << "Minimum:  " << minHR << " bpm\n"
                  << "Maximum:  " << maxHR << " bpm\n"
                  << "Average:  " << std::fixed << std::setprecision(2)
                  << static_cast<double>(totalHR) / records.size()
                  << " bpm\n";
    }

    bool VitalHistory::saveToCSV(
        const std::string& filename) const
    {
        std::ofstream file(filename);

        if (!file.is_open()) {
            return false;
        }

        // Column headings
        file << "timestamp,heartRate,spo2,"
            << "systolicBP,diastolicBP,"
            << "respRate,temperature\n";

        // Write each stored record
        for (const VitalRecord& record : records) {
            file << record.timestamp << ","
                << record.heartRate << ","
                << record.spo2 << ","
                << record.systolicBP << ","
                << record.diastolicBP << ","
                << record.respRate << ","
                << record.temperature << "\n";
        }

        file.close();

        return file.good();
    }

    
    bool VitalHistory::loadFromCSV(
        const std::string& filename)
    {
        std::ifstream file(filename);

        if (!file.is_open()) {
            return false;
        }

        std::string line;

        // Skip CSV header
        if (!std::getline(file, line)) {
            return false;
        }

        std::vector<VitalRecord> loadedRecords;

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);
            VitalRecord record{};

            char comma1, comma2, comma3;
            char comma4, comma5, comma6;

            if (!(ss >> record.timestamp
                    >> comma1 >> record.heartRate
                    >> comma2 >> record.spo2
                    >> comma3 >> record.systolicBP
                    >> comma4 >> record.diastolicBP
                    >> comma5 >> record.respRate
                    >> comma6 >> record.temperature)) {
                return false;
            }

            if (comma1 != ',' || comma2 != ',' ||
                comma3 != ',' || comma4 != ',' ||
                comma5 != ',' || comma6 != ',') {
                return false;
            }

            ss >> std::ws;
            if (!ss.eof()) {
                return false;
            }

            loadedRecords.push_back(record);
        }

        if (file.bad()) {
            return false;
        }

        // Replace history only after successful parsing
        records = std::move(loadedRecords);

        return true;
    }

}
