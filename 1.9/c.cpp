#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 110, MAXN2 = MAXN * 2;
int n;
int a[MAXN2], f[MAXN2][MAXN2];

void Work(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for(int i = n + 1; i <= 2 * n; i ++) a[i] = a[i - n];
	for(int len = 1; len <= n; len ++)
		for(int i = 1; i <= 2 * n - len + 1; i ++){
			int j = i + len - 1;
			for(int k = i; k <= j - 1; k ++) 
				f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
		}
	int ans = 0;
	for(int i = 1; i <= n; i ++) ans = max(ans, f[i][i + n - 1]);
	printf("%lld", ans);
}

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	Work();
	
	return 0;
}