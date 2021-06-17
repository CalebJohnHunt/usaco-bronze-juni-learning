"""
ID: caleb.h1
LANG: PYTHON3
PROG: beads
"""

def count_beads(index, beads, size):
    counter = 0
    i = index
    for _ in range(2):
        color = ''
        while counter < size and (beads[i] == 'w' or beads[i] == color or not color):
            if not color and beads[i] != 'w':
                color = beads[i]
            i += 1
            counter += 1
    return counter

def main():
    with open('beads.in', 'r') as f:
        size = int(f.readline())
        beads = f.read().strip() * 2
    

    count = 0
    for c in range(size):
        count = max(count, count_beads(c, beads, size))
    
    with open('beads.out', 'w') as f:
        f.write(str(count)+'\n')

if __name__ == '__main__':
    main()