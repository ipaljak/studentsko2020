#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 100005;
const llint INF = 1000000000000000000LL;

int n, m, poc, kraj;
int prv[MAXN], nxt[MAXN], ok[MAXN];
llint f[MAXN], sum[MAXN], ofs[MAXN], pos[MAXN], cost[MAXN], dp[MAXN];

llint get_val (llint len) {
    int ind = upper_bound(f, f + m, len) - f;
    if (ind == 0) return sum[m - 1] - m * len;
    return ind * len - sum[ind - 1] + (sum[m - 1] - sum[ind - 1]) - (m - ind) * len;
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
    dp[1] = -cost[1];
    for (int i = 2; i <= n; i++) {
        llint res = -INF;
        for (int j = 1; j <= min(10, i - 1); j++) {
            res = max(res, dp[j] + get_val(pos[i] - pos[j]) - cost[i]);
            if (i - j >= 1) res = max(res, dp[i - j] + get_val(pos[i] - pos[i - j]) - cost[i]);
        }
        dp[i] = res;
    }
    cout << dp[n];
    return 0;
}

