#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef long double ld;
typedef pair <llint, llint> pi;
typedef map <int, int> :: iterator iter;

const int MAXN = 300005;

int n;
pi p[MAXN];
map <int, int> mp;
ld sol = 1e9;

bool cmp (pi a, pi b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

llint ccw (pi a, pi b, pi c) {
    return a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second);
}

iter get_prv (iter it) {it--; return it;}
iter get_nxt (iter it) {it++; return it;}

bool ok (iter it) {
    if (it == mp.begin()) return 1;
    auto prv = get_prv(it);
    auto nxt = get_nxt(it);
    if (nxt == mp.end()) return 1;
    return ccw(*prv, *it, *nxt) < 0;
}

llint sq (llint val) {
    return val * val;
}

ld calc (pi a, pi b) {
    return ((ld) sq(abs(a.first - b.first) + abs(a.second - b.second))) / (sq(a.first - b.first) + sq(a.second - b.second));
}

void ubaci (int x, int y) {
    mp[x] = y;
    auto it = mp.find(x);
    while (it != mp.begin() && !ok(get_prv(it))) mp.erase(get_prv(it));
    while (get_nxt(it) != mp.end() && !ok(get_nxt(it))) mp.erase(get_nxt(it));
    if (it != mp.begin()) sol = min(sol, calc(*get_prv(it), *it));
    if (get_nxt(it) != mp.end()) sol = min(sol, calc(*get_nxt(it), *it));
}

void sweep () {
    sort(p, p + n, cmp);
    mp.clear();
    for (int i = 0; i < n; i++) {
        ubaci(p[i].first, p[i].second);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    sweep();
    for (int i = 0; i < n; i++) {
        swap(p[i].first, p[i].second);
        p[i].first *= -1;
    }
    sweep();
    cout << fixed << setprecision(15) << sqrt(sol) << endl;
    return 0;
}
