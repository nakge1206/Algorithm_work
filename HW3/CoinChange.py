def CoinChange(W):
    change = W
    n500, n100, n50, n10 = 0, 0, 0, 0
    while change >= 500:
        change -= 500
        n500 += 1
    while change >= 100:
        change -= 100
        n100 += 1
    while change >= 50:
        change -= 50
        n50 += 1
    while change >= 10:
        change -= 10
        n10 += 1
    return [n500, n100, n50, n10]

def main():
    given = 2780
    result = CoinChange(given)
    print(f"{given} Won - 500 Won: {result[0]}, 100 Won: {result[1]}, 50 Won: {result[2]}, 10 Won: {result[3]}")

if __name__ == "__main__":
    main()

