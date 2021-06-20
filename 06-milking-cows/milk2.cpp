/*
ID: caleb.h1
LANG: C++
PROG: milk2
*/

#include <fstream>
#include <map>

#define MAX(a, b) a > b ? a : b;
#define MIN(a, b) a < b ? a : b;

int main() {
    std::ifstream infile("milk2.in");

    // Beginning and ending times 1->5,000
    unsigned int numTimes;
    infile >> numTimes;

    // Maps starting times to their ending times
    // Ordered!
    std::map<uint, uint> times;

    uint s, e;
    for (unsigned int i=0; i<numTimes; ++i) {
        infile >> s >> e;
        // Duplciate checking
        try  {
            times[s] = MAX(times[s], e);
        }
        catch (int e) {
            times[s] = e;
        }
    }

    infile.close();


    // merge
    std::map<uint, uint>::iterator next;
    for (std::map<uint, uint>::iterator i = times.begin(); i != times.end(); ++i) {
        while (std::next(i) != times.end() && std::next(i)->first <= i->second) { // Don't go too far && next.start <= cur.end
            i->second = MAX(std::next(i)->second, i->second);
            times.erase(std::next(i));
        }
    }

    // Find longest duration of milking
    // Find longest duration without milking
    uint durationMilking = 0;
    uint durationNoMilking = 0;

    for (std::map<uint, uint>::iterator i = times.begin(); i != times.end(); ++i) {
        durationMilking = MAX(durationMilking, i->second - i->first);
        durationNoMilking = MAX(durationNoMilking, (std::next(i) != times.end() ? std::next(i)->first - i->second : 0));
    }


    std::ofstream outfile("milk2.out");
    outfile << durationMilking << ' ' << durationNoMilking << std::endl;
    outfile.close();
}