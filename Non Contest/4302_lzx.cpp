#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;
int nt[5];
int n,tot;
int to[N * 2],next[N * 2],g[N * 5];
int a[N * 5],p[N * 5];
LL d[5][N * 5],dis[N * 2];

void add(int u,int v,int D)
{
	to[++ tot] = v;
	next[tot] = g[u];
	dis[tot] = LL(D);
	g[u] = tot;
}

void init()
{
	for (int i = 1;i <= 5;++ i) 
	{
		scanf("%d",&nt[i]);
		nt[i] += nt[i - 1];
	}
	scanf("%d",&n);
	for (int i = 1;i <= n;++ i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v + 1,v - u + 1);
		add(v + 1,u,v - u + 1);
	}
}

void spfa(int t,int u)
{
	memset(d[t],60,sizeof(d[t]));
	d[t][u] = 0;
	memset(p,0,sizeof(p));
	p[u] = 1;
	int l = 0,r = 1;
	a[1] = u;
	while (l != r)
	{
		l = l % (5 * N) + 1;
		u = a[l];
		for (int i = g[u];i;i = next[i])
		{
			int v = to[i];
			if (d[t][u] + dis[i] < d[t][v])
			{
				d[t][v] = d[t][u] + dis[i];
				if (p[v]) continue;
				p[v] = true;
				r = r % (5 * N) + 1;
				a[r] = v;
			}
		}
		p[u] = 0;
	}
}

void solve()
{
	for (int i = 1;i < 5;++ i)
		spfa(i,nt[i] + 1);
	LL Inf = n * 5ll * N,ans = Inf;
	for (int i = 1;i <= 4;++ i)
		for (int j = i + 1;j <= 4;++ j)
		{
			LL cur = d[i][nt[j] + 1];
			int u,v;
			for (u = 1;u <= 4;++ u) if (u != i && u != j) break;
			v = 10 - u - i - j;
			cur += d[u][nt[v] + 1];
			ans = min(ans,cur);
		}
	if (ans == Inf)
		puts("-1");
	else 
		printf("%lld",ans);
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	init();
	solve();
}