'''
ID: caleb.h1
LANG: PYTHON3
PROG: crypt1
'''

def hasBadDigits(n, digits):
    for char in str(n):
        if not char in digits:
            return True
    return False


def main():
    digits = set()
    solutionsCount = 0
    with open("crypt1.in", "r") as f:
        f.readline()

        for i in f.readline().split():
            digits.add(i)
    
    # firstNum is 3 digits
    for firstNum in range(100, 1000):
        # firstNum has viable digits
        if hasBadDigits(firstNum, digits):
            continue
        # secondNum is 2 digits
        for secondNum in range(10, 100):
            # seconNum has viable digits
            if hasBadDigits(secondNum, digits):
                continue

            firstProduct = firstNum * (secondNum % 10)


            # firstProduct is 3 digits
            if firstProduct < 100 or firstProduct > 999:
                continue
            # firstProduct contains viable numbers
            if hasBadDigits(firstProduct, digits):
                continue

            secondProduct = firstNum * (secondNum // 10)


            # secondProduct is 3 digits
            if secondProduct < 100 or secondProduct > 999:
                continue
            # secondProduct has viable numbers
            if hasBadDigits(secondProduct, digits):
                continue
            
            product = firstProduct + secondProduct * 10
            
            # product has 4 digits
            if product < 1000 or product > 9999:
                continue
            if hasBadDigits(product, digits):
                continue

            solutionsCount += 1

    with open("crypt1.out", "w") as f:
        f.write(f'{solutionsCount}\n')

if __name__ == '__main__':
    main()