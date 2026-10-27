#include "VitalHistory.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>

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
    bool VitalHistory::saveToCSV(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) return false;
        file << "timestamp,heartRate,spo2,systolicBP,diastolicBP,respRate,temperature\n";
        for (const auto& r : records) {
            file << r.timestamp << ',' << r.heartRate << ',' << r.spo2 << ','
                 << r.systolicBP << ',' << r.diastolicBP << ',' << r.respRate
                 << ',' << r.temperature << '\n';
        }
        file.flush();
        return file.good();
    }

    bool VitalHistory::loadFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) return false;
        std::string line;
        if (!std::getline(file, line) ||
            line != "timestamp,heartRate,spo2,systolicBP,diastolicBP,respRate,temperature")
            return false;
        std::vector<VitalRecord> incoming;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            VitalRecord r{};
            char a,b,c,d,e,f;
            if (!(ss >> r.timestamp >> a >> r.heartRate >> b >> r.spo2
                     >> c >> r.systolicBP >> d >> r.diastolicBP >> e >> r.respRate
                     >> f >> r.temperature) ||
                a != ',' || b != ',' || c != ',' || d != ',' || e != ',' || f != ',') return false;
            ss >> std::ws;
            if (!ss.eof()) return false;
            VitalSigns check(r.heartRate, r.spo2, r.systolicBP,
                             r.diastolicBP, r.respRate, r.temperature);
            if (r.timestamp < 0 || !check.isValidHeartRate() || !check.isValidSpO2() ||
                !check.isValidBloodPressure() || !check.isValidRR() || !check.isValidTemp() ||
                r.systolicBP <= r.diastolicBP || !std::isfinite(r.temperature)) return false;
            incoming.push_back(r);
        }
        if (file.bad()) return false;
        records = std::move(incoming);
        return true;
    }

    bool VitalHistory::restoreLatest(VitalSigns& vitals) const {
        if (records.empty()) return false;
        const auto& r = records.back();
        vitals.setHeartRate(r.heartRate);
        vitals.setSpO2(r.spo2);
        vitals.setSystolicBP(r.systolicBP);
        vitals.setDiastolicBP(r.diastolicBP);
        vitals.setRespRate(r.respRate);
        vitals.setTemperature(r.temperature);
        return true;
    }
}
