#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;

int n, k;
int fact[MAXN];

inline int add(int a, int b) {
  if (a + b >= MOD) return a + b - MOD;
  if (a + b < 0) return a + b + MOD;
  return a + b;
}

inline int mul(int a, int b) {
  return (llint) a * b % MOD;
}

int fpow(int a, int b) {
  int ret = 1;
  while (b) {
    if (b & 1) {
      ret = mul(ret, a);
      --b;
    }
    a = mul(a, a);
    b >>= 1;
  }
  return ret;
}

inline int inv(int x) {
  return fpow(x, MOD - 2);
}

int main(void) {
  scanf("%d%d", &n, &k);

  fact[0] = 1;
  for (int i = 1; i < MAXN; ++i)
    fact[i] = mul(fact[i - 1], i);

  int sol = 1;
  for (llint i = (llint) n * k + 1; i > (llint) n * k + 1 - n; --i)
    sol = mul(sol, i % MOD);
  sol = mul(sol, inv(fact[n]));
  sol = mul(sol, inv(((llint) n * k + 1) % MOD));

  printf("%d\n", sol);
  return 0;
}
