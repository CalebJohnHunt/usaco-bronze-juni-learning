/*
ID: caleb.h1
LANG: C++
PROG: barn1
*/

#include <fstream>
#include <iostream>

#define write(a) std::ofstream fout("barn1.out"); fout << a << std::endl; fout.close();

// reverse Compare
// Used for qsort
// sorts greatest to least
template <typename T>
int rCompare(const void * a, const void * b) {
    return *(T*)b - *(T*)a;
}

int main() {
    std::ifstream fin("barn1.in");
    int maxBoards, numStalls, numCows;
    fin >> maxBoards >> numStalls >> numCows;

    // numStalls is inclusive (i.e. i<=numStalls), so let's just add 1 now instead
    ++numStalls;

    // Edge case: Enough boards to cover all the cows -> covered stalls == number of filled stalls
    if (numCows <= maxBoards) {
        write(numCows);
        fin.close();
        return 0;
    }

    // hasCow: false -> empty, true -> occupied. Init to falses
    bool hasCow[numStalls];
    int i;
    for (i = 0; i < numStalls; ++i) hasCow[i] = false;
    while (fin >> i) {
        hasCow[i] = true;
    }

    fin.close();

    /**** Repurposing hasCow[] ****
     * gaps[] just points to the same data as hasCow BUT it's an unsigned char[], so it can store the gaps between cows
     * gapIndex is the size of the gap
     * This will not be a problem
        * Worst case scenario: gapIndex == i -> still ok.
        * This is the final time we iterate through hasCow, so old data can be overwritten
     * gapIndex now stores the "end" of gaps array (or at least, everything before gapIndex is gaps, everything after is hasCow info)
    */

    unsigned char* gaps = (unsigned char*) hasCow;

    /*
     * gapSize:  length of a run of empty stalls -> [1, 0, 0, 1] -> gapSize=2
     * gapIndex: place to store gapSize (also acts as the end of gaps[])
     * firstCow: index of first occupied stall
    */
    int counter = 0, gapIndex = 0, firstCow = 0;
    while (!hasCow[++firstCow]); // find firstCow

    // Find and saves all the gaps (start from firstCow because 0->firstCow isn't a gap)
    for (i = firstCow; i < numStalls; ++i) {
        // When we find a cow, write down the gap length and reset the counter
        if (hasCow[i]) {
            gaps[gapIndex++] = counter;
            counter = 0;
        } else {
            ++counter;
        }
    }

    // Sort only the gap portion (i.e. everything before gapIndex)
    qsort(gaps, gapIndex, sizeof(hasCow[0]), rCompare<unsigned char>);

    // We must have all cows covered, so we'll add onto numCows for our answer
    // We skip the maxBoards biggest gaps, then add on all the rest of the gaps.
    for (i = maxBoards-1; i < gapIndex; ++i) {
        numCows += gaps[i];
    }

    write(numCows);

}