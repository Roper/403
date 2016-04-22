#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e6;
int n, tot;
LL dis[6][N], Last[N], Q[N], a[6], inf;
bool b[N];
struct Edge{
	int to, next, val;
	Edge(int X = 0, int Y = 0, int Z = 0){to = X, next = Y, val = Z;}
} E[N];

void Link(int x, int y, int val){
	E[++ tot] = Edge(y, Last[x], val); Last[x] = tot; // ; --> , ?
	E[++ tot] = Edge(x, Last[y], val); Last[y] = tot;
}

void Spfa(int k, int x){
	memset(b, 0, sizeof(b));
	memset(dis[k], 60, sizeof(dis[k]));
	Q[1] = x; dis[k][x] = 0; inf = dis[k][N-1];
	for(int L = 1, R = 1; L <= R; L ++){
		x = Q[L];
		for(int p = Last[x]; p; p = E[p].next){
			int to = E[p].to;
			if(dis[k][to] > dis[k][x] + E[p].val){
				dis[k][to] = dis[k][x] + E[p].val;
				if(!b[to]) b[to] = 1, Q[++ R] = to;
			}
		}
		b[x] = 0;
	}
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	for(int i = 1; i <= 5; i ++)
		scanf("%d", &a[i]), a[i] += a[i - 1];
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		int x, y;
		scanf("%d %d", &x, &y), Link(x - 1, y, y - x + 1);
	}
	
	for(int i = 1; i < 5; i ++) Spfa(i, a[i]);
	
	LL ans = inf;
	for(int i = 1; i < 4; i ++)
		for(int j = i + 1; j < 5; j ++){
			int k = 1, l;
			for(; k == i || k == j; k ++);
			l = 10 - i - j - k;
			ans = min(ans, dis[i][a[j]] + dis[k][a[l]]);
			if(ans < 0) ans = inf;
		}
		
	if(ans == inf) printf("-1\n");
	else printf("%lld\n", ans);
	
	return 0;
}