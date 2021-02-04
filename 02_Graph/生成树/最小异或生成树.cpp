// 完全图  边权为两个节点权值异或结果

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
typedef long long  LL;
struct XorMinTree {
    int n, arr[maxn];
    LL res;
    int Tree[maxn * 30][2], top;
    void clear() {
        res = 0;
        top = 0;
        Tree[0][0] = Tree[0][1] = 0;
    }
    void insert(int x) {
        int root = 0;
        for (int i = 30; i >= 0; -- i) {
            int ch = (1 & (x >> i));
            if(!Tree[root][ch]) {
                Tree[root][ch] = ++ top;
                //这样可以不用O(n)清空  每次开点自动处理历史遗留
                Tree[Tree[root][ch]][0] = Tree[Tree[root][ch]][1] = 0;
            }
            root = Tree[root][ch];
        }
    }
    void read() {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++ i) scanf("%d", arr + i);
        // 带佬们都说sort一下会加速  我也不懂为啥
        sort(arr + 1, arr + n + 1);
        for (int i = 1; i <= n; ++ i) insert(arr[i]);
        res = 0;
    }
    // 查询两个子树xor最小
    LL query(int r1, int r2, int bit) {
        if(bit < 0) return 0;
        int sum1 = -1, sum2 = -1;
        if(Tree[r1][0] && Tree[r2][0]) {
            sum1 = query(Tree[r1][0], Tree[r2][0], bit - 1);
        } 
        if(Tree[r1][1] && Tree[r2][1]) {
            sum2 = query(Tree[r1][1], Tree[r2][1], bit - 1);
        }
        if(~sum1 && ~sum2) return min(sum1, sum2);
        if(~sum1) return sum1;
        if(~sum2) return sum2;
        if(Tree[r1][0] && Tree[r2][1]) {
            sum1 = query(Tree[r1][0], Tree[r2][1], bit - 1) + (1 << bit);
        }
        if(Tree[r1][1] && Tree[r2][0]) {
            sum2 = query(Tree[r1][1], Tree[r2][0], bit - 1) + (1 << bit);
        }
        if(~sum1 && ~sum2) return min(sum1, sum2);
        if(~sum1) return sum1;
        if(~sum2) return sum2;
    }
    // 分治lca
    void devide(int root, int bit = 30) {
        // LCA
        if(Tree[root][1] && Tree[root][0]) {
            res += query(Tree[root][0], Tree[root][1], bit - 1) + (1 << bit);
        }
        // devide
        if(Tree[root][0]) {
            devide(Tree[root][0], bit - 1);
        }
        if(Tree[root][1]) {
            devide(Tree[root][1], bit - 1);
        }
    }
}solve;
int main () {
    solve.read();
    solve.devide(0);
    printf("%lld\n", solve.res);
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}