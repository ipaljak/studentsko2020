#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 1005;
const int OFS = 2100000000;

int L, n;
int sx, sy, ex, ey;
int sol[MAXN];
unordered_set <llint> st;
vector <llint> v;

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, -1, 1};

void normalize (int &x, int &y) {
    int d;
    if (x == 0 || y == 0) d = max(abs(x), abs(y)); else d = __gcd(abs(x), abs(y));
    x /= d; y /= d;
}

int sign (int a) {
    if (a >= 0) return 0; else return 1;
}

llint spoji (int a, int b) {
    return ((llint) (2 * abs(a) + sign(a))) * OFS + (2 * abs(b) + sign(b));
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> L >> n >> sx >> sy >> ex >> ey;
    for (int i = 0; i <= n; i++) {
        v.clear();
        for (int x = -i; x <= i; x++) {
            int ay = i - abs(x);
            for (int s = -1; s <= 1; s += 2) {
                int y = ay * s;
                if (y == 0 && s == 1) break;

                int cx = 2 * L * x - sx, cy = 2 * L * y - sy;
                if (x % 2 == 0) cx += ex; else cx -= ex;
                if (y % 2 == 0) cy += ey; else cy -= ey;
                normalize(cx, cy);

                if (st.find(spoji(cx, cy)) == st.end()) {
                    sol[i]++;
                    v.push_back(spoji(cx, cy));
                }
                for (int k = 0; k < 4; k++) {
                    int nx = (2 * x + dx[k]) * L - sx, ny = (2 * y + dy[k]) * L - sy;
                    normalize(nx, ny);
                    v.push_back(spoji(nx, ny));
                }
            }
        }
        for (auto val : v) {
            st.insert(val);
        }
        cout << sol[i] << " ";
    }
    return 0;
}
