/*
ID: caleb.h1
LANG: C++
PROG: milk
*/

#include <iostream>
#include <fstream>
#include <map>

#define MIN(a, b) a < b ? a : b

int main() {
    std::ifstream infile("milk.in");
    unsigned int milkToBuy;
    infile >> milkToBuy;
    unsigned int moneySpent = 0;

    unsigned int numOfFarmers;
    infile >> numOfFarmers;

    // map setup
    // prices<price, quantity>
    std::map<unsigned int, unsigned int> prices;

    unsigned int price;
    unsigned int quantity;
    for (size_t i = 0; i < numOfFarmers; ++i) {
        infile >> price;
        infile >> quantity;
        // If this is a new price
        if (prices.find(price) == prices.end())
            prices[price] = quantity;
        else
            prices[price] += quantity;
    }

    infile.close();


    // Go through each farmer (starting least expensive to move)
    // Either buy them out or buy as much as we need
    // No need to worry about the iterator b/c we are guarenteed enough milk is offered
    for (auto it = prices.begin(); milkToBuy > 0; ++it) {
        unsigned int order = MIN(milkToBuy, it->second);
        // it->second -= order; // Don't need to change quanitity since we'll either buy it all or be done 
        milkToBuy -= order;
        moneySpent += it->first * order;
    }

    std::ofstream outfile("milk.out");
    outfile << moneySpent << std::endl;
    outfile.close();


    return 0;
}