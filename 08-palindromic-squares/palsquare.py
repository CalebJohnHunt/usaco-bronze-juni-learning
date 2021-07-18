"""
ID: caleb.h1
LANG: PYTHON3
PROG: palsquare
"""

# Map numbers to higher base digits
# 0 -> 0, 5 -> 5
# 10 -> a, 15 -> f
def convertNumToDigit(c: int) -> str:
    if c < 10:
        return str(c)
    return chr(c - 10 + ord('A'))

def tenToBase(number: int, base: int) -> str:
    newNumber: str = ""
    
    while (number > 0):
        newNumber = convertNumToDigit(number % base) + newNumber
        number //= base

    return newNumber

def isPalindrome(s: str) -> bool:
    for i in range(len(s) // 2):
        if s[i] != s[len(s) - i - 1]:
            return False
    
    return True


def main() -> None:

    with open("palsquare.in", "r") as f:
        base: int = int(f.readline())

    with open("palsquare.out", "w") as f:
        for i in range(1, 301):
            square: int = i * i
            squareString: str = tenToBase(square, base)
            if isPalindrome(squareString):
                f.write(f'{tenToBase(i, base)} {squareString}\n')

if __name__ == '__main__':
    main()

