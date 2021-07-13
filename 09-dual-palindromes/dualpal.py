"""
ID: caleb.h1
LANG: PYTHON3
PROG: dualpal
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

def main():
    with open("dualpal.in", "r") as f:
        N, S = [int(i) for i in f.readline().split()]

    foundNumbers = 0
    curNumber = S+1
    with open("dualpal.out", "w") as f:
        while foundNumbers < N:

            numOfBasesWherePalindromic = 0
            for base in range(2, 11):
                if numOfBasesWherePalindromic < 2 and isPalindrome(tenToBase(curNumber, base)):
                    numOfBasesWherePalindromic += 1
            
            if numOfBasesWherePalindromic > 1:
                f.write(f'{curNumber}\n')
                foundNumbers += 1
            curNumber += 1

if __name__ == '__main__':
    main()