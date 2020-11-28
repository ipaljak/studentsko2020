#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 100005;

int n, m, poc, kraj, t;
int prv[MAXN], nxt[MAXN], ok[MAXN];
llint f[MAXN], sum[MAXN], ofs[MAXN], pos[MAXN], cost[MAXN], dp[MAXN];
vector <int> v[MAXN];

llint get_val (llint len) {
    int ind = upper_bound(f, f + m, len) - f;
    if (ind == 0) return sum[m - 1] - m * len;
    return ind * len - sum[ind - 1] + (sum[m - 1] - sum[ind - 1]) - (m - ind) * len;
}

int beats (int a, int b) {
    int lo = b + 1, hi = n + 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (dp[a] + get_val(pos[mid] - pos[a]) >= dp[b] + get_val(pos[mid] - pos[b])) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void izbaci (int ind) {
    if (ok[ind] == 0) return;
    ok[ind] = 0;
    if (ind == poc) {
        poc = nxt[ind];
    } else if (ind == kraj) {
        kraj = prv[ind];
    } else {
        nxt[prv[ind]] = nxt[ind];
        prv[nxt[ind]] = prv[ind];
        v[max(beats(prv[ind], nxt[ind]), t)].push_back(nxt[ind]);
    }
}

void ubaci (int ind) {
    if (ok[ind] == 1) return;
    ok[ind] = 1;
    if (kraj == 0) {
        poc = kraj = ind;
    } else {
        prv[ind] = kraj;
        nxt[kraj] = ind;
        kraj = ind;
        v[max(beats(prv[ind], ind), t)].push_back(ind);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> f[i];
    }
    sort(f, f + m);
    for (int i = 0; i < m; i++) {
        if (i == 0) sum[i] = f[i]; else sum[i] = f[i] + sum[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> pos[i] >> cost[i];
    }
    for (int i = 1; i <= n; i++) {
        t = i;
        if (i > 1) ubaci(i - 1);
        while (!v[i].empty()) {
            int x = v[i].back();
            v[i].pop_back();
            izbaci(x);
        }
        if (i == 1) {
            dp[i] = -cost[i];
        } else {
            dp[i] = dp[kraj] + get_val(pos[i] - pos[kraj]) - cost[i];
        }
        //cout << "best " << i << " " << kraj << '\n';
    }
    cout << dp[n];
    return 0;
}

