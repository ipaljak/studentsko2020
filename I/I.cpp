#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 20005;

int t, n;
int c[MAXN], grd[MAXN], opt[MAXN];

bool check () {
    grd[0] = opt[0] = 0;
    for (int i = 1; i <= 2 * c[n]; i++) {
        opt[i] = 1e9;
        for (int j = 1; j <= n; j++) {
            if (i >= c[j]) {
                grd[i] = 1 + grd[i - c[j]];
                opt[i] = min(opt[i], 1 + opt[i - c[j]]);
            }
        }
        if (grd[i] != opt[i]) return 0;
    }
    return 1;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        if (check()) cout << "DA\n"; else cout << "NE\n";
    }
    return 0;
}
