#include <iostream>
#include <iomanip>
#include "VitalSigns.h"


int main()
{
    
    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program
    ICU::VitalSigns patientVitals;

    return 0;
    int systolicBP{};
    int diastolicBP{};
    int heartRate{};
    int spo2{};
    int respRate{};
    double temperature{};
    
    
    int choice;
    bool vitalsEntered = false;

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

            vitalsEntered = true;
        }

        else if (choice ==2) {
            if (vitalsEntered){
                ICU::displayVitalSigns (heartRate, spo2, systolicBP, diastolicBP, respRate, temperature);
            }
            else {
                std::cout <<"Please enter Vital Signs first. \n";
            }
        }

        else if (choice ==3 ){
            // Assessment Section ----------------------------------------------------------
            
            if (vitalsEntered){
                std::cout << "===== Assessment ===== \n";
                std::cout << std::left;
                
                // Blood Pressure Validation
                if (ICU::isValidBloodPressure(systolicBP, diastolicBP)){
                    ICU::checkBP(systolicBP,diastolicBP);
                }
                else {
                    std::cout <<"Invalid Blood Pressure\n";
                }
                
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
                else {
                    std::cout <<"Invalid Temperature\n";
                }
            }
            else {
                std::cout <<"Please enter Vital Signs first. \n";
            }
            
        }

        else if (choice == 4)
        {
            
             if (vitalsEntered){
                std::cout << "\n===== Calculations =====\n";

                std::cout << std::left;
                std::cout << std::setw(20) <<  "MAP: "<< ICU::calculateMAP(systolicBP, diastolicBP) << '\n';

                std::cout << std::setw(20) << "Pulse Pressure: " << ICU::calculatePulsePressure(systolicBP,diastolicBP)<< " mmHg\n";

                std::cout << std::setw(20) << "Shock Index: "<< ICU::calculateShockIndex(heartRate,systolicBP)<< '\n';
            }
            else {
                std::cout <<"Please enter Vital Signs first. \n";
            }
        }

        else if (choice ==5)
        {
            std::cout <<"Exiting ICU Monitor...\n";
        }

        else 
        {
            std::cout <<"Invalid menu option.\n";
        }

    } while(choice !=5);

    return 0;
}