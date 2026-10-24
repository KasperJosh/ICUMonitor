
#include "AlarmManager.h"
#include <iostream>

namespace ICU {

    void AlarmManager::addAlarm(
        const std::string& parameter,
        const std::string& message,
        AlarmSeverity severity)
    {
        activeAlarms.push_back({
            parameter,
            message,
            severity
        });
    }

    void AlarmManager::evaluate(const VitalSigns& vitals)
    {
        // Rebuild current alarms from latest measurements
        activeAlarms.clear();

        // HEART RATE
        if (!vitals.isValidHeartRate()) {
            addAlarm("Heart Rate", "Invalid measurement",
                     AlarmSeverity::Warning);
        }
        else if (vitals.getHeartRate() < 60) {
            addAlarm("Heart Rate", "Below 60 bpm",
                     AlarmSeverity::High);
        }
        else if (vitals.getHeartRate() > 100) {
            addAlarm("Heart Rate", "Above 100 bpm",
                     AlarmSeverity::High);
        }

        // OXYGEN SATURATION
        if (!vitals.isValidSpO2()) {
            addAlarm("SpO2", "Invalid measurement",
                     AlarmSeverity::Warning);
        }
        else if (vitals.getSpO2() < 88) {
            addAlarm("SpO2", "Below 88%",
                     AlarmSeverity::High);
        }

        // BLOOD PRESSURE
        if (!vitals.isValidBloodPressure() ||
            vitals.getSystolicBP() <= vitals.getDiastolicBP())
        {
            addAlarm("Blood Pressure", "Invalid measurement",
                     AlarmSeverity::Warning);
        }
        else if (vitals.getSystolicBP() < 90 ||
                 vitals.getDiastolicBP() < 60)
        {
            addAlarm("Blood Pressure",
                     "Below configured lower limit",
                     AlarmSeverity::High);
        }
        else if (vitals.getSystolicBP() > 180 ||
                 vitals.getDiastolicBP() > 120)
        {
            addAlarm("Blood Pressure",
                     "Above configured upper limit",
                     AlarmSeverity::High);
        }

        // RESPIRATORY RATE
        if (!vitals.isValidRR()) {
            addAlarm("Respiratory Rate", "Invalid measurement",
                     AlarmSeverity::Warning);
        }
        else if (vitals.getRespRate() < 12 ||
                 vitals.getRespRate() > 20)
        {
            addAlarm("Respiratory Rate", "Outside 12-20 /min",
                     AlarmSeverity::High);
        }

        // TEMPERATURE
        if (!vitals.isValidTemp()) {
            addAlarm("Temperature", "Invalid measurement",
                     AlarmSeverity::Warning);
        }
        else if (vitals.getTemperature() < 36.0 ||
                 vitals.getTemperature() > 38.0)
        {
            addAlarm("Temperature", "Outside 36.0-38.0 C",
                     AlarmSeverity::High);
        }
    }

    int AlarmManager::getAlarmCount() const
    {
        return static_cast<int>(activeAlarms.size());
    }

    void AlarmManager::displayAlarms() const
    {
        std::cout << "\n===== ACTIVE ALARMS =====\n";

        if (activeAlarms.empty()) {
            std::cout << "No active alarms (demo limits).\n";
            return;
        }

        for (const Alarm& alarm : activeAlarms) {
            std::cout << "["
                      << (alarm.severity == AlarmSeverity::High
                          ? "HIGH" : "WARNING")
                      << "] "
                      << alarm.parameter
                      << ": "
                      << alarm.message
                      << '\n';
        }
    }
}
