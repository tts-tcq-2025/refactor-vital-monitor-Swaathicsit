#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

constexpr float TEMP_LOW = 95.0f;
constexpr float TEMP_HIGH = 102.0f;
constexpr float PULSE_LOW = 60.0f;
constexpr float PULSE_HIGH = 100.0f;
constexpr float SPO2_MIN = 90.0f;
constexpr float WARNING_THRESHOLD_PERCENTAGE = 0.015f;  // 1.5% tolerance

constexpr int OK = 1;
constexpr int NOT_OK = 0;

void blinkAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\r *" << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\r  \r" << flush;  // Clear line after alert
}

void earlyWarning(float value, float lower_limit, float upper_limit, const string& type) {
    float warningThreshold = upper_limit * WARNING_THRESHOLD_PERCENTAGE;
    
    if (value >= upper_limit - warningThreshold) {
        cout << type << " is approaching upper limit: Warning - Approaching critical level!" << endl;
    }
    else if (value <= lower_limit + warningThreshold) {
        cout << type << " is approaching lower limit: Warning - Approaching critical level!" << endl;
    }
}

int checkVitals(float temperature, float pulseRate, float spo2) {
    // Temperature checks
    earlyWarning(temperature, TEMP_LOW, TEMP_HIGH, "Temperature");
    if (temperature < TEMP_LOW) {
        cout << "Temperature critical! Hypothermia risk." << endl;
        blinkAlert();
        return NOT_OK;
    }
    if (temperature > TEMP_HIGH) {
        cout << "Temperature critical! Hyperthermia risk." << endl;
        blinkAlert();
        return NOT_OK;
    }
    if (temperature >= TEMP_LOW && temperature <= TEMP_LOW + (TEMP_HIGH * WARNING_THRESHOLD_PERCENTAGE)) {
        cout << "Warning: Approaching hypothermia" << endl;
    }
    if (temperature <= TEMP_HIGH - (TEMP_HIGH * WARNING_THRESHOLD_PERCENTAGE) && temperature >= TEMP_HIGH) {
        cout << "Warning: Approaching hyperthermia" << endl;
    }

    // Pulse Rate checks
    earlyWarning(pulseRate, PULSE_LOW, PULSE_HIGH, "Pulse Rate");
    if (pulseRate < PULSE_LOW) {
        cout << "Pulse Rate critical! Too low." << endl;
        blinkAlert();
        return NOT_OK;
    }
    if (pulseRate > PULSE_HIGH) {
        cout << "Pulse Rate critical! Too high." << endl;
        blinkAlert();
        return NOT_OK;
    }
    if (pulseRate >= PULSE_LOW && pulseRate <= PULSE_LOW + (PULSE_HIGH * WARNING_THRESHOLD_PERCENTAGE)) {
        cout << "Warning: Approaching bradycardia" << endl;
    }
    if (pulseRate <= PULSE_HIGH - (PULSE_HIGH * WARNING_THRESHOLD_PERCENTAGE) && pulseRate >= PULSE_HIGH) {
        cout << "Warning: Approaching tachycardia" << endl;
    }

    // SPO2 checks
    earlyWarning(spo2, 0.0f, 100.0f, "Oxygen Saturation");
    if (spo2 < SPO2_MIN) {
        cout << "Oxygen Saturation critical! Hypoxemia risk." << endl;
        blinkAlert();
        return NOT_OK;
    }
    if (spo2 >= SPO2_MIN && spo2 <= SPO2_MIN + (SPO2_MIN * WARNING_THRESHOLD_PERCENTAGE)) {
        cout << "Warning: Approaching low oxygen saturation" << endl;
    }

    return OK;
}

int main() {
    // Example usage
    float temperature = 101.5f;  // Temperature in Fahrenheit
    float pulseRate = 80.0f;     // Pulse rate in beats per minute
    float spo2 = 92.0f;          // SPO2 percentage

    if (checkVitals(temperature, pulseRate, spo2) == OK) {
        cout << "All vitals are OK." << endl;
    } else {
        cout << "Some vitals are out of range." << endl;
    }

    return 0;
}
