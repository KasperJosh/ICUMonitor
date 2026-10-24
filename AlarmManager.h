
#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include <string>
#include <vector>
#include "VitalSigns.h"

namespace ICU {

    enum class AlarmSeverity {
        Warning,
        High
    };

    struct Alarm {
        std::string parameter;
        std::string message;
        AlarmSeverity severity;
    };

    class AlarmManager {
    private:
        std::vector<Alarm> activeAlarms;

        void addAlarm(
            const std::string& parameter,
            const std::string& message,
            AlarmSeverity severity
        );

    public:
        void evaluate(const VitalSigns& vitals);
        void displayAlarms() const;
        int getAlarmCount() const;
    };
}

#endif
