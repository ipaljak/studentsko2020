#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;

int n;
int pic[MAXN][MAXN];

set<pair<int, int>> s;

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    s.insert({x, y});
  }

  int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
  for (auto &p : s) {
    xmin = min(xmin, p.first);
    xmax = max(xmax, p.first);
    ymin = min(ymin, p.second);
    ymax = max(ymax, p.second);
  }

  int row = ymax - ymin + 2;
  int col = xmax - xmin + 2;

  memset(pic, '#', sizeof pic);
  for (int i = 1; i < row; ++i)
    for (int j = 1; j < col; ++j)
      pic[i][j] = ' ';

  for (int i = 1; i < row; ++i)
    pic[i][1 - xmin] = '|';

  for (int j = 1; j < col; ++j)
    pic[ymax + 1][j] = '-';

  pic[ymax + 1][1 - xmin] = 'o';

  for (auto &p : s)
    pic[1 + ymax - p.second][1 + p.first - xmin] = 'x';

  for (int i = 0; i <= row; ++i) {
    for (int j = 0; j <= col; ++j)
      printf("%c", pic[i][j]);
    printf("\n");
  }
  return 0;
}
