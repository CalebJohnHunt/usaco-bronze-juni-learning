"""
ID: caleb.h1
LANG: PYTHON3
PROG: namenum
"""

def main():
    keypad = {
        '2': {'A','B','C'},
        '3': {'D','E','F'},
        '4': {'G','H','I'},
        '5': {'K','J','L'},
        '6': {'M','N','O'},
        '7': {'P','R','S'},
        '8': {'T','U','V'},
        '9': {'W','Y','Z'},
    }

    with open("dict.txt", 'r') as f:
        possibleNames = [i.strip() for i in f.readlines()]

    with open("namenum.in", 'r') as f:
        numbers = f.readline().strip()

    # The purge - Remove from the possibleNames ones that don't fit

    # Remove ones too long or too short
    i = 0
    while i < len(possibleNames):
        if len(possibleNames[i]) != len(numbers):
            possibleNames.pop(i)
        else:
            i+=1

    # Remove those that don't share letters
    for i in range(len(numbers)):
        letters = keypad[numbers[i]]
        j = 0
        while j < len(possibleNames):
            name = possibleNames[j]
            if name[i] not in letters:
                possibleNames.pop(j)
            else:
                j += 1


    # Write NONE if no names match, otherwise all matching names
    if not possibleNames:
        open("namenum.out", 'w').write("NONE\n")
    else:
        print(*possibleNames, sep='\n', file=open("namenum.out", 'w'))

if __name__ == '__main__':
    main()
