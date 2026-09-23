#include <iostream>

using namespace std;

int main()
{
    
    //cout << "Hello"; //Test

    // Start Program→ Ask user for values → Call
    // Functions → Display Results → End Program

    // Asking for the heart rate
    int heartRate;

    std::cout <<"Enter Heart Rate: ";
    std::cin >> heartRate;

    std::cout << "Heart Rate entered: "
            << heartRate
            << " bpm\n";
            

    return 0;
}