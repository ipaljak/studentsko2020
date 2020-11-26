#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 2005;
const int OFS = 1000;

int n, lox = OFS, loy = OFS, hix = OFS, hiy = OFS;
char c[MAXN][MAXN];

void precompute () {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            c[i][j] = ' ';
            if (i == OFS) c[i][j] = '-';
            if (j == OFS) c[i][j] = '|';
        }
    }
    c[OFS][OFS] = 'o';
}

void ispis () {
    for (int j = loy - 1; j <= hiy + 1; j++) cout << '#'; cout << '\n';
    for (int i = lox; i <= hix; i++) {
        cout << '#';
        for (int j = loy; j <= hiy; j++) cout << c[i][j];
        cout << '#';
        cout << '\n';
    }
    for (int j = loy - 1; j <= hiy + 1; j++) cout << '#'; cout << '\n';
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    precompute();
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        swap(x, y);
        x *= -1;
        x += OFS; y += OFS;
        c[x][y] = 'x';
        lox = min(lox, x); hix = max(hix, x);
        loy = min(loy, y); hiy = max(hiy, y);
    }
    ispis();
    return 0;
}
