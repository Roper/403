#include <cstdio>

const int ch2[6][2] = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
const int ch3[4][3] = {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}};
long long n, m;
long long a[5], sum1[4][36], sum2[6][36][36], sum3[4][36][36][36], sum4[36][36][36][36], sum[5];
char st[5];

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%s", st);
		for(int j = 0; j < 4; j ++)
			if(st[j] >= '0' && st[j] <= '9') a[j + 1] = st[j] - '0';
			else a[j + 1] = st[j] - 'a' + 10;
		
		for(int j = 0; j < 4; j ++)
			sum1[j][a[j + 1]] ++;
		for(int j = 0; j < 6; j ++){
			int x = a[ch2[j][0]], y = a[ch2[j][1]];
			sum2[j][x][y] ++;
		}
		for(int j = 0; j < 4; j ++){
			int x = a[ch3[j][0]], y = a[ch3[j][1]], z = a[ch3[j][2]];
			sum3[j][x][y][z] ++;
		}
		sum4[a[1]][a[2]][a[3]][a[4]] ++;
	}
	
	for(int i = 0; i < 4; i ++)
		for(int j = 0; j < 36; j ++){
			if(sum1[i][j]*(sum1[i][j] - 1) / 2 > 0){
				int tttt = 1;
				tttt = 2;
			}
			sum[1] += sum1[i][j]*(sum1[i][j] - 1) / 2;
		}
	for(int i = 0; i < 6; i ++)
		for(int j = 0; j < 36; j ++)
		for(int k = 0; k < 36; k ++)
			sum[2] += sum2[i][j][k]*(sum2[i][j][k] - 1) / 2;
	for(int i = 0; i < 4; i ++)
		for(int j = 0; j < 36; j ++)
		for(int k = 0; k < 36; k ++)
		for(int l = 0; l < 36; l ++)
			sum[3] += sum3[i][j][k][l]*(sum3[i][j][k][l] - 1) / 2;
	for(int i = 0; i < 36; i ++)
		for(int j = 0; j < 36; j ++)
		for(int k = 0; k < 36; k ++)
		for(int l = 0; l < 36; l ++) 
			sum[4] += sum4[i][j][k][l]*(sum4[i][j][k][l] - 1) / 2;
		
	if(m == 3) printf("%lld", sum[1] - 2*sum[2] + 3*sum[3] - 4*sum[4]);
	else if(m == 2) printf("%lld", sum[2] - 3*sum[3] + 6*sum[4]);
	else if(m == 1) printf("%lld", sum[3] - 4*sum[4]);
	else printf("%lld", n*(n - 1)/2 - (sum[1] - sum[2] + sum[3] - 2*sum[4]));
	
	return 0;
}