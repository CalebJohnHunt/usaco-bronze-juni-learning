/*
ID: caleb.h1
LANG: C++
PROG: crypt1
*/

#include <fstream>
#include <unordered_set>

#include <iostream>

bool hasBadDigits(uint n, const std::unordered_set<char>& digits) {
    while (n) {
        // If there's a bad digit, return true
        if (digits.find(n % 10) == digits.end()) {
            return true;
        }
        // shift n down a digit
        n /= 10;
    }
    return false;
}

int main() {
    std::unordered_set<char> digits;
    uint solutionsCount = 0;
    std::ifstream fin("crypt1.in");
    int N, t;
    fin >> N;
    for (char i = 0; i < N; ++i) {
        fin >> t;
        digits.insert(t);
    }

    // firstNum is 3 digits
    for (uint firstNum = 100; firstNum < 1000; ++firstNum) {
        // firstNum has viable digits
        if (hasBadDigits(firstNum, digits))
            continue;
        // secondNum is 2 digits
        for (uint secondNum = 10; secondNum < 100; ++secondNum) {
            // seconNum has viable digits
            if (hasBadDigits(secondNum, digits))
                continue;

            uint firstProduct = firstNum * (secondNum % 10);

            // firstProduct is 3 digits
            if (firstProduct < 100 || firstProduct > 999)
                continue;
            // firstProduct contains viable numbers
            if (hasBadDigits(firstProduct, digits))
                continue;

            uint secondProduct = firstNum * (secondNum / 10);

            // secondProduct is 3 digits
            if (secondProduct < 100 || secondProduct > 999)
                continue;
            // secondProduct has viable numbers
            if (hasBadDigits(secondProduct, digits))
                continue;
            
            uint product = firstProduct + secondProduct * 10;
            
            // product has 4 digits
            if (product < 1000 || product > 9999)
                continue;
            if (hasBadDigits(product, digits))
                continue;
            
            ++solutionsCount;
        }
    }

    std::ofstream fout("crypt1.out");
    fout << solutionsCount << std::endl;
    fout.close();

    return 0;
}
