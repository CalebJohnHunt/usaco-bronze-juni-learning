/* 
ID: caleb.h1
LANG: C++
PROG: skidesign
*/

/*
 * This program solves skidesign by raising or lowering the
 * lowest or highest hills, repectively, for as cheap as possible.
 * If it's cheaper to raise all the shortest hills, then do that,
 * but if it's cheaper to lower all the tallest hills, do that.
 * We repeat until the difference from tallest and shortest hills <= 17
 * 
 * Complexity:
 * I don't even know. I think sorting the data while taking it in is n^2?
*/

#include <iostream>
#include <fstream>

struct Hill {
    int height;
    int change=0;
};

// Checks upwards
// hills should point to the start of the possible hills
// ex: Short hills: points to start of hills; Tall hills: points a few hills from the end
int findPriceToChangeNHills(const Hill* hills, const int& N) {
    int price = 0;
    // Cost increases at a rate of 2n-1 where n is the new cost
    // ex: 3->4 : 4**2 - 3**2 == 2(4)-1 == 7
    // was 2*(change+1)-1, but that's eq to 2*change+1
    for (int i = 0; i < N; ++i)
        price += 2*hills[i].change+1;

    return price;
}

// returns the number of hills with the same height starting at the start of the array
int inline findNumOfEquallyShortHills(const Hill* hills, const int& size) {
    int count = 0;
    while (count < size && hills[count].height == hills[++count].height);

    return count;
}

// returns the number of hills with the same height starting at the end of the array
int inline findNumOfEquallyTallHills(const Hill* hills, const int& size) {
    int count = 0;
    while (count < size && hills[size-1-count].height == hills[size-1-++count].height);

    return count;
}

int addToHills(Hill* hills, const int& size, int& equallyShortHills, int& equallyTallHills) {
    // Calculate the price to raise all the shortest hills
    const int priceForShortHills = findPriceToChangeNHills(hills, equallyShortHills);

    // Calculate the price for tallest hills
    const int priceForTallHills  = findPriceToChangeNHills(hills + size - equallyTallHills, equallyTallHills);

    // If it's cheaper to raise the short hills, raise them
    // otherwise, lower the tall hills
    if (priceForShortHills <= priceForTallHills) {
        for (int i = 0; i < equallyShortHills; ++i) {
            hills[i].height++;
            hills[i].change++;
        }
        // Update number of short hills
        while (hills[equallyShortHills-1].height == hills[equallyShortHills].height
            && equallyShortHills < size)
            ++equallyShortHills;
        return priceForShortHills;
    }

    for (int i = size-1; i > size-1-equallyTallHills; --i) {
        hills[i].height--;
        hills[i].change++;
    }
    // Update number of tall hills
    while (hills[size-equallyTallHills].height == hills[size-equallyTallHills-1].height
        && equallyTallHills < size)
        ++equallyTallHills;
    return priceForTallHills;
}

Hill* readHills(int& N) {
    std::ifstream fin("skidesign.in");
    fin >> N;
    Hill* hills = new Hill[N];
    // hills = (Hill*) malloc(N * (sizeof(Hill))); // Just trying this for fun

    Hill temp;
    int j;
    for (int i = 0; i < N; ++i) {
        fin >> temp.height;

        // Sort as you take in
        for (j=0; j<i; ++j) {
            if (temp.height < hills[j].height) {
                const Hill t2 = hills[j];
                hills[j] = temp;
                temp = t2;
            }
        }
        hills[j] = temp;
    }

    fin.close();

    return hills;
}

int main() {
    int N, i, price=0;

    // readHills updates N and sorts the hills as they come in
    Hill* hills = readHills(N);

    // We're going to raise up all the shortest or lower all the tallest hills
    // at the same time, so it's nice to keep track of how many there are of each
    int equallyShortHills = findNumOfEquallyShortHills(hills, N);
    int equallyTallHills = findNumOfEquallyTallHills(hills, N);

    // biggest differences in hills are too big
    while (hills[N-1].height - hills->height > 17)
        price += addToHills(hills, N, equallyShortHills, equallyTallHills);

    std::ofstream fout("skidesign.out");
    fout << price << std::endl;
    fout.close();
    

    return 0;
}