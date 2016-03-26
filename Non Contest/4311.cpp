#include <cstdio>
typedef long long LL;

const LL N = 4*1e5, M = 2*N;
LL n0, n1;
LL tot[2], Last[2][N];
LL ans[2], f[2][N], num[2][N], g[2][N];

struct Edge{
	int to, next;
	Edge(int X = 0, int Y = 0){to = X, next = Y;}
} E[2][M];

void Link(int k, int x, int y){
	E[k][++ tot[k]] = Edge(y, Last[k][x]); Last[k][x] = tot[k];
}

void Dfs(int k, int x, int last){
	for(int p = Last[k][x]; p; p = E[k][p].next){
		int to = E[k][p].to;
		if(to == last) continue;
		Dfs(k, to, x);
		f[k][x] += f[k][to] + num[k][to];
		g[k][x] += g[k][to];
		num[k][x] += num[k][to];
	}
	num[k][x] ++;
	for(int p = Last[k][x]; p; p = E[k][p].next){
		int to = E[k][p].to;
		if(to == last) continue;
		g[k][x] += (f[k][to] + num[k][to]) * (num[k][x] - num[k][to]);
	}
}

void Findroot(int k, int x, int last){
	if(f[k][x] < ans[k]) ans[k] = f[k][x];
	for(int p = Last[k][x]; p; p = E[k][p].next){
		int to = E[k][p].to;
		if(to == last) continue;
		LL t0 = f[k][to], t1 = num[k][to];
		f[k][x] -= (t0 + t1), num[k][x] -= t1; 
		f[k][to] += (f[k][x] + num[k][x]), num[k][to] += num[k][x];
		Findroot(k, to, x);
		f[k][x] += (t0 + t1), num[k][x] += t1;
		f[k][to] = t0, num[k][to] = t1;
	}
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n0, &n1);
	for(int i = 1; i <= n0 - 1; i ++){
		int x, y; scanf("%d %d", &x, &y); 
		Link(0, x, y), Link(0, y, x);
	}
	for(int i = 1; i <= n1 - 1; i ++){
		int x, y; scanf("%d %d", &x, &y);
		Link(1, x, y), Link(1, y, x);
	}
	
	Dfs(0, 1, 0), Dfs(1, 1, 0);
	ans[0] = ans[1] = N*1LL*N;
	Findroot(0, 1, 0); Findroot(1, 1, 0);
	printf("%lld", g[0][1] + g[1][1] + ans[0] * num[1][1] + ans[1] * num[0][1] + num[0][1] * num[1][1]);
	
	return 0;
}