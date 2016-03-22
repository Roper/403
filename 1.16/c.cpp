#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 15, maxstt = 10000;
int n, m, T;
long long a[maxn], f[maxstt][maxn][maxn][2];
bool b[maxn][maxn];

void Work(){
	memset(f, 0, sizeof(f));
	memset(b, 0, sizeof(b));
	memset(a, 0, sizeof(a));
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	if(n == 1){printf("%d 1\n", a[1]); return;}
	for(int i = 1; i <= m; i ++){
		int x, y;
		scanf("%d %d", &x, &y);
		b[x][y] = b[y][x] = 1;
	}
	int limstt = (1 << n) - 1;
	for(int i = 1; i <= n; i ++){
		int ii = 1 << (i - 1);
		for(int j = 1; j <= n; j ++) if(i != j && b[i][j]){
			int jj = 1 << (j - 1);
			f[ii + jj][i][j][0] = a[i] + a[j] + a[i] * a[j] * b[i][j];
			f[ii + jj][i][j][1] = 1;
		}
	}
	
	for(int stt = 1; stt <= limstt; stt ++)
		for(int i = 1; i <= n; i ++){
			int ii = 1 << (i - 1);
			if(!(stt & ii)) continue;
			for(int j = 1; j <= n; j ++)if(b[i][j]){
				int jj = 1 << (j - 1);
				if(!(i != j && (stt & jj))) continue;
				for(int k = 1; k <= n; k ++)if(b[j][k]){
					int kk = 1 << (k - 1);
					if(!((stt & kk) && (i != k) && (j != k))) continue;
					if(!f[stt - kk][i][j][1]) continue;
					int F = f[stt - kk][i][j][0] + a[k] + a[k] * a[j] * b[k][j] + a[i] * a[j] * a[k] * b[k][i];
					if(!(k != i && k != j && (stt & kk))) continue;
					if(F == f[stt][j][k][0]) f[stt][j][k][1] += f[stt - kk][i][j][1];
					else if(F > f[stt][j][k][0]) f[stt][j][k][0] = F, f[stt][j][k][1] = f[stt - kk][i][j][1];
					if(f[stt][j][k][0] == 2178 && f[stt][j][k][1] == 0){
						kk = 1;
					}
				}
			}
		}
		
	long long ans[2];
	ans[0] = ans[1] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++){
			if(f[limstt][i][j][0] == ans[0]) ans[1] += f[limstt][i][j][1];
			else if(f[limstt][i][j][0] > ans[0]) ans[0] = f[limstt][i][j][0], ans[1] = f[limstt][i][j][1];
		}
	if(ans[0] == 0) printf("0 0\n");
	else printf("%lld %lld\n", ans[0], ans[1] / 2);
}

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	scanf("%d", &T);
	while(T --) Work();
	
	return 0;
}