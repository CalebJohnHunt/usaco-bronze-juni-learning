/*
ID: caleb.h1
LANG: C++
PROG: gift1
*/

#include <fstream>
#include <unordered_map>
#include <string>

#include <iostream>

int main() {
    std::unordered_map<std::string, int> wallets;

    std::ifstream infile("gift1.in");
    
    // Count people
    short numPeople;
    infile >> numPeople;

    std::string names[numPeople];

    // Add people to dictionary
    std::string name;
    for (short i=0; i<numPeople; ++i) {
        infile >> name;
        names[i] = name;
        wallets[name] = 0;
    }

    // Main loop
    // Take how much they're giving, remove it from the giver's wallet, split it to the friends
    unsigned int money = 0;
    while (infile >> name) {
        // std::cout << "Giver: " << name << std::endl;
        infile >> money;
        // std::cout << "Giving: " << money << std::endl;
        
        infile >> numPeople;

        if (numPeople > 0) { // If there are no receipiants, no need to deduct money
            // Remove money from giver
            wallets[name] -= money;
            wallets[name] += money % numPeople; // Leftover money after giving it out

            // Give money to receivers
            for (char i=0; i<numPeople; ++i) {
                infile >> name;
                wallets[name] += money / numPeople; // int division OK    
            }
        }
    }
    infile.close();
    
    std::ofstream outfile("gift1.out");
    for (auto a : names) {
        outfile << a << ' ' << wallets[a] << std::endl;
    }
    outfile.close();

}