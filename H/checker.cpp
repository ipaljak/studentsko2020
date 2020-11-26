// Checker to be used by HSIN evaluator.
//
// This should *not* be used for CMS!
//
// Usage: [checker] [input] [official_output] [contestant_output] [configuration_file (optional)]
//
// Output (stdout):
//     Score.
//     Textual description (optional).
//
// Score should be output as an integer (0 or 1), or a real (between 0.0 and
// 1.0) or a fraction (between `0/1` and `1/1`, you don't have to
// simplify/reduce the fraction).

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

const int MAXN = 2e5 + 10;

// Use one of the following functions to output the points to the contestant.
// The first accepts a double and outputs it.
// The second accepts a fraction and outputs it.

void finish(double score) {
  cout << score << endl;
  exit(0);
}

void finish(llint points_awarded, llint points_max) {
  cout << points_awarded << "/" << points_max << endl;
  exit(0);
}

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream &fin, ifstream &foff, ifstream &fout) {
  // Read official input
  int n;
  bool col[MAXN], bio[MAXN];
  vector<int> v[MAXN];

  if (!(fin >> n)) finish(0);
  for (int i = 0; i < n; ++i) {
    int x;
    if (!(fin >> x)) finish(0);
    col[i] = (x == 1);
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    if (!(fin >> a)) finish(0);
    if (!(fin >> b)) finish(0);
    --a; --b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  // Read official output verdict
  string off_result;
  if (!(foff >> off_result)) finish(0);

  // Read contestant's output cerdict
  string usr_result;
  if (!(fout >> usr_result)) finish(0);

  if (off_result != usr_result) finish(0);
  if (off_result == "PORAZ") {
    string trash;
    if (fout >> trash) finish(0);
    finish(1);
  }

  vector<int> sol;
  for (int i = 0; i < n; ++i) {
    int x;
    if (!(fout >> x)) finish(0);
    sol.push_back(x);
  }

  string trash;
  if (fout >> trash) finish(0);

  for (int i = 0; i < n; ++i) bio[i] = false;
  for (int node : sol) {
    --node;
    if (bio[node] || !col[node]) finish(0);
    bio[node] = true;
    for (int nxt : v[node])
      col[nxt] = !col[nxt];
  }

  finish(1);

  // The function MUST terminate before this line via finish()!
}

int main(int argc, char *argv[]) {
  assert(argc >= 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  // Optional, uncomment when using the configuration file for additional
  // information about the testcase.
  // ifstream fconf(argv[4]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);

  // Checker must terminate via finish() before exiting!
  assert(false);

  return 0;
}
