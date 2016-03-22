#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int n, tot, dfn;
int Last[N], tr[N * 8], ans[N];
struct Edge{
	int to, next;
	Edge(int X = 0, int Y = 0){to = X, next = Y;}
} E[N];
struct Point{
	int x, dfn, R, num;
} a[N];

void Link(int x, int y){
	E[++ tot] = Edge(y, Last[x]); Last[x] = tot;
}

void Dfs(int x){
	a[x].dfn = ++ dfn;
	for(int p = Last[x]; p; p = E[p].next) Dfs(E[p].to);
	a[x].R = dfn;
}

bool cmp(Point A, Point B){
	if(A.x != B.x) return A.x < B.x;
	else return A.dfn > B.dfn;
}

int Ask(int s, int L, int R, int x, int y){
	if(x <= L && R <= y) return tr[s];
	int mid = (L + R) / 2;
	if(y <= mid) return Ask(s * 2, L, mid, x, y);
	if(x > mid) return Ask(s * 2 + 1, mid + 1, R, x, y);
	return max(Ask(s * 2, L, mid, x, y), Ask(s * 2 + 1, mid + 1, R, x, y));
}

void Add(int s, int L, int R, int x, int y){
	if(L == R){tr[s] = ans[x]; return;}
	int mid = (L + R) / 2;
	if(y <= mid) Add(s * 2, L, mid, x, y);
	else Add(s * 2 + 1, mid + 1, R, x, y);
	tr[s] = max(tr[s * 2], tr[s * 2 + 1]);
}

void Work(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		int x;
		scanf("%d", &x);
		Link(x, i);
	}
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i].x);
		a[i].num = i;
	}

	Dfs(1);
	sort(a + 1, a + 1 + n, cmp);

	for(int i = 1; i <= n; i ++){
		ans[a[i].num] = Ask(1, 1, n, a[i].dfn, a[i].R) + 1;
		Add(1, 1, n, a[i].num, a[i].dfn);
	}

	for(int i = 1; i <= n; i ++) printf("%d ", ans[i]);
}

int main(){
	freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);

	Work();

	return 0;
}
