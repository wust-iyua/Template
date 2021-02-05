#include <bits/stdc++.h>
using namespace std;
typedef long long  LL;
const int maxn = 1e6 + 7;
inline int lowbit(int x) {
    return x & (-x);
}
int arr[maxn];
LL Tree[maxn] = {0};
int n, q;
void updata(int pos, int val) {
    while (pos <= n) {
        Tree[pos] += 1ll * val;
        pos += lowbit(pos);
    }
}
void change(int L, int R, int val) {
    updata(L, val);
    updata(R + 1, -val);
}
LL query(int x) {
    LL res = 0;

    while (x >= 1) {
        res += Tree[x];
        x -= lowbit(x);
    }

    return res;
}
int main() {
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &arr[i]);
        updata(i, arr[i] - arr[i - 1]);
    }

    while (q --) {
        int ope, l, r, val, pos;
        scanf("%d", &ope);

        if (ope == 1) {
            scanf("%d %d %d", &l, &r, &val);
            change(l, r, val);
        } else {
            scanf("%d", &pos);
            printf("%lld\n", query(pos));
        }
    }

#ifdef iyua
    system("pause");
#endif
    return 0;
}