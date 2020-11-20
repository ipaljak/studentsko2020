#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 10;

int t, n;
int c[MAXN], dp[2 * MAXN], greedy[2 * MAXN];

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &c[i]);

  bool ok = true;
  dp[0] = greedy[0] = 0;
  for (int i = 1; i <= 10000; ++i) {
    dp[i] = greedy[i] = i + 5;
    for (int j = 0; j < n && c[j] <= i; ++j) {
      greedy[i] = 1 + greedy[i - c[j]];
      dp[i] = min(dp[i], 1 + dp[i - c[j]]);
    }
    ok &= greedy[i] == dp[i];
  }

  if (ok) printf("DA\n"); else printf("NE\n");
}

int main(void) {
  scanf("%d", &t);
  while (t--) solve();
  return 0;
}
