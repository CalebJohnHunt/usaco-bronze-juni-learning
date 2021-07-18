/*
ID: caleb.h1
LANG: C++
PROG: barn1
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

struct Stall {
    unsigned int number;
    unsigned int distanceFromPrev;
};

// Used for qsort
int compare(const void * a, const void * b) {
    return ((Stall*)a)->number - ((Stall*)b)->number;
}

// Add stallPtr if it has a big enough distanceFromPrev
// stallGaps has size slots, so we want to put size stallPtr's
// Ex: size = 3, stallGaps = {&prev=8, &prev=6, &prev=4}
unsigned int shiftIn(Stall *stallPtr, std::vector<Stall*>& stallGaps, const int& size) {
    // pretend there's a huge gap to simplify comparisons
    if (size == 0)
        return -1;
    int i;
    if (stallPtr->distanceFromPrev > stallGaps[size-1]->distanceFromPrev) {
        stallGaps[size-1] = stallPtr;
    }
    for (i = size-2; i >= 0 && stallPtr->distanceFromPrev > stallGaps[i]->distanceFromPrev ; --i) {
        stallGaps[i+1] = stallGaps[i];
    }
    stallGaps[i+1] = stallPtr;
    return stallGaps[size-1]->distanceFromPrev;
}

int main() {
    // Setup variables
    std::ifstream fin("barn1.in");
    unsigned int i, numOfStalls, numOfCows;
    int maxBoards;

    // Data that helps set up the future data

    fin >> maxBoards >> numOfStalls >> numOfCows;

    // If we got more boards than cows, we'll just use cow-number of boards
    if (numOfCows <= maxBoards) {
        std::ofstream fout("barn1.out");
        fout << numOfCows << std::endl;
        fout.close();
        fin.close();
        return 0;
    }

    // Off by one prevention
    --maxBoards;


    Stall occupiedStalls[numOfCows];
    std::vector<Stall*> stallGaps;
    // Initialize stallGaps with pointers to the first stall
    for (int i = 0; i < maxBoards; ++i) stallGaps.push_back(occupiedStalls);

    /* Prepare occupiedStalls
     * 1. Read in the numbers of occupied stalls
     * 2. Sort the numbers (sometimes the numbers don't come in pre-sorted)
     * 3. Add in distanceFromPrev for each one
    */

    // First stall has 0 from previous so it won't seem like a huge gap between it and the start
    fin >> occupiedStalls[0].number;
    
    for (i = 1; i < numOfCows; ++i) {
        fin >> occupiedStalls[i].number;
    }

    fin.close();

    qsort(occupiedStalls, numOfCows, sizeof(Stall), compare);
    
    occupiedStalls[0].distanceFromPrev = 0;

    for (i = 1; i < numOfCows; ++i) {
        occupiedStalls[i].distanceFromPrev = occupiedStalls[i].number - occupiedStalls[i-1].number;
    }

    /* End of Preparing occupiedStalls */

    /* Find the biggest gaps */

    unsigned int min = 0;
    for (i = 0; i < numOfCows; ++i) {
        if (occupiedStalls[i].distanceFromPrev >= min) {
            min = shiftIn(occupiedStalls + i, stallGaps, maxBoards);
        }
    }

    /*
     * End of Finding the biggest gaps
     * -- stallGaps now contains pointers to the occupied stalls where the biggest gaps occur
    */

    unsigned int covered = 0, gap = 0, prevGap = occupiedStalls[0].number;
    for (gap = 0; gap < numOfCows; ++gap) {
        auto it = std::find(stallGaps.begin(), stallGaps.end(), &occupiedStalls[gap]);
        if (it == stallGaps.end())
            continue;
        covered += occupiedStalls[gap-1].number - prevGap + 1;
        prevGap = occupiedStalls[gap].number;
        stallGaps.erase(it);
    }

    covered += occupiedStalls[gap-1].number - prevGap + 1;

    std::ofstream fout("barn1.out");
    fout << covered << std::endl;
    fout.close();

    return 0;
}