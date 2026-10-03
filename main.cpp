#include <iostream>
#include <iomanip>
#include "VitalSigns.h"


int main()
{
    
    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program

    int systolicBP{};
    int diastolicBP{};
    int heartRate{};
    int spo2{};
    int respRate{};
    double temperature{};

    int choice;

    do{
        std::cout << "\n===== ICU PATIENT MONITOR =====\n";
        std::cout << "1. Enter Vital Signs\n";
        std::cout << "2. Display Vital Signs\n";
        std::cout << "3. Display Assessment\n";
        std::cout << "4. Display Calculations\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
    
        if (choice ==1){
            std::cout <<"\n ==== Enter Vital Signs ====\n";
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
        }

        else if (choice ==2) {
            ICU::displayVitalSigns (heartRate, spo2, systolicBP, diastolicBP, respRate, temperature);
        }

        else if (choice ==3 ){
            // Assessment Section ----------------------------------------------------------
            std::cout << "===== Assessment ===== \n";
            std::cout << std::left;
            
            ICU::checkBP(systolicBP, diastolicBP);
            double map = ICU::calculateMAP(systolicBP, diastolicBP);
            
            std::cout <<std::setw(20)<< "MAP: " << map << '\n';
            
            // Heart Rate Validation
            if (ICU::isValidHeartRate(heartRate)){
                ICU::checkHeartRate(heartRate);
            }
            else{
                std::cout << "Invalid Heart Rate\n";
            }
            
            // SpO2 Validation 
            if (ICU::isValidSpO2(spo2)){
                ICU::checkSpO2(spo2);
            }
            else {
                std::cout << "Invalid SpO2\n";
            }

            // Blood Pressure Validation
            if (ICU::isValidBloodPressure(systolicBP, diastolicBP)){
                ICU::checkBP(systolicBP,diastolicBP);
            }
            
            // RR Validation
            if (ICU::isValidRR(respRate)){
                ICU::checkRespRate(respRate);
            }
            else{
                std::cout << "Invalid Respiratory Rate \n";
            }
            
            // Temperature Validation
            if (ICU::isValidTemp(temperature)){
                ICU::checkTemperature(temperature);
            }
            
            int pulsePressure = ICU::calculatePulsePressure(systolicBP, diastolicBP);
            double shockIndex = ICU::calculateShockIndex(heartRate, systolicBP);

            std::cout << std::setw(20) <<"Pulse Pressure: " << pulsePressure <<  " mmHg\n";
            std::cout << std::setw(20) << "Shock Index: " << shockIndex << '\n'; 
        }

        else if (choice ==5)
        {
            std::cout <<"Exiting ICU Monitor...\n";
        }
        
        else if (choice == 4)
        {
            std::cout << "\n===== Calculations =====\n";

            std::cout << "MAP: "
                      << ICU::calculateMAP(
                             systolicBP,
                             diastolicBP)
                      << '\n';

            std::cout << "Pulse Pressure: "
                      << ICU::calculatePulsePressure(
                             systolicBP,
                             diastolicBP)
                      << " mmHg\n";

            std::cout << "Shock Index: "
                      << ICU::calculateShockIndex(
                             heartRate,
                             systolicBP)
                      << '\n';
        }

        else 
        {
            std::cout <<"Invalid menu option.\n";
        }

    } while(choice !=5);

    
    return 0;
}