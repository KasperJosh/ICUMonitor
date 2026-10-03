#ifndef VITALSIGNS_H
#define VITALSIGNS_H

namespace ICU{
    
    void checkHeartRate (int heartRate);
    void checkSpO2 (int spo2);
    void checkBP (int systolicBP, int diastolicBP);
    void checkRespRate(int respRate);
    void checkTemperature ( double temperature);
    double calculateMAP(int systolicBP, int diastolicBP);
    
    int calculatePulsePressure ( int systolicBP, int diastolicBP);
    double calculateShockIndex (int heartRate, int systolicBP);


    void displayVitalSigns(
        int heartRate, 
        int spo2, 
        int systolicBP, 
        int diastolicBP, 
        int respRate, 
        double temperature);


}

#endif 