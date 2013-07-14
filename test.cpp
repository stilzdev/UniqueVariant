#include <iostream>

#include "UniqueVariant.hpp"

typedef stilzdev::UniqueVariant<int, float> MyUniqueVariant;

void inc(MyUniqueVariant & variant) {
    float & fv = variant.acquire<float>();
    fv += 1.0;
}

int main(int, char **) {
    MyUniqueVariant variant;
    float & floatValue = variant.acquire<float>();
    floatValue = 1.0;
    inc(variant);
    std::cout << floatValue << std::endl;
}
