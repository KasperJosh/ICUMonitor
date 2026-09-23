#ifndef VITALSIGNS_H
#define VITALSIGNS_H

namespace ICU{
    void checkHeartRate (int heartRate);
    void checkSpO2 (int spo2);
    void checkBP (int systolicBP, int diastolicBP);
    void checkRespRate(int respRate);
    double calculateMAP(int systolicBP, int diastolicBP);

}

#endif 