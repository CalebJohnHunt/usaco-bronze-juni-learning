/*
ID: caleb.h1
LANG: C++
PROG: ride
*/

#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream infile("ride.in");
    std::string line;
    std::string lines[2];
    unsigned char counter = 0;
    uint values[2] = {1, 1};
    while (getline(infile, line)) { 
        lines[counter++] = line;
    }

    infile.close();

    for (uint i=0; i<2; ++i) {
        for (char c : lines[i]) {
            values[i] *= c - 64;
        }
    }

    std::ofstream outfile("ride.out");
    outfile << ((values[0] % 47 == values[1] % 47) ? "GO" : "STAY") << '\n';
    outfile.close();

    return 0;
}