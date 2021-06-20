"""
ID: caleb.h1
LANG: PYTHON3
PROG: milk2
"""


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

    times = [[key, times[key]] for key in times]

    # merge


    i = 0
    while i < len(times):
        while i + 1 < len(times) and times[i+1][0] <= times[i][1]:
            times[i][1] = max(times[i][1], times[i+1][1]) # cur.end = max(cur.end, next.end)
            times.pop(i+1) # merge times together by removing overlapping one
        i+=1
    
    milkingDuration = max( [ i[1] - i[0] for i in times ] )
    noMilkingDuration = 0
    for i in range(len(times) - 1):
        noMilkingDuration = max(times[i+1][0] - times[i][1], noMilkingDuration)
    
    with open('milk2.out', 'w') as f:
        f.write(f'{milkingDuration} {noMilkingDuration}\n')



if __name__ == '__main__':
    main()