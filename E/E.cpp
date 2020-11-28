#include <cstdio>
#include <cstring>
#include <vector>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int LOG = 20;
const int N = 3e5 + 500;

inline int add(int A, int B){
	if(A + B >= MOD)
		return A + B - MOD;
	return A + B;
}

inline int sub(int A, int B){
	if(A - B < 0)
		return A - B + MOD;
	return A - B;
}

inline int mul(int A, int B){
	return (ll)A * B % MOD;
}

inline int pot(int A, int B){
	int ret = 1, bs = A;
	for(; B ; B >>= 1){
		if(B & 1) ret = mul(ret, bs);
		bs = mul(bs, bs);
	}
	return ret;
}

inline int inv(int A){
	return pot(A, MOD - 2);
}

inline int div(int A, int B){
	return mul(A, inv(B));
}

int n, q;
int siz[N], deg[N], dep[N];
int up[N][LOG], down[N][LOG], par[N][LOG];
vector < int > v[N];

void dfs(int x, int lst){
	siz[x] = 1; dep[x] = dep[lst] + 1;
	for(int y : v[x]){
		if(y == lst) continue;
		dfs(y, x); siz[x] += siz[y];
		int E_vrac = div(2 * (siz[y] - 1), deg[y] - 1);
		up[y][0] = add(1, mul(deg[y] - 1, E_vrac));
		E_vrac = div(2 * (n - siz[y] - 1), deg[x] - 1);
		down[y][0] = add(1, mul(deg[x] - 1, E_vrac));
		par[y][0] = x; 
	}		
}

void precompute(){
	for(int j = 1;j < LOG;j++){
		for(int i = 1;i <= n;i++){
			par[i][j] = par[par[i][j - 1]][j - 1];
			up[i][j] = add(up[i][j - 1], up[par[i][j - 1]][j - 1]);
			down[i][j] = add(down[i][j - 1], down[par[i][j - 1]][j - 1]);
		}
	}
}

int get_ans(int x, int y){
	int ret = 0;
	for(int i = LOG - 1;i >= 0;i--)
		if(dep[x] - dep[y] >= (1 << i)){
			ret = add(ret, up[x][i]);
			x = par[x][i];
		}
	for(int i = LOG - 1;i >= 0;i--)
		if(dep[y] - dep[x] >= (1 << i)){
			ret = add(ret, down[y][i]);
			y = par[y][i];
		}		
	if(x == y) return ret;
	for(int i = LOG - 1;i >= 0;i--){
		if(par[x][i] != par[y][i]){
			ret = add(ret, add(up[x][i], down[y][i]));
			x = par[x][i], y = par[y][i];
		}
	}
	ret = add(ret, add(up[x][0], down[y][0]));
	return ret;
}


int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1;i < n;i++){
		int x, y; scanf("%d%d", &x, &y);
		v[x].PB(y), v[y].PB(x);
		deg[x]++, deg[y]++;
	}
	dfs(1, 1); precompute();
	for(int i = 0;i < q;i++){
		int x, y; scanf("%d%d", &x, &y);
		printf("%d\n", get_ans(x, y));
	}
	return 0;
}

