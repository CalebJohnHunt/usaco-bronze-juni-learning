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
    for (char j=0; j<2; ++j) {
        char color = 0;
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
    ushort size;
    std::string beads;
    std::ifstream infile("beads.in");
    infile >> size;
    infile >> beads;
    beads = beads + beads;
    
    ushort count = 0;
    for (ushort c=0; c<size; ++c)
        count = max(count, count_beads(c, beads, size));
    
    std::ofstream outfile("beads.out");
    outfile << count << std::endl;
    
    return 0;
}