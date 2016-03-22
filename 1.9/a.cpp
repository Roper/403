#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 55, MAXN2 = MAXN * 2, inf = 2147483647;
int n;
int f[MAXN2][MAXN2], g[MAXN2][MAXN2], a[MAXN2];
bool b[MAXN2];

int Operate(int x, int y, int op){
	if(op == 1) return x * y;
	else return x + y;
}

void Work(){
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++){
		char c; int x;
		scanf("%c %d ", &c, &x);
		if(c == 'x') a[i - 1] = 1;
		else a[i - 1] = 0;
		f[i][i] = g[i][i] = x;
	}
	a[n] = a[0]; a[0] = 0;
	for(int i = n + 1; i <= 2 * n; i ++){
		a[i] = a[i - n];
		f[i][i] = g[i][i] = f[i - n][i - n];
	}
	for(int len = 2; len <= n; len ++)
		for(int i = 1; i <= 2 * n - len + 1; i ++){
			int j = i + len - 1;
			f[i][j] = Operate(f[i][i], f[i + 1][j], a[i]);
			f[i][j] = Operate(f[i][i], f[i + 1][j], a[i]);
			f[i][j] = Operate(g[i][i], g[i + 1][j], a[i]);
			f[i][j] = Operate(f[i][i], f[i + 1][j], a[i]);
			g[i][j] = Operate(f[i][i], f[i + 1][j], a[i]);
			g[i][j] = Operate(f[i][i], g[i + 1][j], a[i]);
			g[i][j] = Operate(g[i][i], f[i + 1][j], a[i]);
			g[i][j] = Operate(g[i][i], g[i + 1][j], a[i]);
			for(int k = i + 1; k <= j - 1; k ++){
				f[i][j] = max(f[i][j], Operate(f[i][k], f[k + 1][j], a[k]));
				f[i][j] = max(f[i][j], Operate(g[i][k], g[k + 1][j], a[k]));
				f[i][j] = max(f[i][j], Operate(f[i][k], g[k + 1][j], a[k]));
				f[i][j] = max(f[i][j], Operate(g[i][k], f[k + 1][j], a[k]));
				g[i][j] = min(g[i][j], Operate(f[i][k], f[k + 1][j], a[k]));
				g[i][j] = min(g[i][j], Operate(f[i][k], g[k + 1][j], a[k]));
				g[i][j] = min(g[i][j], Operate(g[i][k], f[k + 1][j], a[k]));
				g[i][j] = min(g[i][j], Operate(g[i][k], g[k + 1][j], a[k]));
			}
		}
	int ans = -inf;
	for(int i = 1; i <= n; i ++){
		if(f[i][i + n - 1] == ans) b[i] = 1;
		else if(f[i][i + n - 1] > ans){
			memset(b, 0, sizeof(b));
			b[i] = 1;
		}
		ans = max(ans, f[i][i + n - 1]);
	}
	printf("%d\n", ans);
	for(int i = 1; i <= n; i ++)
		if(b[i]) printf("%d ", i);
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	Work();
	
	return 0;
}