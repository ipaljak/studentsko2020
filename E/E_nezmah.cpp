#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <llint, llint> pi;

const int MAXN = 300005;
const int LOG = 20;

int n, q;
llint sum[MAXN], dub[MAXN], par[MAXN][LOG], upp[MAXN][LOG], dwn[MAXN][LOG];
vector <int> v[MAXN];

void dfs (int x, int rod) {
    par[x][0] = rod;
    dub[x] = 1 + dub[rod];
    sum[x] = v[x].size();
    for (auto sus : v[x]) {
        if (sus == rod) continue;
        dfs(sus, x);
        sum[x] += sum[sus];
    }
}

void precompute () {
    for (int i = 2; i <= n; i++) {
        upp[i][0] = sum[i];
        dwn[i][0] = sum[1] - sum[i];
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
            upp[j][i] = upp[j][i - 1] + upp[par[j][i - 1]][i - 1];
            dwn[j][i] = dwn[j][i - 1] + dwn[par[j][i - 1]][i - 1];
        }
    }
}

int kth (int x, int k) {
    int pot = 0;
    while (k > 0) {
        if (k & 1) x = par[x][pot];
        k /= 2;
        pot++;
    }
    return x;
}

pi get_ex (int x, int k) {
    int pot = 0;
    llint res_upp = 0, res_dwn = 0;
    while (k > 0) {
        if (k & 1) {
            res_upp += upp[x][pot];
            res_dwn += dwn[x][pot];
            x = par[x][pot];
        }
        k /= 2;
        pot++;
    }
    return {res_upp, res_dwn};
}

int lca (int a, int b) {
    if (dub[a] < dub[b]) swap(a, b);
    a = kth(a, dub[a] - dub[b]);
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}

llint upit (int a, int b) {
    int d = lca(a, b);
    return get_ex(a, dub[a] - dub[d]).first + get_ex(b, dub[b] - dub[d]).second;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1, 0);
    precompute();
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << upit(a, b) << endl;
    }
    return 0;
}
