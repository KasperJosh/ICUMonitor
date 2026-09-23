#include <iostream>

using namespace std;


void checkHeartRate(int heartRate)
{
    if (heartRate < 60 )
    {
        std::cout << "Heart Rate: BRADYCARDIA\n";
    }
    else if (heartRate >100)
    {
        std::cout << "Heart Rate: TACHYCARDIA\n";
    }
    else
    {
        std::cout << "Heart Rate: NORMOCARDIA";
    }
}


int main()
{
    
    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program

    // Asking for the heart rate
    int heartRate;

    std::cout <<"Enter Heart Rate: ";
    std::cin >> heartRate;

    checkHeartRate(heartRate);
    
    return 0;
}