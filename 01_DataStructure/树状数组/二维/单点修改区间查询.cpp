#include <bits/stdc++.h>
using namespace std;
typedef long long  LL;
const int maxn = 5e3 + 7;
inline int lowbit(int x) {
    return x & (-x);
}
LL tree[maxn][maxn];
int n, m;
void updata(int x, int y, int val) {
    int prey = y;

    while (x <= n) {
        y = prey;

        while (y <= m) {
            tree[x][y] += val;
            y += lowbit(y);
        }

        x += lowbit(x);
    }
}
LL query(int x, int y) {
    LL res = 0;
    int prey = y;

    while (x >= 1) {
        y = prey;

        while (y >= 1) {
            res += tree[x][y];
            y -= lowbit(y);
        }

        x -= lowbit(x);
    }

    return res;
}
LL range_query(int a, int b, int c, int d) {
    return query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1);
}
int main() {
    scanf("%d %d", &n, &m);
    int ope;

    while (~scanf("%d", &ope)) {
        int x, y, k, a, b, c, d;

        if (ope == 1) {
            scanf("%d %d %d", &x, &y, &k);
            updata(x, y, k);
        } else {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            printf("%lld\n", range_query(a, b, c, d));
        }
    }

#ifdef iyua
    system("pause");
#endif
    return 0;
}