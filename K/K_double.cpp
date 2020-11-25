#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 5e5 + 10;

int n, a, b;
double p[MAXN];

int calc() {
  int x = a, y = a + b;
  for (int i = 0; i < n; ++i) {
    if (y == 0 || (double) x / y >= p[i]) ++x;
    ++y;
  }
  return x;
}

int main(void) {
  scanf("%d%d%d", &a, &b, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%%", &p[i]);
    p[i] /= (double) 100;
  }

  sort(p, p + n);
  reverse(p, p + n);
  printf("%d ", calc());

  reverse(p, p + n);
  printf("%d\n", calc());

  return 0;
}
