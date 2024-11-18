def knapsack(W, V, C):
    n = len(W)
    K = [[0 for _ in range(C + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, C + 1):
            if W[i-1] > w:
                K[i][w] = K[i - 1][w]
            else:
                K[i][w] = max(K[i - 1][w], V[i - 1] + K[i - 1][w - W[i - 1]])
    
    return K

def printC(K, W, V, C):
    n = len(W)
    header = f"물건    가치    무게    " + "  ".join([f"W={i}" for i in range(C + 1)])
    print(header)

    for i in range(n + 1):
        if i == 0:
            row = f"  -      -       -     " + "  ".join([f"{x:3}" for x in K[i]])
        else:
            row = f"  {i}     {V[i - 1]:3}     {W[i - 1]:3}    " + "  ".join([f"{x:3}" for x in K[i]])
        print(row)


W = [5, 4, 6, 3]
V = [10, 40, 30, 50]
C = 10 

result = knapsack(W, V, C)

printC(result, W, V, C)