"""
ID: caleb.h1
LANG: PYTHON3
PROG: namenum
"""

def main():
    keypad = {
        '2': ('A','B','C'),
        '3': ('D','E','F'),
        '4': ('G','H','I'),
        '5': ('K','J','L'),
        '6': ('M','N','O'),
        '7': ('P','R','S'),
        '8': ('T','U','V'),
        '9': ('W','Y','Z'),
    }

    with open("dict.txt", 'r') as f:
        possibleNames = [i.strip() for i in f.readlines()]

    with open("namenum.in", 'r') as f:
        numbers = f.readline().strip()

    # The purge - Remove from the possibleNames ones that don't fit

    # Remove ones too long or too short
    for name in possibleNames.copy():
        if len(name) != len(numbers):
            possibleNames.remove(name)

    # Remove those that don't share letters
    for i in range(len(numbers)):
        letters = keypad[numbers[i]]
        for name in possibleNames.copy():
            if name[i] != letters[0] and name[i] != letters[1] and name[i] != letters[2]:
                possibleNames.remove(name)


    # Write NONE if no names match, otherwise all matching names
    with open("namenum.out", 'w') as f:
        if not len(possibleNames):
            f.write("NONE\n")
        else:
            for name in possibleNames:
                f.write(name+'\n')

if __name__ == '__main__':
    main()
