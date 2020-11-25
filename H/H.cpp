#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

bool col[MAXN], bio[MAXN];

int n;
int lvl[MAXN];

vector<int> v[MAXN];
priority_queue<pair<int, int>> pq;

void dfs(int node, int dad) {
  for (int nxt : v[node]) {
    if (nxt == dad) continue;
    lvl[nxt] = lvl[node] + 1;
    dfs(nxt, node);
  }
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    col[i] = (x == 1);
  }

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    scanf("%d%d", &a, &b); --a; --b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  dfs(0, -1);

  for (int i = 0; i < n; ++i)
    if (col[i])
      pq.push({lvl[i], i});

  vector<int> sol;
  while (!pq.empty()) {
    while (!pq.empty() && (bio[pq.top().second] || !col[pq.top().second]))
      pq.pop();
    if (pq.empty()) break;
    auto p = pq.top(); pq.pop();
    sol.push_back(p.second);
    bio[p.second] = true;
    for (int nxt : v[p.second]) {
      col[nxt] = !col[nxt];
      if (bio[nxt] || !col[nxt]) continue;
      pq.push({lvl[nxt], nxt});
    }
  }

  if (sol.size() != n) {
    printf("PORAZ\n");
    return 0;
  }

  printf("POBJEDA\n");
  for (int x : sol) printf("%d ", x + 1);
  printf("\n");

  return 0;
}
