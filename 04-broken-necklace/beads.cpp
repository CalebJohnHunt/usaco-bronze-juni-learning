/*
ID: caleb.h1
LANG: C++
PROG: beads
*/

#include <string>
#include <fstream>

#define max(a, b) a > b ? a : b

typedef unsigned short ushort;

ushort count_beads(const ushort &index, const std::string &beads, const ushort &size) {
    ushort counter = 0;
    ushort i = index;
    // Read forward 2 times
    for (char j=0; j<2; ++j) {
        // Reset color
        char color = 0;
        // Make sure we haven't counted passed one full loop
        // Also that either the bead is white, matches our color, or we just don't hae a color
        while (counter < size && (beads[i] == 'w' || beads[i] == color || !color)) {
            if (!color && beads[i] != 'w')
                color = beads[i];
            ++i;
            ++counter;
        }
    }
    return counter;
}

int main() {
    // Setup and read in
    ushort size;
    std::string beads;
    std::ifstream infile("beads.in");
    infile >> size;
    infile >> beads;
    // Add another set of beads on the end. This way we can just read forward twice
    // rather than read once forward and once backwards
    beads = beads + beads;
    
    // Get the max count of beads
    ushort count = 0;
    for (ushort c=0; c<size; ++c)
        count = max(count, count_beads(c, beads, size));
    
    // Write to file
    std::ofstream outfile("beads.out");
    outfile << count << std::endl;
    
    return 0;
}