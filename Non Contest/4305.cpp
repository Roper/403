#include <cstdio>

const int mo = 1e9+7, N = 1e5+100;
int n;
int f[N], fac[N], fac2[N];

int Quick(int x, int y){
	if(y == 1) return x;
	int t = Quick(x, y/2);
	t = t*1LL*t % mo;
	if(y % 2) t = t*1LL*x % mo;
	return t;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d", &n);
	
	f[1] = 0;
	fac2[0] = fac[1] = 1;
	fac2[1] = 2;
	for(int i = 2; i <= n; i ++){
		fac[i] = fac[i - 1]*1LL*i % mo;
		fac2[i] = fac2[i - 1]*1LL*2 % mo;
		f[i] = (f[i - 1]*1LL*i % mo + fac[i - 1]*(fac2[i - 1] - 1LL) % mo) % mo;
	}
	
	printf("%d", f[n]*1LL*Quick(fac[n], mo - 2) % mo);
	
	return 0;
}