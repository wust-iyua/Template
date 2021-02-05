#include <bits/stdc++.h>
using namespace std;
#define int  long long 
inline int lowbit(int x) { return x & (-x);}
const int maxn = 5e3 + 7;
int Tree[maxn][maxn], n, m;
void add(int x, int y, int k) {
    int prey = y;
    while(x <= n) {
        y = prey;
        while(y <= m) {
            Tree[x][y] += k;
            y += lowbit(y);
        }
        x += lowbit(x);
    }
}
void range_add(int a, int b, int c, int d, int k) {
    add(a, b, k);
    add(a, d + 1, -k);
    add(c + 1, b, -k);
    add(c + 1, d + 1, k);
}
int query(int x, int y) {
    int res = 0, prey = y;
    while(x >= 1) {
        y = prey;
        while(y >= 1) {
            res += Tree[x][y];
            y -= lowbit(y);
        }
        x -= lowbit(x);
    }
    return res;
}
signed main () {
    scanf("%lld %lld", &n, &m);
    int option, a, b, c, d, k;
    while(~scanf("%lld", &option)) {
        if(option == 1) {
            scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &k);
            range_add(a, b, c, d, k);
        } else {
            scanf("%lld %lld", &a, &b);
            printf("%lld\n", query(a, b));
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}