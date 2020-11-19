#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 5e5 + 10;

int n, a, b;
int p[MAXN];

int calc() {
  int x = a, y = a + b;
  for (int i = 0; i < n; ++i) {
    if ((llint) x * 100 * 100 >= (llint) p[i] * y) ++x;
    ++y;
  }
  return x;
}

int main(void) {
  scanf("%d%d%d", &a, &b, &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d.%d%%", &x, &y);
    p[i] = x * 100 + y;
  }

  sort(p, p + n);
  reverse(p, p + n);
  printf("%d ", calc());

  reverse(p, p + n);
  printf("%d\n", calc());

  return 0;
}
