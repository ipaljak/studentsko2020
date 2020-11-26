#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 200005;

int n;
int s[MAXN];
int dub[MAXN], bio[MAXN];
vector <int> v[MAXN], sol;
priority_queue <pi> pq;

void dfs (int x, int rod) {
    dub[x] = 1 + dub[rod];
    for (auto sus : v[x]) {
        if (sus == rod) continue;
        dfs(sus, x);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i + 1];
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        if (s[i] == 1) pq.push({dub[i], i});
    }
    if (pq.size() % 2 == 0) {
        cout << "PORAZ\n";
        return 0;
    }
    while (!pq.empty()) {
        int x = pq.top().second;
        pq.pop();
        if (s[x] == 0 || bio[x]) continue;
        bio[x] = 1;
        sol.push_back(x);
        for (auto sus : v[x]) {
            if (bio[sus]) continue;
            if (s[sus] == 0) s[sus] = 1; else s[sus] = 0;
            if (s[sus] == 1) pq.push({dub[sus], sus});
        }
    }
    cout << "POBJEDA\n";
    for (auto x : sol) cout << x << " ";
    cout << "\n";
    return 0;
}
