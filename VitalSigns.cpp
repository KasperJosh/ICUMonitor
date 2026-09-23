#include <iostream>  
#include "VitalSigns.h"

//private implementation detail of this .cpp file
namespace
{
    const int NORMAL_HR_LOW = 60;
    const int NORMAL_HR_HIGH = 100;
}


namespace ICU{
    void checkHeartRate(int heartRate)
    {
        if (heartRate < NORMAL_HR_LOW )
        {
            std::cout << "Heart Rate: BRADYCARDIA\n";
        }
        else if (heartRate > NORMAL_HR_HIGH)
        {
            std::cout << "Heart Rate: TACHYCARDIA\n";
        }
        else
        {
            std::cout << "Heart Rate: NORMOCARDIA\n";
        }
    }

    void checkSpO2 (int spo2)
    {
        if (spo2 < 88)
        {
            std::cout << "SpO2: DESATURAION\n";
        }
        else if (spo2 >= 88 && spo2 <= 100) {
            std::cout << "SpO2: NORMAL SATURATION\n";
        }
    }

    void checkBP (int systolicBP, int diastolicBP)
    {
        if (systolicBP < 90 || diastolicBP < 60){
            std::cout << "Blood Pressure: Low blood pressure\n";
        } 
        else if (systolicBP > 180 || diastolicBP > 120){
            std::cout << "Blood Pressure: Severe hypertension\n";
        }
        else if (systolicBP >= 140 || diastolicBP >= 90){
            std::cout << "Blood Pressure: Stage 2 hypertension\n";
        }
        else if (systolicBP >= 130 || diastolicBP >= 80){
            std::cout << "Blood Pressure: Stage 1 hypertension\n";
        }    
        else if (systolicBP >= 120){
            std::cout << "Blood Pressure: Elevated\n";
        } 
        else{
            std::cout << "Blood Pressure: Normal\n";
        }
    }

    void checkRespRate(int respRate){

        if (respRate < 12 )
        {
            std::cout << "Respiratory Rate: BRADYPNEA\n";
        }
        else if (respRate < 20 )
        {
            std::cout << "Respiratory Rate: TACHYPNEA\n";
        }
        else
        {
            std::cout << "Respiratory Rate: EUPNEIC\n";
        }
    }


    double calculateMAP(int systolicBP, int diastolicBP)
    {
        return (systolicBP + 2.0*diastolicBP) / 3.0;
    }

}


