#include <bits/stdc++.h>

using namespace std;

typedef long long llint;

struct Node {
  int r, s, x, y;
  Node() {}
  Node(int r, int s, int x, int y): r(r), s(s), x(x), y(y) {}
  friend bool operator < (const Node &A, const Node &B) {
    return make_pair(A.r, A.s) < make_pair(B.r, B.s);
  }
};

struct Frac {
  int a, b;
  Frac () {}
  Frac (int _a, int _b) {
    a = _a; b = _b;
    int g = max(abs(a), abs(b));
    if (b != 0) g = __gcd(abs(a), abs(b));
    a /= g;
    b /= g;
  }
  friend bool operator < (const Frac &A, const Frac &B) {
    return make_pair(A.a, A.b) < make_pair(B.a, B.b);
  }
};

const int dr[] = {-1, 0, 1, 0};
const int ds[] = {0, -1, 0, 1};

int l, n, xs, ys, xf, yf;

set<Frac> blist;
set<Node> holes;

Frac dir(int x, int y) {
  return Frac(x - xs, y - ys);
}

void blacklist(const Node &curr) {
  for (int dx : {-1, 1})
    for (int dy : {-1, 1})
      blist.insert(dir(curr.r * 2 * l + dx * l, curr.s * 2 * l + dy * l));
  blist.insert(dir(curr.x, curr.y));
}

inline int count() {
  int ret = 0;
  for (auto &p : holes)
    ret += (int) (blist.find(dir(p.x, p.y)) == blist.end());
  return ret;
}

int mirror(int x, int a, int b) {
  if (a == b) return x;
  if (a < b) return x + 2 * (a * 2 * l + l - x);
  return x - 2 * (x - (a * 2 * l - l));
}

void move(int dst) {
  set<Node> nxt;
  for (const Node &curr : holes) {
    blacklist(curr);
    for (int i = 0; i < 4; ++i) {
      int r = curr.r + dr[i], s = curr.s + ds[i];
      if (abs(r) + abs(s) != dst) continue;
      nxt.insert(Node(r, s, mirror(curr.x, curr.r, r), mirror(curr.y, curr.s, s)));
    }
  }
  holes = nxt;
}

int main(void) {
  scanf("%d%d", &l, &n);
  scanf("%d%d%d%d", &xs, &ys, &xf, &yf);

  holes.insert(Node(0, 0, xf, yf));
  for (int i = 0; i < n; ++i) {
    printf("%d ", count()); fflush(stdout);
    move(i + 1);
  }

  printf("%d\n", count());

  return 0;
}
