#include <cstdio>

int main(){
	freopen("t.out", "w", stdout);
	
	for(int i = 0; i <= 100; i ++) printf("%d\n", (1024-1) & (-i));
	
	return 0;
}