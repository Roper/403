#include <cstdio>

const int MAXN = 55, MAXK = MAXN, mo = 9397;
int n, k;
int f[MAXN][MAXK];

void Work(){
	scanf("%d %d", &n, &k);
	f[2][0] = 1;
	f[3][1] = 1;
	for(int len = 4; len <= n; len ++){
		for(int kk = 0; kk <= k; kk ++)
			for(int i = 2; i <= len - 1; i ++){
				int l1 = n - len + 1, l2 = i - 1, l3 = len - i, iso;
				if(l1 == l2 || l1 == l3 || l2 == l3) iso = 1;
				else iso = 0;
				if(iso && !kk) break;
				for(int j = 0; j <= kk && kk - j - iso >= 0; j ++)
					f[len][kk] = (f[len][kk] + f[i][j] * f[len - i + 1][kk - j - iso]) % mo;
			}
	}
	printf("%d", f[n][k]);
}

int main(){
	freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
	
	Work();
	
	return 0;
}