"""
ID: caleb.h1
LANG: PYTHON3
PROG: milk
"""

MAX_FARMERS = 1001

def main():

    with open("milk.in", "r") as f:
        milkToBuy, numOfFarmers = (int(i) for i in f.readline().split())

        quantityAtPrice = [0] * MAX_FARMERS

        for _ in range(numOfFarmers):
            price, quantity = (int(i) for i in f.readline().split())
            quantityAtPrice[price] += quantity

    moneySpent = 0

    price = 0
    while milkToBuy > 0:
        quantity = min(milkToBuy, quantityAtPrice[price])
        milkToBuy -= quantity
        moneySpent += price * quantity
        price += 1
    
    with open("milk.out", "w") as f:
        f.write(f'{moneySpent}\n')

if __name__ == '__main__':
    main()