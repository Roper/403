#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 2*1e3;
LL n;
LL v[N], x[N], y[N], cnt[N][N], val[N][N], f[N][N], g[N][N], a[N], b[N], aa[N];

void Relabel(LL *a){
	for(int i = 1; i <= n; i ++) aa[i] = a[i];
	sort(aa + 1, aa + 1 + n);
	int m = unique(aa + 1, aa + 1 + n) - 1 - aa;
	for(int i = 1; i <= n; i ++)
		a[i] = lower_bound(aa + 1, aa + 1 + m, a[i]) - aa;
	for(int i = 1; i <= n; i ++) a[i] = m - a[i] + 1;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%lld", &v[i]);
	for(int i = 1; i <= n; i ++) scanf("%lld %lld", &x[i], &y[i]);
	Relabel(x), Relabel(y);
	
	for(int i = 1; i <= n; i ++) 
		cnt[x[i]][y[i]] ++, val[x[i]][y[i]] += v[i];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++){
			cnt[i][j] += cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
			val[i][j] += val[i-1][j] + val[i][j-1] - val[i-1][j-1];
		}
	
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++){
			if(cnt[i][j] == cnt[i-1][j]) f[i][j] = f[i-1][j];
			else f[i][j] = b[j] + val[i][j];
			
			if(cnt[i][j] == cnt[i][j-1]) g[i][j] = g[i][j-1];
			else g[i][j] = a[i];
			
			a[i] = min(a[i], f[i][j]);
			b[j] = max(b[j], g[i][j] - val[i][j]);
		}
	printf("%lld\n", f[n][n]);
	
	return 0;
}