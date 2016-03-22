#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int TT = 200, N = 30000, MxPrm = 1100000, Dig = 8, Dig10 = 100000000;

int T;
int opp[TT], p[MxPrm+100];
bool b[MxPrm+100];
LL a[TT][N], ans[TT][N];

void Prime(){
	memset(b, 0, sizeof(b));
	for(int i = 2; i <= MxPrm; i ++){
		if(!b[i]) p[++ p[0]] = i;
		for(int j = 1; j <= p[0]; j ++){
			if(i * p[j] > MxPrm) break;
			b[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}

char st[N];
void Read(LL *a){
	scanf("%s\n", st);
	int len = strlen(st);
	a[0] = len / 8 + (len % 8 > 0);
	for(int i = 1; i <= len; i ++){
		int ii = len - i + 1;
		a[ii / 8 + (ii % 8 > 0)] = a[ii / 8 + (ii % 8 > 0)] * 10 + st[i - 1] - '0';
	}
}

bool cmp(int x, int y){
	if(a[x][0] < a[y][0]) return 1;
	if(a[x][0] > a[y][0]) return 0;
	for(int i = a[x][0]; i >= 1; i --)
		if(a[x][i] < a[y][i]) return 1;
		else if(a[x][i] > a[y][i]) return 0;
	return 1;
}

void Mult(LL *a, int num){
	for(int i = a[0]; i >= 1; i --) a[i] = a[i] * p[num];
	int i = 1;
	while(a[i]){a[i + 1] += a[i] / Dig10, a[i] = a[i] % Dig10; i ++;}
	a[0] = i - 1;
}

int main(){
	freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);

	Prime();
	scanf("%d\n", &T);
	for(int i = 1; i <= T; i ++) Read(a[i]);
	for(int i = 1; i <= T; i ++) opp[i] = i;
	sort(opp + 1, opp + 1 + T, cmp);
	
	int num = 0;
	a[T + 1][0] = a[T + 1][1] = 1;
	for(int i = 1; i <= T; i ++){
		while(cmp(T + 1, opp[i])){ 
			for(int j = 0; j <= a[T + 1][0]; j ++)
				a[T + 2][j] = a[T + 1][j];
			num ++; Mult(a[T + 1], num);
		}
		for(int j = 0; j <= a[T + 2][0]; j ++)
			ans[opp[i]][j] = a[T + 2][j];
	}

	for(int i = 1; i <= T; i ++){
		printf("%lld", ans[i][ans[i][0]]);
		for(int j = ans[i][0] - 1; j >= 1; j --){
			int t = Dig10 / 10;
			while(t > ans[i][j]) printf("0"), t /= 10;
			printf("%lld", ans[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}