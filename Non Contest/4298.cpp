#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e6;
int n, m;
LL tr[8*N][4];

void Pass(int s, int len){
	if(len != 1){
		tr[s*2][0] = (len+1)/2*tr[s][3]; tr[s*2][1] = tr[s*2][2] = tr[s*2][3] = tr[s][3];
		tr[s*2+1][0] = len/2*tr[s][3]; tr[s*2+1][1] = tr[s*2+1][2] = tr[s*2+1][3] = tr[s][3];
	}
	tr[s][3] = 0;
}

LL AAA(int s, int L, int R, int x, int y, LL z){ //0=sum 1=max 2=min 3=to pass
	LL mid = (L+R) >> 1, ret = 0;
	if(tr[s][2] > z) return 0;
	if(x <= L && R <= y && tr[s][1] <= z){
		ret = (R-L+1)*z - tr[s][0];
		tr[s][0] = (R-L+1)*z, tr[s][1] = tr[s][2] = tr[s][3] = z;
		return ret;
	}
	if(tr[s][3]) Pass(s, R-L+1);
	if(y <= mid) ret = AAA(s*2, L, mid, x, y, z);
	else if(x > mid) ret = AAA(s*2+1, mid+1, R, x, y, z);
	else ret = AAA(s*2, L, mid, x, y, z) + AAA(s*2+1, mid+1, R, x, y, z);
	tr[s][0] = tr[s*2][0] + tr[s*2+1][0],
	tr[s][1] = max(tr[s*2][1], tr[s*2+1][1]), 
	tr[s][2] = min(tr[s*2][2], tr[s*2+1][2]);
	return ret;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	
	for(int i = 1; i <= n; i ++)
		AAA(1, 1, n, i, i, i);
	
	for(int i = 1; i <= m; i ++){
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%lld\n", AAA(1, 1, n, x, y, y));
	}
	
	return 0;
}