#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

const int MAXN = 1e5 + 10;

const double EPSILON = 1e-12;

inline bool lt(const double a, const double b) { return b - a > EPSILON; }

inline bool gt(const double a, const double b) { return lt(b, a); }
inline bool eq(const double a, const double b) { return !lt(a, b) && !lt(b, a); }
inline bool le(const double a, const double b) { return !gt(a, b); }
inline bool ge(const double a, const double b) { return !lt(a, b); }

int r, n;
int x[MAXN], y[MAXN];

vector<pair<double, int>> event;

bool cmp(const pair<double, int> &A, const pair<double, int> &B) {
  if (!eq(A.first, B.first)) return lt(A.first, B.first);
  return A.second > B.second;
}

int main(void) {
  scanf("%d%d", &n, &r);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &x[i], &y[i]);

  for (int i = 0; i < n; ++i) {
    if (y[i] > r) continue;
    double lo = (double) x[i] - sqrt((llint) r * r - (llint) y[i] * y[i]);
    double hi = (double) x[i] + sqrt((llint) r * r - (llint) y[i] * y[i]);
    event.emplace_back(lo, 1);
    event.emplace_back(hi, -1);
  }

  sort(event.begin(), event.end(), cmp);

  int sol = 0, curr = 0;
  for (auto &e : event) {
    curr += e.second;
    sol = max(sol, curr);
  }

  printf("%d\n", sol);
  return 0;
}
