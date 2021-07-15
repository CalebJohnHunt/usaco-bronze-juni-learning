"""
ID: caleb.h1
LANG: PYTHON3
PROG: milk
"""

def main():

    with open("milk.in", "r") as f:
        milkToBuy, numOfFarmers = (int(i) for i in f.readline().split())

        # dict setup
        # prices[price] = quantity
        prices = {}

        for _ in range(numOfFarmers):
            price, quantity = (int(i) for i in f.readline().split())
            # If this is a new price
            if not price in prices:
                prices[price] = quantity
            else:
                prices[price] += quantity

    keys = sorted(prices)

    moneySpent = 0

    # Go through each farmer (starting least expensive to move)
    # Either buy them out or buy as much as we need
    # No need to worry about the iterator b/c we are guarenteed enough milk is offered
    for price in keys:
        if milkToBuy <= 0:
            break
        order = min(milkToBuy, prices[price])
        milkToBuy -= order
        moneySpent += price * order
    
    with open("milk.out", "w") as f:
        f.write(f'{moneySpent}\n')

if __name__ == '__main__':
    main()