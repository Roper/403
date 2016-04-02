#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 1000005,MAXM = 5005;

int G[MAXM],H[MAXM][MAXM],N,M,Mo,A[MAXN],C[MAXM],Fac[MAXM],Least[MAXM];

int gcd(int a,int b)
{
	return b ? gcd(b,a % b) : a;
}

int main()
{
	freopen("kalanchoe.in","r",stdin),freopen("kalanchoe.out","w",stdout);
	scanf("%d%d%d", &N, &M, &Mo);
	int mx = 0;
	for(int i = 1;i <= N;i ++)
		scanf("%d", &A[i]),mx = max(mx,A[i]);
	Fac[0] = 1;
	for(int i = 1;i <= 5000;i ++) Fac[i] = Fac[i - 1] * 1ll * i % Mo;
	int tot = 0;
	for(int i = 1;i <= min(mx,M);i ++)
	{
		Least[++ tot] = M - i + 1;
		for(int j = 1,tmp = i;j <= tot && tmp > 1;j ++)
		{
			int v = gcd(Least[j],tmp);
			tmp /= v,Least[j] /= v;
			if (Least[j] == 1) {swap(Least[j],Least[tot]);tot --;j --;}
		}
		C[i] = 1;
		for(int j = 1;j <= tot;j ++)
			C[i] = C[i] * 1ll * Least[j] % Mo;
	}
	H[0][0] = 1;
	for(int i = 1;i <= mx;i ++)
		for(int j = 1;j <= i;j ++)
			H[i][j] = (H[i - 1][j - 1] + H[i - 1][j] * 1ll * (j - 1) % Mo) % Mo;
	for(int i = 1;i <= mx;i ++)
		for(int j = 1;j <= i;j ++)
			H[i][j] = H[i][j] * 1ll * Fac[j] % Mo;
	int f = 1,s = 0;
	for(int i = 1;i <= N;i ++)
	{
		int cf = 0;
		for(int a = 1;a <= A[i];a ++)
		{
			int bk = G[a];
			if (a > A[i - 1]) bk = 0;
			G[a] = H[A[i]][a] * 1ll * f % Mo * C[a] % Mo;
			if (i > 1) G[a] = (G[a] - H[A[i]][a] * 1ll * bk % Mo + Mo) % Mo;
			cf = (cf + G[a]) % Mo;
		}
		s += A[i];
		f = cf;
	}
	printf("%d\n", f);
}