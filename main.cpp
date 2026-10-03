#include <iostream>
#include "VitalSigns.h"


int main()
{
    
    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program

    int systolicBP;
    int diastolicBP;
    int heartRate;
    int spo2;
    int respRate;
    double temperature;

    // Since we're using the namespace std, we don't need std::
    std::cout <<"========ICU PATIENT Monitor ========\n";
    std::cout <<"Enter Systolic Blood Pressure: ";
    std::cin >> systolicBP;

    std::cout <<"Enter Diastolic Blood Pressure: ";
    std::cin >> diastolicBP;

    std::cout <<"Enter Heart Rate: ";
    std::cin >> heartRate;

    std::cout <<"Enter SpO2: ";
    std::cin >> spo2;

    std::cout <<"Enter Respiratory Rate : ";
    std::cin >> respRate;

    std::cout <<"Enter Temperature: ";
    std::cin >> temperature;

    std::cout << "\n";

    
    ICU::checkBP(systolicBP, diastolicBP);
    double map = ICU::calculateMAP(systolicBP, diastolicBP);
    std::cout << "MAP: " << map << '\n';
    
    ICU::checkHeartRate(heartRate);
    ICU::checkSpO2(spo2);
    ICU::checkRespRate(respRate);
    ICU::checkTemperature(temperature);
    
    ICU::displayVitalSigns (heartRate, spo2, systolicBP, diastolicBP, respRate, temperature);


    return 0;
}