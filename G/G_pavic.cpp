#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

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

int n, k;

int main(){
	scanf("%d%d", &n, &k);
	ll naz = (ll)n * k + 1;
	int ret = 1, potm = 0;
	for(int i = 0;i < n;i++){
		int x = (naz - i) % MOD;
		if(x == 0){
			x = ((naz - i) / MOD) % MOD;
			potm = 1;
		}
		ret = mul(ret, x);
		ret = div(ret, i + 1);
	}
	if(naz % MOD == 0){
		potm = 0;
		ret = div(ret, (naz / MOD) % MOD);
	}
	else{
		ret = div(ret, naz % MOD);
	}
	if(potm) ret = 0;
	printf("%d\n", ret);
	return 0;
}
