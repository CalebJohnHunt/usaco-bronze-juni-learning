/*
ID: caleb.h1
LANG: C++
PROG: palsquare
*/

#include <string>
#include <fstream>
#include <iostream>

// Map numbers to higher base digits
// 0 -> 0, 5 -> 5
// 10 -> a, 15 -> f
char convertNumToDigit(char c) {
    if (c < 10)
        return c + '0';
    return c - 10 + 'A';
}

std::string tenToBase(unsigned int number, char base) {
    std::string newNumber;
    
    while (number > 0) {
        newNumber = convertNumToDigit(number % base) + newNumber;
        number /= base;
    }

    return newNumber;
}


bool isPalindrome(std::string s) {
    for (int i = 0; i < s.length() / 2; ++i) {
        if (s[i] != s[s.length()-i-1])
            return false;
    }
    return true;
}


int main(int argc, const char* argv[]) {

    std::ifstream infile("palsquare.in");
    int base;
    infile >> base;
    infile.close();

    std::ofstream outfile("palsquare.out");
    for (int i = 1; i < 301; ++i) {
        int square = i * i;
        std::string squareString = tenToBase(square, base);
        // std::cout << i << ' ' << square << ' ' << squareString << std::endl;
        if (isPalindrome(squareString))
            outfile << tenToBase(i, base) << ' ' << squareString << std::endl;
    }

    outfile.close();

    return 0;
}