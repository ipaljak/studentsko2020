#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long double ld;

const int N = 1e5 + 500;

ld r;
int n;
vector < pair < ld, int > > v;

int main(){
	scanf("%d%Lf", &n, &r);
	for(int i = 0;i < n;i++){
		ld x, y; scanf("%Lf%Lf", &x, &y);
		if(abs(y) <= r){
			ld pom = sqrt(r * r - y * y);
			v.push_back({x + pom, 1});
			v.push_back({x - pom, 0});
		}
	}
	sort(v.begin(), v.end());
	int sol = 0, cur = 0;
	for(pair < ld, int > tmp : v){
		if(tmp.second)
			cur--;
		else
			cur++;
		sol = max(sol, cur);
	}
	printf("%d\n", sol);
	return 0;
}
