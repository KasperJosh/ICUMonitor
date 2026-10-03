#ifndef VITALSIGNS_H
#define VITALSIGNS_H

namespace ICU{
    
    class VitalSigns{
        private: 
            int heartRate;
            int spo2;
            int systolicBP;
            int diastolicBP;
            int respRate;
            double temperature;

        public:

            //Default constructor
            VitalSigns();
            // Parameter constructor
            VitalSigns(int heartRate, int spo2, int systolicBP, int diastolicBP, int respRate, double temperature);

            int getHeartRate() const;
            int getSpO2() const;
            int getSystolicBP() const;
            int getDiastolicBP() const;
            int getRespRate() const;
            double getTemperature() const;

            void setHeartRate(int heartRate);
            void setSpO2(int spo2);
            void setSystolicBP(int systolicBP);
            void setDiastolicBP(int diastolicBP);
            void setRespRate(int respRate);
            void setTemperature(double temperature);
    
        }; 


    void checkHeartRate (int heartRate);
    void checkSpO2 (int spo2);
    void checkBP (int systolicBP, int diastolicBP);
    void checkRespRate(int respRate);
    void checkTemperature ( double temperature);
    double calculateMAP(int systolicBP, int diastolicBP);
    
    int calculatePulsePressure ( int systolicBP, int diastolicBP);
    double calculateShockIndex (int heartRate, int systolicBP);

    //Validation
    bool isValidHeartRate(int heartRate);
    bool isValidSpO2 (int spo2);
    bool isValidBloodPressure( int systolicBP, int diastolicBP);
    bool isValidRR (int rr);
    bool isValidTemp (double temp);

    void displayVitalSigns(
        int heartRate, 
        int spo2, 
        int systolicBP, 
        int diastolicBP, 
        int respRate, 
        double temperature);


}

#endif 