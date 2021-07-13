/*
ID: caleb.h1
LANG: C++
PROG: dualpal
*/

#include <iostream>
#include <fstream>

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

int main() {
    int N, S;
    std::ifstream infile("dualpal.in");
    infile >> N >> S;
    infile.close();

    std::ofstream outfile("dualpal.out");
    int foundNumbers = 0;
    for (int curNumber = S+1; foundNumbers < N; ++curNumber) {
        char numOfBasesWherePalindromic = 0;
        for (char base = 2; base < 11; ++base)
            if (numOfBasesWherePalindromic < 2 && isPalindrome(tenToBase(curNumber, base)))
                ++numOfBasesWherePalindromic;
        
        if (numOfBasesWherePalindromic > 1) {
            outfile << curNumber << std::endl;
            ++foundNumbers;
        }
    }

    outfile.close();
}