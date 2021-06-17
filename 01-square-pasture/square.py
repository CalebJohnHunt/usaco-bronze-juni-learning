def main():
    with open('square.in', 'r') as f:
        temp = [int(i) for i in f.read().strip().split()]
    left = min(temp[::2])
    right = max(temp[::2])
    bottom = min(temp[1::2])
    top = max(temp[1::2])

    ans = max(right - left, top - bottom) ** 2

    with open('square.out', 'w') as f:
        f.write(str(ans))
        f.write('\n')


if __name__ == '__main__':
    main()