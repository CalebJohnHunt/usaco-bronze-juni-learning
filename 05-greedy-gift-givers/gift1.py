"""
ID: caleb.h1
LANG: PYTHON3
PROG: gift1
"""

def main():
    wallets = dict()
    names = []

    with open('gift1.in', 'r') as f:

        # Count people
        numPeople = int(f.readline())

        # Add people to dictionary
        for _ in range(numPeople):
            name = f.readline().strip()
            names.append(name)
            wallets[name] = 0

        # Main loop
        # Take how much they're giving, remove it from the giver's wallet, split it to the friends
        money = 0
        while (name := f.readline().strip()):
            # std::cout << "Giver: " << name << std::endl;
            money, numPeople = (int(n) for n in f.readline().strip().split())
            # std::cout << "Giving: " << money << std::endl;

            if numPeople > 0: # If there are no receipiants, no need to deduct money
                # Remove money from giver
                wallets[name] -= money
                wallets[name] += money % numPeople # Leftover money after giving it out

                # Give money to receivers
                for _ in range(numPeople):
                    wallets[f.readline().strip()] += money // numPeople; # int division OK

    with open('gift1.out', 'w') as f:
        for name in wallets:
            f.write(f'{name} {wallets[name]}\n')


if __name__ == '__main__':
    main()