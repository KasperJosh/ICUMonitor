#ifndef VITALSIGNS_h
#define VITALSIGNS_h


void checkHeartRate (int heartRate);
void checkSpO2 (int spo2);
void checkBP (int systolicBP, int diastolicBP);
void checkRespRate(int respRate);
double calculateMAP(int systolicBP, int diastolicBP);


#endif 