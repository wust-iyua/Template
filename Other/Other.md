###### 枚举子集
枚举状压集合S的子集
```cpp
// S为集合  S1为子集  S2为补集
for (int S1 = S; S1; S1 = (S1 - 1) & S) {
	int S2 = (S ^ S1);
}
```
示例
```cpp
#include <bits/stdc++.h>
using namespace std;
void print(int x, bool tag = true) {
    if(tag && !x) {
        putchar('0');
        return ;
    }
    if(!x) return ;
    print(x >> 1, false);
    printf("%d", x & 1);
}
int main () {
    int S; while(~scanf("%d", &S)) {
        print(S); puts("");
        // S是集合  S1是子集  S2是子集的补集
        for (int S1 = S; S1; S1 = (S1 - 1) & S) {
            int S2 = (S ^ S1);
            print(S1); printf("----"); print(S2); putchar('\n');
        }
    }
    return 0;
}
```
###### 可行解的floyd优化
可用 $bitset$ 来优化时间复杂度，例题[牛客挑战赛47-C-条件](https://ac.nowcoder.com/acm/contest/10743/C)
需弄清楚 $floyd$ 循环变量的位置