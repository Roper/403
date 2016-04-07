#include <cstdio>
#include <cstring>
#include <algorithm>
#define Maxn 3433333
#define N 100000
using namespace std;

int n, ans[N], a[N], b[N], c[2 * Maxn + 1];

struct node {
	int x, y, d;
} q[Maxn];

bool cmpx(int a, int b) {
	return q[a].x < q[b].x;
}

bool cmpy(int a, int b) {
	return q[a].y < q[b].y;
}

void add(int p, int v) {
	while (p < 2 * Maxn) {
		c[p] += v;
		p += p & -p;
	}
}

int query(int x) {
	int ans = 0;
	if (x > 2 * Maxn) x = 2 * Maxn;
	while (x > 0) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

void solve(int l1, int l2) {
	sort(a + 1, a + l1 + 1, cmpx);
	sort(b + 1, b + l2 + 1, cmpx);
	int now = 1;
	for (int i = 1; i <= l2; i++) {
		while (q[a[now]].x < q[b[i]].x && now <= l1) add(q[a[now]].x + q[a[now]].y, 1), now ++;
		ans[b[i]] -= query(q[b[i]].x + q[b[i]].y + q[b[i]].d) - query(q[b[i]].x + q[b[i]].y - 1);
	}
	for (int i = 1; i < now; i++) add(q[a[i]].x + q[a[i]].y, -1);
	sort(a + 1, a + l1 + 1, cmpy);
	sort(b + 1, b + l2 + 1, cmpy);
	now = 1;
	for (int i = 1; i <= l2; i++) {
		while (q[a[now]].y < q[b[i]].y && now <= l1) add(q[a[now]].x + q[a[now]].y, 1), now ++;
		ans[b[i]] -= query(q[b[i]].x + q[b[i]].y + q[b[i]].d) - query(q[b[i]].x + q[b[i]].y - 1);
	}
	for (int i = 1; i < now; i++) add(q[a[i]].x + q[a[i]].y, -1);
}

void divide(int l, int r) {
	int mid = (l + r) >> 1, len1 = 0, len2 = 0;
	for (int i = l; i <= mid; i++) if (!q[i].d) a[++ len1] = i;
	for (int i = mid + 1; i <= r; i++) if (q[i].d) b[++ len2] = i;
	if (len1 && len2) solve(len1, len2);
	if (len1 && l != mid) divide(l, mid);
	if (len2 && mid + 1 != r) divide(mid + 1, r);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &q[i].x, &q[i].y, &q[i].d);
		if (!q[i].d) add(q[i].x + q[i].y, 1);
		else ans[i] = query(q[i].x + q[i].y + q[i].d) - query(q[i].x + q[i].y - 1);
	}
	for (int i = 1; i <= n; i++) if (!q[i].d) add(q[i].x + q[i].y, -1);
	if (n != 1) divide(1, n);
	for (int i = 1; i <= n; i++) if (q[i].d) printf("%d\n", ans[i]);
	return 0;
}