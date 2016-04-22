#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long i64;

const int N = 1e3 + 10;
const i64 INF = LONG_LONG_MAX / 3;

int n, v[N], x[N], y[N], data[N];

void Relabel(int *x) {
	for (int i = 1; i <= n; ++ i) data[i] = x[i];
	sort(data + 1, data + n + 1);
	int m = unique(data + 1, data + n + 1) - data - 1;
	for (int i = 1; i <= n; ++ i) x[i] = lower_bound(data + 1, data + m + 1, x[i]) - data;
	for (int i = 1; i <= n; ++ i) x[i] = m - x[i] + 1;
}

i64 sum[N][N], cnt[N][N];

void Init() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf("%d", &v[i]);
	for (int i = 1; i <= n; ++ i) scanf("%d%d", &x[i], &y[i]);
	Relabel(x), Relabel(y);
	for (int i = 1; i <= n; ++ i)
		++ cnt[x[i]][y[i]], sum[x[i]][y[i]] += v[i];
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j) {
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			cnt[i][j] += cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1];
		}
}

i64 f[N][N], g[N][N], a[N], b[N];

void Solve() {
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j) {
			if (cnt[i][j] == cnt[i - 1][j]) f[i][j] = f[i - 1][j];
			else f[i][j] = a[j] + sum[i][j];

			if (cnt[i][j] == cnt[i][j - 1])	g[i][j] = g[i][j - 1];
			else g[i][j] = b[i];

			a[j] = max(a[j], g[i][j] - sum[i][j]);
			b[i] = min(b[i], f[i][j]);
		}
	printf("%lld\n", f[n][n]);
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);

	Init();
	Solve();

	return 0;
}