def choose(n, k):
    ret = 1
    for i in range(k):
        ret *= (n - i)
    for i in range(k):
        ret //= i + 1
    return ret

n, k = map(int, input().split())
MOD = 10 ** 9 + 7
print((choose(n * k + 1, n) // (n * k + 1)) % MOD)
