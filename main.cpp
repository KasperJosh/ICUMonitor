#include <iostream>
#include "VitalSigns.h"
using namespace std;


int main()
{
    
    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program

    // Asking for the heart rate
    int systolicBP;
    int diastolicBP;
    int heartRate;
    int spo2;
    int respRate;

    // Since we're using the namespace std, we don't need std::
    cout <<"========ICU PATIENT Monitor ========\n";
    cout <<"Enter Systolic Blood Pressure: ";
    cin >> systolicBP;

    cout <<"Enter Diastolic Blood Pressure: ";
    cin >> diastolicBP;

    cout <<"Enter Heart Rate: ";
    cin >> heartRate;

    cout <<"Enter SpO2: ";
    cin >> spo2;

    cout <<"Enter Respiratory Rate : ";
    cin >> respRate;

    cout << "\n";

    
    ICU::checkBP(systolicBP, diastolicBP);
    double map = ICU::calculateMAP(systolicBP, diastolicBP);
    cout << "MAP: " << map << '\n';
    
    ICU::checkHeartRate(heartRate);
    ICU::checkSpO2(spo2);
    ICU::checkRespRate(respRate);
    
    

    return 0;
}