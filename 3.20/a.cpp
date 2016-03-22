#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 100, MxSta = 300000;
int n, m;
int a[N], f[N][MxSta];
bool b[N];

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	
	int mxSta = (1 << n) - 1;
	memset(f, 120, sizeof(f));
	f[1][0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= mxSta; j ++){
			if(f[i][j] > m) continue;
			int cut = 1;
			for(int k = j; k; k = k >> 1){
				if(k % 2) b[cut] = 1;
				else b[cut] = 0;
				cut ++;
			}
			
			for(int k = 1; k <= n; k ++){
				if(!b[k]) 
					if(f[i][j] + a[k] <= m) 
						f[i][j + (1 << (k - 1))] = min(f[i][j + (1 << (k - 1))], f[i][j] + a[k]);
					else 
						f[i + 1][j + (1 << (k - 1))] = min(f[i + 1][j + (1 << (k - 1))], a[k]);
			}
	}
	
	for(int i = 1; i <= n; i ++)
		if(f[i][mxSta] <= m){
			printf("%d", i);
			break;
		}
	
	return 0;
}