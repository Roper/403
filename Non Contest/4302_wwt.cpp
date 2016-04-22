#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

const int MAXN = 500005;

typedef long long LL;
typedef pair<LL,int> P;

priority_queue<P,vector<P>,greater<P> >Q;
LL D[5][MAXN],Ans;
bool Walk[MAXN],Match[5];
int To[MAXN],Next[MAXN],Cost[MAXN],Final[MAXN];
int V[5],N,tot;

void Link(int u,int v,int c)
{
	To[++ tot] = v,Cost[tot] = c,Next[tot] = Final[u],Final[u] = tot;
}

void Spfa(int s)
{
	int S = V[s - 1] + 1;
	for(int i = 1;i <= V[4] + 1;i ++)
		D[s][i] = (1ll << 60);
	D[s][S] = 0;
	Q.push(P(0,S));
	while (!Q.empty())
	{
		P cur = Q.top();
		Q.pop();
		if (D[s][cur.second] != cur.first) continue;
		int u = cur.second;
		for(int i = Final[u];i;i = Next[i])
			if (D[s][u] + Cost[i] < D[s][To[i]])
			{
				D[s][To[i]] = D[s][u] + Cost[i];
				Q.push(P(D[s][To[i]],To[i]));
			}
	}
}

void Dfs(int Now,LL Cur)
{
	if (Cur >= Ans) return;
	if (Now == 5) Ans = min(Ans,Cur); else
	{
		if (Match[Now]) {Dfs(Now + 1,Cur);return;}
		//Divide this point itself
		Match[Now] = 1;
		Dfs(Now + 1,Cur + D[Now][V[4] + 1]);
		Match[Now] = 0;
		for(int i = 1;i < 5;i ++)
			if (i != Now && !Match[i])
			{
				Match[i] = 1;
				Dfs(Now + 1,Cur + D[Now][V[i - 1] + 1]);
				Match[i] = 0;
			}
	}
}

int main()
{
	freopen("card.in","r",stdin),freopen("card.out","w",stdout);
	scanf("%d%d%d%d%d", &V[0], &V[1], &V[2], &V[3], &V[4]);
	V[1] += V[0],V[2] += V[1],V[3] += V[2],V[4] += V[3];
	scanf("%d", &N);
	for(int i = 1;i <= N;i ++)
	{
		int s,t;
		scanf("%d%d", &s, &t);
		t ++;
		Link(s,t,t - s),Link(t,s,t - s);
	}
	for(int i = 1;i < 5;i ++)
		Spfa(i);
	Ans = (1ll << 60);
	Dfs(1,0);
	if (Ans == (1ll << 60)) printf("-1\n"); else
		printf("%lld\n", Ans);
	return 0;
}	
