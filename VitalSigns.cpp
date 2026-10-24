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
    void VitalSigns::checkHeartRate() const
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

    void VitalSigns::checkSpO2() const
    {
        if (spo2 < NORMAL_SPO2_LOW && spo2 >= MIN_VALID_SPO2 )
        {
            std::cout << std::setw(20) << "SpO2: " << "DESATURATION\n";
        }
        else if (spo2 >= NORMAL_SPO2_LOW  && spo2 <= MAX_VALID_SPO2) {
            std::cout << std::setw(20) << "SpO2: " << "NORMAL\n";
        }
    }

    void VitalSigns::checkBP() const
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

    void VitalSigns::checkRespRate() const{

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


    void VitalSigns::checkTemperature() const {
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


    double VitalSigns::calculateMAP() const
    {
        return (systolicBP + 2.0*diastolicBP) / 3.0;
    }

    int VitalSigns::calculatePulsePressure() const
    {
        return systolicBP - diastolicBP;
    }

    double VitalSigns::calculateShockIndex () const
    {
        if (systolicBP == 0)
        {
            return 0.0;
        }

        return static_cast<double>(heartRate) / systolicBP;
    }

    // Adding some input validations
    bool VitalSigns::isValidHeartRate() const{
        return heartRate >0 && heartRate < 300;
    }
    bool VitalSigns::isValidSpO2() const{
        return spo2 >0 && spo2 <=100;
    }
    bool VitalSigns::isValidBloodPressure () const{
        return (systolicBP >0 && systolicBP < 300) && (diastolicBP >0 && diastolicBP < 300);
    }
    bool VitalSigns::isValidRR() const{
        return respRate >0 && respRate <=50;
    }
    bool VitalSigns::isValidTemp() const{
        return temperature >20.0 && temperature < 45.0;
    }


    void VitalSigns::displayVitalSigns() const
    {
        std::cout << "\n==== ICU Monitor ====\n";
        
        std::cout << std::left;
        std::cout << std::setw(15) << "HR: " << heartRate << " bpm\n";
        std::cout << std::setw(15) << "SpO2: " << spo2 << " %\n";
        std::cout << std::setw(15) << "BP: " << systolicBP << "/" << diastolicBP << " mmHg\n";
        std::cout << std::setw(15) << "MAP: " << calculateMAP() << "\n";
        std::cout << std::setw(15) << "RR: " << respRate << " /min\n";
        std::cout << std::setw(15) << "Temp " << temperature << " Celcius\n";
    }

    // Defining the default constructor
    VitalSigns::VitalSigns()
    {
        heartRate = 0;
        spo2 = 0;
        systolicBP = 0;
        diastolicBP = 0;
        respRate = 0;
        temperature = 0.0;
    }

    // Implementing the parameterized constructor
    VitalSigns::VitalSigns(
        int heartRate,
        int spo2,
        int systolicBP,
        int diastolicBP,
        int respRate,
        double temperature)
    {
        this->heartRate = heartRate;
        this->spo2 = spo2;
        this->systolicBP = systolicBP;
        this->diastolicBP = diastolicBP;
        this->respRate = respRate;
        this->temperature = temperature;
    }

    // Getters -----------------------------------------
    int VitalSigns::getHeartRate() const
    {
        return heartRate;
    }

    int VitalSigns::getSpO2() const
    {
        return spo2;
    }

    int VitalSigns::getSystolicBP() const
    {
        return systolicBP;
    }

    int VitalSigns::getDiastolicBP() const
    {
        return diastolicBP;
    }

    int VitalSigns::getRespRate() const
    {
        return respRate;
    }

    double VitalSigns::getTemperature() const
    {
        return temperature;
    }


    // Setters --------------------------------------------------
    void VitalSigns::setHeartRate(int heartRate){
        this->heartRate =heartRate;
    }
    void VitalSigns::setSpO2(int spo2){
        this->spo2=spo2;
    }
    void VitalSigns::setSystolicBP(int systolicBP){
        this->systolicBP = systolicBP;
    }
    void VitalSigns::setDiastolicBP(int diastolicBP){
        this->diastolicBP = diastolicBP;
    }
    void VitalSigns::setRespRate(int respRate){
        this->respRate = respRate;
    }
    void VitalSigns::setTemperature(double temperature){
        this->temperature = temperature;
    }


    // Storing a history of heart-rate readings
    void VitalSigns::addHeartRateReading (int heartRate)
    {
        heartRateHistory.push_back(heartRate);
    }

    void VitalSigns::displayHeartRateHistory() const
    {
        if (heartRateHistory.empty())
        {
            std::cout << "No heart rate history available.\n";
            return;
        }

        std::cout << "\n===== Heart Rate History =====\n";

        for (int hr : heartRateHistory)
        {
            std::cout << hr << " bpm\n";
        }
    }

    double VitalSigns::calculateAverageHeartRate() const
    {
        if (heartRateHistory.empty())
        {
            return 0.0;
        }

        int total = 0;

        for (int hr : heartRateHistory)
        {
            total += hr;
        }

        return static_cast<double>(total) / heartRateHistory.size();
    }


}


