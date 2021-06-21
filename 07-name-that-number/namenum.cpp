/*
ID: caleb.h1
LANG: C++
PROG: namenum
*/

#include <fstream>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <string>
#include <array>

#include <iostream>


int main() {
    static std::unordered_map<char, std::array<char, 3>> keypad = {
        {'2', {'A','B','C'}},
        {'3', {'D','E','F'}},
        {'4', {'G','H','I'}},
        {'5', {'K','J','L'}},
        {'6', {'M','N','O'}},
        {'7', {'P','R','S'}},
        {'8', {'T','U','V'}},
        {'9', {'W','Y','Z'}},
    };

    std::ifstream infile("dict.txt");
    std::set<std::string> possibleNames;
    std::string name;
    while (getline(infile, name)) possibleNames.insert(name);

    infile.close();
    infile.open("namenum.in");

    char numbers[15];
    char numbersCount = 0;
    char c;
    while (infile >> c) {
        numbers[numbersCount++] = c;
    }

    infile.close();

    // The purge - Remove from the possibleNames ones that don't fit

    // Remove ones too long or too short
    for (auto it = possibleNames.begin(); it != possibleNames.end();)
        if (it->length() != numbersCount)
            it = possibleNames.erase(it);
        else
            ++it;

    // Remove those that don't share letters
    for (char i = 0; i < numbersCount; ++i) {
        std::array<char, 3> a = keypad[numbers[i]];
        for (auto it = possibleNames.begin(); it != possibleNames.end();) {
            if ((*it)[i] != a[0] && (*it)[i] != a[1] && (*it)[i] != a[2])
                it = possibleNames.erase(it);
            else
                ++it;
        }
    }


    // Write NONE if no names match, otherwise all matching names
    std::ofstream outfile("namenum.out");

    if (!possibleNames.size())
        outfile << "NONE" << std::endl;
    else
        for (std::string name : possibleNames)
            outfile << name << std::endl;
    
    outfile.close();

    return 0;

}
