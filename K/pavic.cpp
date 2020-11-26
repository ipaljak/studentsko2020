#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#define PB push_back

typedef long long ll;

using namespace std;

vector < int > v;
ll sA, sB, A, B;
int n;

int main(){	
	scanf("%lld%lld%d", &sA, &sB, &n);
	for(int i = 0;i < n;i++){
		double x; char bla;
		scanf("%lf %c", &x, &bla);
		v.PB((int) round(x * 100));
	}
	sort(v.rbegin(), v.rend());
	A = sA, B = sB;
	for(int i = 0;i < n;i++){
		//printf("v = %d A = %lld B = %lld\n", v[i], A, B);
		if(A * 10000 >= (A + B) * v[i])
			A++;
		else
			B++;
	}
	printf("%lld ", A);
	sort(v.begin(), v.end());
	A = sA, B = sB;
	for(int i = 0;i < n;i++){
		if(A * 10000 >= (A + B) * v[i])
			A++;
		else
			B++;
	}
	printf("%lld\n", A);
	return 0;
}
