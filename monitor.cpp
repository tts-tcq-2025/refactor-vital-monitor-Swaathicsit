#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Replace constexpr with regular const
const float TEMP_LOW = 95.0f;
const float TEMP_HIGH = 102.0f;
const float PULSE_LOW = 60.0f;
const float PULSE_HIGH = 100.0f;
const float SPO2_MIN = 90.0f;

const int OK = 1;
const int NOT_OK = 0;

// Blinking alert function to simulate visual alerts
void blinkAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << "\r  \r" << flush;  // Clear the line after the alert
}

// Function to check temperature
int tempOk(float temperature) {
    if (temperature > TEMP_HIGH || temperature < TEMP_LOW) {
        cout << "Temperature is critical!\n";
        blinkAlert();
        return NOT_OK;
    }
    return OK;
}

// Function to check pulse rate
int pulseRateOk(float pulseRate) {
    if (pulseRate < PULSE_LOW || pulseRate > PULSE_HIGH) {
        cout << "Pulse Rate is out of range!\n";
        blinkAlert();
        return NOT_OK;
    }
    return OK;
}

// Function to check SPO2
int spo2Ok(float spo2) {
    if (spo2 < SPO2_MIN) {
        cout << "Oxygen Saturation out of range!\n";
        blinkAlert();
        return NOT_OK;
    }
    return OK;
}

// Single function to check all vitals and return overall status
int vitalsOk(float temperature, float pulseRate, float spo2) {
    // If any vital check fails, return NOT_OK
    if (tempOk(temperature) == NOT_OK) return NOT_OK;
    if (pulseRateOk(pulseRate) == NOT_OK) return NOT_OK;
    if (spo2Ok(spo2) == NOT_OK) return NOT_OK;

    // All vitals are OK
    return OK;
}

int main() {
    // Example usage
    float temperature = 98.5f;  // Example temperature
    float pulseRate = 80.0f;    // Example pulse rate
    float spo2 = 92.0f;         // Example SPO2

    if (vitalsOk(temperature, pulseRate, spo2) == OK) {
        cout << "All vitals are within normal range.\n";
    } else {
        cout << "One or more vitals are out of range.\n";
    }

    return 0;
}
