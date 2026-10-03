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

            // Before checkHeartRate (int heartRate) → because objects already contains heartRate
            void checkHeartRate() const;
            void checkSpO2() const;
            void checkBP() const;
            void checkRespRate() const;
            void checkTemperature() const;
            double calculateMAP() const;
            
            int calculatePulsePressure() const;
            double calculateShockIndex () const ;

            //Validation
            bool isValidHeartRate() const;
            bool isValidSpO2 () const;
            bool isValidBloodPressure() const;
            bool isValidRR () const;
            bool isValidTemp () const;

            void displayVitalSigns() const;
    
        }; 



}

#endif 