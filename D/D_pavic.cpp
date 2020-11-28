#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

#define PB push_back
#define X first
#define Y second

using namespace std;

typedef long double ld;
typedef pair < int, int > pt;

vector < pt > v;
int n;	

bool cmpX(pt A, pt B){
	if(A.X == B.X) return A.Y < B.Y;
	return A.X < B.X;
}

bool cmpY(pt A, pt B){
	if(A.Y == B.Y) return A.X < B.X;
	return A.Y < B.Y;
}

ld manhattan(pt A, pt B){
	return (ld)abs(A.X - B.X) + (ld)abs(A.Y - B.Y);
}

ld euclid(pt A, pt B){
	return sqrt((ld)(A.X - B.X) * (A.X - B.X) + (ld)(A.Y - B.Y) * (A.Y - B.Y));
}

ld omjer(pt A, pt B){
	return manhattan(A, B) / euclid(A, B);
}



int main(){
	scanf("%d", &n);
	for(int i = 0;i < n;i++){
		int x, y; scanf("%d%d", &x, &y);
		v.PB({x, y});
	}
	ld ans = 1e9;
	sort(v.begin(), v.end(), cmpX);
	for(int i = 1;i < (int)v.size();i++)
		ans = min(ans, omjer(v[i], v[i - 1]));
	sort(v.begin(), v.end(), cmpY);
	for(int i = 1;i < (int)v.size();i++)
		ans = min(ans, omjer(v[i], v[i - 1]));
	printf("%.15Lf\n", ans);
	return 0;
}
