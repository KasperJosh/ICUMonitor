#include <iostream>  
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
        if (spo2 < NORMAL_SPO2_LOW && spo2 >= MIN_VALID_SPO2 )
        {
            std::cout << "SpO2: DESATURATION\n";
        }
        else if (spo2 >= NORMAL_SPO2_LOW  && spo2 <= MAX_VALID_SPO2) {
            std::cout << "SpO2: NORMAL SATURATION\n";
        }
        else{
            std::cout << "Invalid SpO2\n";
        }
    }

    void checkBP (int systolicBP, int diastolicBP)
    {
        if (systolicBP < LOW_SYSTOLIC || diastolicBP  < LOW_DIASTOLIC){
            std::cout << "Blood Pressure: Low blood pressure\n";
        } 
        else if (systolicBP > SEVERE_SYS || diastolicBP > SEVERE_DIA){
            std::cout << "Blood Pressure: Severe hypertension\n";
        }
        else if (systolicBP >= STAGE2_SYS || diastolicBP >= STAGE2_DIA){
            std::cout << "Blood Pressure: Stage 2 hypertension\n";
        }
        else if (systolicBP >= STAGE1_SYS || diastolicBP >= STAGE1_DIA){
            std::cout << "Blood Pressure: Stage 1 hypertension\n";
        }    
        else if (systolicBP >= ELEVATED_SYS ){
            std::cout << "Blood Pressure: Elevated\n";
        } 
        else{
            std::cout << "Blood Pressure: Normal\n";
        }
    }

    void checkRespRate(int respRate){

        if (respRate < NORMAL_RR_LOW  )
        {
            std::cout << "Respiratory Rate: BRADYPNEA\n";
        }
        else if (respRate > NORMAL_RR_HIGH )
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


