#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e6+100, Ai = 7*1e3;
int n, m, mo;
int a[N], mul[Ai], son[Ai], W[Ai][Ai], C[Ai], flr[Ai];

int Gcd(int x, int y){
	return x ? Gcd(y % x, x) : y;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d %d", &n, &m, &mo);
	int mx = 0;
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]), mx = max(mx, a[i]);
	
	int mn = min(m, mx); mul[1] = 1;
	for(int i = 2; i <= mn; i ++)
		mul[i] = mul[i-1] *1LL* i % mo;
	
	int tot = 0;
	for(int i = 1; i <= mn; i ++){
		son[++ tot] = m - i + 1;
		for(int j = 1, mom = i; mom > 1; j ++){
			int t = Gcd(mom, son[j]);
			mom /= t, son[j] /= t;
			if(son[j] == 1){swap(son[j], son[tot]); tot --; j --;}
		}
		C[i] = 1;
		for(int j = 1; j <= tot; j ++) C[i] = C[i] *1LL* son[j] % mo;
	}
	
	W[0][0] = 1;
	for(int i = 1; i <= mx; i ++)
		for(int j = 1; j <= i; j ++)
			W[i][j] = (W[i - 1][j - 1] + W[i - 1][j] *1LL* (j - 1) % mo) % mo;
	for(int i = 1; i <= mx; i ++)
		for(int j = 1; j <= i; j ++)
			W[i][j] = W[i][j] *1LL* mul[j] % mo;
			
	int lans = 1, ans;
	for(int i = 1; i <= n; i ++){
		ans = 0;
		for(int j = 1; j <= a[i]; j ++){
			int last = flr[j];
			if(a[i - 1] < j) last = 0;
			flr[j] = W[a[i]][j] *1LL* lans % mo * C[j] % mo;
			if(i > 1) flr[j] = (flr[j] - W[a[i]][j] *1LL* last % mo + mo) % mo;
			ans = (ans*1LL + flr[j]) % mo;
		}
		lans = ans;
	}
	printf("%d", ans);
	
	return 0;
}