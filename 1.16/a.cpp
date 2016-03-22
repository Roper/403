#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 20, maxstt = 300000;
int n;
int a[maxn][maxn], f[maxstt];

void Work(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) scanf("%d", &a[i][j]);
	
	for(int stt = 1; stt <= maxstt; stt ++)
		for(int i = 1; i <= n - 1; i ++) if((1 << (i - 1)) & stt)
			for(int j = i + 1; j <= n; j ++) if((1 << (j - 1)) & stt){
				int old = stt - (1 << (i - 1)) - (1 << (j - 1));
				if(f[stt] == 0) f[stt] = f[old] + a[i][j];
				else f[stt] = min(f[stt], f[old] + a[i][j]);
			}
	
	printf("%d", f[(1 << n) - 1]);
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	Work();
	
	return 0;
}