#include <iostream>
#include <cmath>

inline float roundToTwoDecimalPlaces(float value) {
    return std::round(value * 100) / 100;
}

int main() {
    float number = 3.14159;

    float roundedNumber = roundToTwoDecimalPlaces(number);
    std::cout << roundedNumber << std::endl;

    return 0;
}