
#include <math.h>
#include <string>

#include <iostream>


char asciiBaseToNum(char c) {
    if ('0' <= c && c <= '9')
        return c-48;
    return c-55;
}

char numToAsciiBase(char n, char base) {
    if (n >= base) {
        char ones = n % base;
        char tens = n / base;
    }
}

unsigned int baseToTen(std::string number, char base) {
    unsigned int r = 0;
    for (char i = number.length()-1; i >= 0; --i) {
        char n = asciiBaseToNum(number[i]);
        r += n * pow(base, number.length() - i -1);
    }
    return r;
}

std::string tenTobase(unsigned int number, char base) {
    float l = log(number) / log(base);
    for (float i = 0; i < l; ++i) {
        unsigned int low = number % base;
        number /= base;
        
    }
}


int main() {
    std::cout << baseToTen("100", 11) << std::endl;
    return 0;
}