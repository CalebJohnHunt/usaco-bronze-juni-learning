/*
ID: caleb.h1
LANG: C++
PROG: milk2
*/

/*
Longest milking (O(n^2)):
First put everything intho an ordered map so we don't have to sort it. We want sort by start times
For each start time:
    For each start time after it:
        Does the original overlap the following start time?
        extend current duration to the new end time
Pick the maximum duration

Longest without milking (O(n^2)):
Start with the same map
For each end time:
    For each start/end pair:
        make sure the end time isn't surrounded
    For each start/end pair:
        if the start is later, find the space between them
    return the minimum distance found
Pick the maximum duration
*/

#include <fstream>
#include <map>

#define MAX(a, b) a > b ? a : b;
#define MIN(a, b) a < b ? a : b;

#include <iostream>

// Takes an iterator so that we know where to start. And it passes by value so we don't change it 
uint findDurationOfMilking(std::map<uint, uint>::iterator i, const std::map<uint, uint>::iterator& endIterator) {
    const uint start = i->first;
    uint end = i->second;

    // Start at ++i instead of the beginning cause we don't care about older start times
    for (++i; i != endIterator; ++i) {
        // This start (and all future ones) are too late; they start after we've ended
        if (i->first > end)
            break;
        // New time starts before we've already ended
        // Update ending time
        end = MAX(i->second, end);
    }
    return end - start;
}

// Check to make sure it isn't surrounded (this means it is an "end-of-milking-point")
// Find soonest start after
// Difference is duration
uint findDurationWithoutMilking(const uint& endTime, std::map<uint, uint>& times) {
    uint duration = -1; // largest number; actual duration will be less than this

    for (std::map<uint,uint>::iterator i = times.begin(); i != times.end(); ++i) {
        // End time is surrounded, so it can't be an "end-of-milking-point"
        if (i->first <= endTime && i->second > endTime)
            return 0;
        
        // If we find a start time later than the endTime, update duration as the time between them
        // This may be for naught if we return 0 earlier, so maybe this should be in a different for loop? I don't think it matters
        if (i->first > endTime) {
            duration = MIN(duration, i->first - endTime);
        }
    }

    // If we never found a bigger start time, just return 0
    return duration == -1 ? 0 : duration;
}

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

    // Find longest duration of milking
    uint durationMilking = 0;

    for (std::map<uint, uint>::iterator i = times.begin(); i != times.end(); ++i) {
        durationMilking = MAX(durationMilking, findDurationOfMilking(i, times.end()));
    }

    // Find longest duration without milking
    uint durationNoMilking = 0;

    for (std::map<uint, uint>::iterator i = times.begin(); i != times.end(); ++i) {
        durationNoMilking = MAX(durationNoMilking, findDurationWithoutMilking(i->second, times));
    }


    std::ofstream outfile("milk2.out");
    outfile << durationMilking << ' ' << durationNoMilking << std::endl;
    outfile.close();
}