/*
ID: caleb.h1
LANG: C++
PROG: milk
*/

#include <fstream>
#include <iostream>

#define MIN(a, b) a < b ? a : b
#define MAX_FARMERS 1001

int main() {
    unsigned int milkToBuy, moneySpent, numOfFarmers, price, quantity, quantityAtPrice[MAX_FARMERS];
    for (size_t i = 0; i < MAX_FARMERS; ++i) {
        quantityAtPrice[i] = 0;
    }

    std::ifstream infile("milk.in");
    infile >> milkToBuy >> numOfFarmers;

    for (size_t i = 0; i < numOfFarmers; ++i) {
        infile >> price >> quantity;
        quantityAtPrice[price] += quantity;
    }

    infile.close();

    for (price = 0; milkToBuy; ++price) {
        quantity = MIN(milkToBuy, quantityAtPrice[price]);
        milkToBuy -= quantity;
        moneySpent += quantity * price;
    }

    std::ofstream outfile("milk.out");
    outfile << moneySpent << std::endl;
    outfile.close();

    return 0;
}
