""" 
ID: caleb.h1
LANG: PYTHON3
PROG: transform
"""

from copy import deepcopy
from types import new_class

def isSame(first, second) -> bool:
    for i in range(len(first)):
        for j in range(len(first)):
            if first[i][j] != second[i][j]:
                return False

    return True


def print2dArray(array):
    for row in array:
        for char in row:
            print(char, end='')
        print()

def rotate2dArray(array):
    copy = deepcopy(array)
    for i in range(len(array)):
        for j in range(len(array)):
            array[i][j] = copy[len(array)-j-1][i]
        
def flip2dArray(array):
    copy = deepcopy(array)
    for i in range(len(array)):
        for j in range(len(array)):
            array[i][j] = copy[i][len(array)-j-1]


# Find the manipulations needed to get the startSquare to the endSquare
def findPattern(startSquare, endSquare):
    
    # 1, 2, 3: N 90 degrees rotations
    for i in range(1, 4):
        rotate2dArray(startSquare)
        if (isSame(startSquare, endSquare)):
            return i
    

    # rotate startSquare so it's normal again
    rotate2dArray(startSquare)

    # 4: Flipped
    flip2dArray(startSquare)
    if (isSame(startSquare, endSquare)):
        return 4

    # 5: Combination (Flip + any rotate)
    for i in range(4):
        rotate2dArray(startSquare)
        if (isSame(startSquare, endSquare)):
            return 5
    
    
    # 6: No change
    if (isSame(startSquare, endSquare)):
        return 6

    # 7: Invalid
    return 7

def create2dArray(N):
    array = []
    for i in range(N):
        sub_array = []
        for j in range(N):
            sub_array.append(0)
        array.append(sub_array)
    return array

def main():
    # Read in file
    with open("transform.in", "r") as f:
        N = int(f.readline())


        startSquare = create2dArray(N)
        endSquare = create2dArray(N)

        for i in range(N):
            for j in range(N):
                startSquare[i][j] = f.read(1)
            # remove newline char
            f.read(1)
        
        for i in range(N):
            for j in range(N):
                endSquare[i][j] = f.read(1)
            # remove newline char
            f.read(1)
    
    with open("transform.out", "w") as f:
        f.write(str(findPattern(startSquare, endSquare)))
        f.write('\n')
    
if __name__ == '__main__':
    main()