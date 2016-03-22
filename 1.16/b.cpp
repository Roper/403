#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 110, maxm = 20, maxstt = 100;
int n, m;
int old[maxm], now[maxm], f[maxn][maxstt][maxstt], st[maxn][100], sum[maxn][100];
char a[maxn][maxm];

void Work(){
	scanf("%d %d\n", &n, &m);
	int limstt = 1;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++) scanf("%c", &a[i][j]);
		scanf("\n");
	}
	for(int j = 1; j <= m; j ++) limstt = limstt * 3;
	limstt --;
	for(int i = 1; i <= n; i ++)
		for(int stt = 0; stt < 1 << m; stt ++){
			bool b = 1; int Sum = 0;
			for(int j = 1; j <= m; j ++){
				if(a[i][j] == 'H' && (stt & (1 << (j - 1)))){b = 0; break;}
				if(stt & (1 << (j - 1))) Sum ++;
			}
			if(b && ((stt >> 1) & stt) == 0 && ((stt >> 2) & stt) == 0){
				st[i][++ st[i][0]] = stt;
				sum[i][st[i][0]] = Sum;
			}
		}
	
	for(int i = 1; i <= st[1][0]; i ++) f[1][i][0] = sum[1][i];
	for(int i = 1; i <= st[1][0]; i ++)
		for(int j = 1; j <= st[2][0]; j ++) if((st[1][i] & st[2][j]) == 0) f[2][j][i] = f[1][i][0] + sum[2][j];
	for(int row = 3; row <= n; row ++)
		for(int i = 1; i <= st[row][0]; i ++)
			for(int j = 1; j <= st[row - 1][0]; j ++) if((st[row][i] & st[row - 1][j]) == 0)
				for(int k = 1; k <= st[row - 2][0]; k ++) 
					if((st[row][i] & st[row - 2][k]) == 0 && (st[row - 1][j] & st[row - 2][k]) == 0)
						f[row][i][j] = max(f[row][i][j], f[row - 1][j][k] + sum[row][i]);
	
	int ans = 0;
	for(int i = 1; i <= st[n][0]; i ++) 
		for(int j = 1; j <= st[n - 1][0]; j ++) ans = max(ans, f[n][i][j]);
	
	printf("%d", ans);
}

int main(){
	freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
	
	Work();
	
	return 0;
}