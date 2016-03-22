#include <cstdio>

const int N = 1e5+10, M = 3 * N;
int n, m, tot;
int Deg0[N], Deg1[N], Last[N], Que[N];
double f[N];

struct Edge{
	int to, next, dis;
	Edge(int X = 0, int Y = 0, int Z = 0){to = X, next = Y, dis = Z;}
} E[M];

void Link(int x, int y, int z){
	E[++ tot] = Edge(y, Last[x], z), Last[x] = tot;
}

void Bfs(){
	Que[1] = n;
	for(int L = 1, R = 1; L <= R; L ++){
		int x = Que[L];
		for(int p = Last[x]; p; p = E[p].next){
			int to = E[p].to;
			f[to] += (f[x] + E[p].dis) / Deg0[to];
			Deg1[to] --;
			if(!Deg1[to]) Que[++ R] = to;
		}
	}
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i ++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		Link(y, x, z);
		Deg0[x] ++, Deg1[x] ++;
	}
	
	Bfs();
	printf("%.2f", f[1]);
	
	return 0;
}