"""
ID: caleb.h1
LANG: PYTHON3
PROG: milk2
"""

 # Takes an iterator so that we know where to start. And it passes by value so we don't change it 
def findDurationOfMilking(start, times):
    end = times[start][1]

     # Start at ++i instead of the beginning cause we don't care about older start times
    for i in range(start+1, len(times)):
        # This start (and all future ones) are too late; they start after we've ended
        if times[i][0] > end:
            break
         # New time starts before we've already ended
         # Update ending time
        end = max(times[i][1], end)
    return end - times[start][0]


 # Check to make sure it isn't surrounded (this means it is an "end-of-milking-point")
 # Find soonest start after
 # Difference is duration
def findDurationWithoutMilking(endTime, times):
    duration = 1e30;  # largest number; actual duration will be less than this

    for i in range(len(times)):
         # End time is surrounded, so it can't be an "end-of-milking-point"
        if times[i][0] <= endTime and times[i][1] > endTime:
            return 0
        
         # If we find a start time later than the endTime, update duration as the time between them
         # This may be for naught if we return 0 earlier, so maybe this should be in a different for loop? I don't think it matters
    for i in range(len(times)):
        if times[i][0] > endTime:
            duration = min(duration, times[i][0] - endTime)
     # If we never found a bigger start time, just return 0
    return 0 if duration == 1e30 else duration


def main():
    with open('milk2.in', 'r') as f:

        # Beginning and ending times 1->5,000
        numTimes = int(f.readline())

        # Maps starting times to their ending times
        times = dict()

        for i in range(numTimes):
            s, e = (int(n) for n in f.readline().strip().split())
            # Duplciate checking
            try:
                times[s] = max(times[s], e)
            except:
                times[s] = e
        
    times = dict(sorted(times.items()))

    times = [(k, times[k]) for k in times]
    # Find longest duration of milking
    durationMilking = 0

    for i in range(len(times)):
        durationMilking = max(durationMilking, findDurationOfMilking(i, times))

    # Find longest duration without milking
    durationNoMilking = 0

    for i in range(len(times)):
        durationNoMilking = max(durationNoMilking, findDurationWithoutMilking(times[i][1], times))

    with open('milk2.out', 'w') as f:
        f.write(f'{durationMilking} {durationNoMilking}\n')

if __name__ == '__main__':
    main()