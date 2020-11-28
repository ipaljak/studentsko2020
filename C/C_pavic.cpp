#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;

const int N = 1e5 + 500;
const int M = 1e7 + 500;

int n, m, pos[N], tren;
ll swpL[M], L[M], dp[N], cost[N];
vector < ll > delta;
vector < int > zaizb[N];
set < int > S;

int nestaje(int i, int j){
	int k = j;
	for(int a = 17;a >= 0;a--){
		if(k + (1 << a) < n &&
		 dp[i] + L[pos[k + (1 << a)] - pos[i]] <= dp[j] + L[pos[k + (1 << a)] - pos[j]])
			k += (1 << a);
	}
	return k + 1;
}

void izbaci(int i){
	if(S.count(i) == 0)
		return;
	S.erase(i);
	if(S.lower_bound(i) != S.end()){
		int prv = *(--S.lower_bound(i));
		int nxt = *S.lower_bound(i);
		zaizb[max(nestaje(prv, nxt), tren)].PB(nxt);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++){
		int x; scanf("%d", &x);
		if(x >= 1) 
			swpL[x - 1]++; 
		L[x + 1]++;
	}
	for(int i = 0;i < n;i++)
		scanf("%d%lld", pos + i, cost + i);
	for(int k = 0;k < 2;k++){
		for(int i = 1;i < M;i++)
			L[i] += L[i - 1];
		for(int i = M - 1;i >= 0;i--)
			swpL[i] += swpL[i + 1];
	}
	for(int i = 0;i < M;i++){
		L[i] += swpL[i];
	}
	S.insert(0);
	dp[0] = -cost[0];
	for(int i = 1;i < n;i++){
		tren = i;
		for(int j = 0;j < (int)zaizb[i].size();j++)
			izbaci(zaizb[i][j]);
		dp[i] = dp[*S.rbegin()] - cost[i] + L[pos[i] - pos[*S.rbegin()]];
		zaizb[nestaje(*S.rbegin(), i)].PB(i);
		S.insert(i);
	}	
	printf("%lld\n", dp[n - 1]);
	return 0;
}
