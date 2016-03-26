#include <cstdio>

const int N = 200;
int n, m;
int a[N][2];

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i ++){
		int t; scanf("%d", &t);
		if(t < 3){
			a[i][0] = t;
			scanf("%d", &a[i][1]); 
		} else{
			for(int j = i, num = 0; j >= 1 && num < 20; j --)if(a[j][1]){
				bool b = 1;
				for(int k = 1; k <= i; k ++)
					if(a[k][1] == a[j][1] && (a[k][0] == 1 || (k > j))){b = 0; break;}
				if(b){
					printf("%d ", a[j][1]);
					num ++;
				}
			}
			printf("\n");
		}
	}
	
	return 0;
}