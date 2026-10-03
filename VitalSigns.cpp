#include <iostream>  
#include <iomanip> 
#include "VitalSigns.h"

//private implementation detail of this .cpp file
namespace
{
    const int NORMAL_HR_LOW = 60;
    const int NORMAL_HR_HIGH = 100;

    const int MIN_VALID_SPO2 = 0;
    const int NORMAL_SPO2_LOW = 88;
    const int MAX_VALID_SPO2 = 100;

    const int LOW_SYSTOLIC = 90;
    const int LOW_DIASTOLIC = 60;

    const int STAGE1_SYS = 130;
    const int STAGE1_DIA = 80;

    const int STAGE2_SYS = 140;
    const int STAGE2_DIA = 90;

    const int SEVERE_SYS = 180;
    const int SEVERE_DIA = 120;

    const int ELEVATED_SYS = 120;

    const int NORMAL_RR_LOW = 12;
    const int NORMAL_RR_HIGH = 20;

    const double NORMAL_TEMP_LOW = 36.0;
    const double NORMAL_TEMP_HIGH = 38.0;

}



namespace ICU{
    void checkHeartRate(int heartRate)
    {
        if (heartRate < NORMAL_HR_LOW )
        {
            std::cout << std::setw(20) <<  "Heart Rate: " << "BRADYCARDIA\n";
        }
        else if (heartRate > NORMAL_HR_HIGH)
        {
            std::cout << std::setw(20) <<  "Heart Rate: " << "TACHYCARDIA\n";
        }
        else
        {
            std::cout << std::setw(20) <<  "Heart Rate: " << "NORMAL\n";
        }
    }

    void checkSpO2 (int spo2)
    {
        if (spo2 < NORMAL_SPO2_LOW && spo2 >= MIN_VALID_SPO2 )
        {
            std::cout << std::setw(20) << "SpO2: " << "DESATURATION\n";
        }
        else if (spo2 >= NORMAL_SPO2_LOW  && spo2 <= MAX_VALID_SPO2) {
            std::cout << std::setw(20) << "SpO2: " << "NORMAL\n";
        }
    }

    void checkBP (int systolicBP, int diastolicBP)
    {
        if (systolicBP < LOW_SYSTOLIC || diastolicBP  < LOW_DIASTOLIC){
            std::cout << std::setw(20) << "Blood Pressure: " << "Low blood pressure\n";
        } 
        else if (systolicBP > SEVERE_SYS || diastolicBP > SEVERE_DIA){
            std::cout << std::setw(20) << "Blood Pressure: " << "Severe hypertension\n";
        }
        else if (systolicBP >= STAGE2_SYS || diastolicBP >= STAGE2_DIA){
            std::cout << std::setw(20) << "Blood Pressure: " << "Stage 2 hypertension\n";
        }
        else if (systolicBP >= STAGE1_SYS || diastolicBP >= STAGE1_DIA){
            std::cout << std::setw(20) << "Blood Pressure: " << "Stage 1 hypertension\n";
        }    
        else if (systolicBP >= ELEVATED_SYS ){
            std::cout << std::setw(20) << "Blood Pressure: " << "Elevated\n";
        } 
        else{
            std::cout << std::setw(20) << "Blood Pressure: " << "Normal\n";
        }
    }

    void checkRespRate(int respRate){

        if (respRate < NORMAL_RR_LOW  )
        {
            std::cout << std::setw(20) << "Respiratory Rate: " << "BRADYPNEA\n";
        }
        else if (respRate > NORMAL_RR_HIGH )
        {
            std::cout << std::setw(20) << "Respiratory Rate: " << "TACHYPNEA\n";
        }
        else
        {
            std::cout << std::setw(20) << "Respiratory Rate: " << "EUPNEIC\n";
        }
    }


    void checkTemperature (double temperature) {
        if (temperature < NORMAL_TEMP_LOW ){
            std::cout << std::setw(20) << "Temperature: " << "HYPOTHERMIA\n";
        }
        else if (temperature > NORMAL_TEMP_HIGH){
            std::cout << std::setw(20) << "Temperature: " << "HYPERTHERMIA\n";
        }

        else {
            std::cout << std::setw(20) << "Temperature: " << "NORMAL\n";
        }
    }


    double calculateMAP(int systolicBP, int diastolicBP)
    {
        return (systolicBP + 2.0*diastolicBP) / 3.0;
    }

    int calculatePulsePressure (int systolicBP, int diastolicBP)
    {
        return systolicBP - diastolicBP;
    }

    double calculateShockIndex (int heartRate, int systolicBP){
        return static_cast<double>(heartRate)/ systolicBP;
    }

    // Adding some input validations
    bool isValidHeartRate(int heartRate){
        return heartRate >0 && heartRate < 300;
    }
    bool isValidSpO2 (int spo2){
        return spo2 >0 && spo2 <=100;
    }
    bool isValidBloodPressure (int systolicBP, int diastolicBP){
        return (systolicBP >0 && systolicBP < 300) && (diastolicBP >0 && diastolicBP < 300);
    }
    bool isValidRR (int rr){
        return rr >0 && rr <=50;
    }
    bool isValidTemp(double temp){
        return temp >20.0 && temp < 45.0;
    }






    void displayVitalSigns(
        int heartRate, 
        int spo2, 
        int systolicBP, 
        int diastolicBP, 
        int respRate, 
        double temperature)
    {
        std::cout << "\n==== ICU Monitor ====\n";
        
        std::cout << std::left;
        std::cout << std::setw(15) << "HR: " << heartRate << " bpm\n";
        std::cout << std::setw(15) << "SpO2: " << spo2 << " %\n";
        std::cout << std::setw(15) << "BP: " << systolicBP << "/" << diastolicBP << " mmHg\n";
        std::cout << std::setw(15) << "MAP: " << calculateMAP(systolicBP, diastolicBP) << "\n";
        std::cout << std::setw(15) << "RR: " << respRate << " /min\n";
        std::cout << std::setw(15) << "Temp " << temperature << " Celcius\n";
    }


}


