#include <cstdio>

const int N = 1e4+100, M = 2*1e4;
int n, m, q;
int tot[3], Last[3][N], d[N], fa[N];
bool b[N];

struct Edge{
	int to, next, dis;
	Edge(int X = 0, int Y = 0, int Z = 0){
		to = X, next = Y, dis = Z;
	}
} E[3][2*M];

void Link(int k, int x, int y, int z){
	E[k][++ tot[k]] = Edge(y, Last[k][x], z); Last[k][x] = tot[k];
}

void Distance(int x, int last, int dis){
	d[x] = dis;
	for(int p = Last[0][x]; p; p = E[0][p].next){
		int to = E[0][p].to;
		if(to == last) continue;
		Distance(to, x, dis + E[0][p].dis);
	}
}

int Getfa(int x){
	if(fa[x] != x) fa[x] = Getfa(fa[x]);
	return fa[x];
}

void Tarjan(int x){
	b[x] = 1;
	for(int p = Last[0][x]; p; p = E[0][p].next){
		int to = E[0][p].to;
		if(b[to]) continue;
		Tarjan(to);
		fa[to] = x;
	}
	
	for(int p = Last[1][x]; p; p = E[1][p].next){
		int to = E[1][p].to;
		if(!b[to]) continue;
		fa[to] = Getfa(to);
		E[1][p].dis = E[1][p ^ 1].dis = d[to] + d[x] - d[fa[to]] * 2;
	}
}

void WorkA(){
	Distance(1, 0, 0);
	for(int i = 1; i <= n; i ++) fa[i] = i;
	Tarjan(1);
	
	for(int i = 1; i <= tot[1] / 2; i ++) printf("%d\n", E[1][i*2].dis);
}

int main(){
	freopen("b.in" , "r", stdin), freopen("b.out", "w", stdout);
	
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= m; i ++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		Link(0, x, y, z); Link(0, y, x, z);
	}
	
	tot[1] = 1;
	for(int i = 1; i <= q; i ++){
		int x, y;
		scanf("%d %d", &x, &y);
		Link(1, x, y, 0), Link(1, y, x, 0);
	}
	if(m == n - 1) WorkA();
	
	return 0;
}