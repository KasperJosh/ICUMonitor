#include <iostream>
#include <iomanip>
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

    
    std::cout << "===== Assessment ===== \n";
    std::cout << std::left;
    ICU::checkBP(systolicBP, diastolicBP);
    double map = ICU::calculateMAP(systolicBP, diastolicBP);
    std::cout <<std::setw(20)<< "MAP: " << map << '\n';
    
    ICU::checkHeartRate(heartRate);
    ICU::checkSpO2(spo2);
    ICU::checkRespRate(respRate);
    ICU::checkTemperature(temperature);
    
    int pulsePressure = ICU::calculatePulsePressure(systolicBP, diastolicBP);
    double shockIndex = ICU::calculateShockIndex(heartRate, systolicBP);

    std::cout << std::setw(20) <<"Pulse Pressure: " << pulsePressure <<  " mmHg\n";
    std::cout << std::setw(20) << "Shock Index: " << shockIndex << '\n'; 



    ICU::displayVitalSigns (heartRate, spo2, systolicBP, diastolicBP, respRate, temperature);


    return 0;
}