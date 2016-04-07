#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5, XY = 1e7;
int n;
int a[N], b[N], ans[N], tr[XY];
struct Problem{
	int x, y, d;
} q[N];

void Add(int x, int pls){
	while(x <= XY)
		tr[x] += pls, x += x & -x;
}
int Ask(int x){
	int ret = 0;
	if(x > XY) x = XY;
	while(x > 0)
		ret += tr[x], x -= x & -x;
	return ret;
}

bool cmpx(int A, int B){return q[A].x < q[B].x;}
bool cmpy(int A, int B){return q[A].y < q[B].y;}
void Sub(int len1, int len2){
	sort(a + 1, a + 1 + len1, cmpx);
	sort(b + 1, b + 1 + len2, cmpx);
	int tot = 1;
	for(int i = 1; i <= len2; i ++){
		while(tot <= len1 && q[a[tot]].x < q[b[i]].x){
			Add(q[a[tot]].x + q[a[tot]].y, 1);
			tot ++;
		}
		ans[b[i]] -= Ask(q[b[i]].x + q[b[i]].y + q[b[i]].d) - Ask(q[b[i]].x + q[b[i]].y - 1);
	}
	for(int i = 1; i <= tot - 1; i ++) Add(q[a[i]].x + q[a[i]].y, -1);
	
	sort(a + 1, a + 1 + len1, cmpy);
	sort(b + 1, b + 1 + len2, cmpy);
	tot = 1;
	for(int i = 1; i <= len2; i ++){
		while(tot <= len1 && q[a[tot]].y < q[b[i]].y){
			Add(q[a[tot]].x + q[a[tot]].y, 1);
			tot ++;
		}
		ans[b[i]] -= Ask(q[b[i]].x + q[b[i]].y + q[b[i]].d) - Ask(q[b[i]].x + q[b[i]].y - 1);
	}
	for(int i = 1; i <= tot - 1; i ++) Add(q[a[i]].x + q[a[i]].y, -1);
}
void Half(int L, int R){
	int mid = (L + R) >> 1, len1 = 0, len2 = 0;
	for(int i = L; i <= mid; i ++) if(!q[i].d) a[++ len1] = i;
	for(int i = mid + 1; i <= R; i ++) if(q[i].d) b[++ len2] = i;
	if(len1 && len2) Sub(len1, len2);
	if(len1 && L != mid) Half(L, mid);
	if(len2 && R != mid + 1) Half(mid + 1, R);
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d %d %d", &q[i].x, &q[i].y, &q[i].d);
		if(!q[i].d) Add(q[i].x + q[i].y, 1);
		else ans[i] = Ask(q[i].x + q[i].y + q[i].d) - Ask(q[i].x + q[i].y - 1);
	}
	
	for(int i = 1; i <= n; i ++)
		if(!q[i].d) Add(q[i].x + q[i].y, -1);
	Half(1, n);
	
	for(int i = 1; i <= n; i ++) if(q[i].d) printf("%d\n", ans[i]);
	
	return 0;
}