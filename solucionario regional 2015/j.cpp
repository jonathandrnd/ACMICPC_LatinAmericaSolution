#include <iostream>
#include <cstdio>
#define f(i,x,y) for(int i = x; i < y; i++)
using namespace std;
typedef long long ll;

ll mod = 1e9 + 7;
ll modpow(ll a, ll pot) {
	ll res = 1;
	for (; pot; pot >>= 1) {
		if (pot&1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

ll C[5005], P[5005];

int main(){
	int n, q;
	while ( scanf("%d%d", &n, &q) == 2 ){
		f(i, 0, n + 1) P[i] = modpow(i, n);
		C[0] = 1;
		f(i, 1, n) C[i] = C[i-1] * (n-i+1) % mod * modpow(i, mod-2) % mod;
		int x;
		f(t, 0, q){
			scanf("%d", &x);
			x = min(x, n);
			ll ans = 0;
			f(i,0,x){
				ans += (i&1? -1 : 1) * C[i] * P[x - i] % mod;
			}
			ans = (ans % mod + mod) % mod;
			printf("%lld%c", ans, t+1 == q? 10 : 32);
		}
	}
	
	return 0;
}
