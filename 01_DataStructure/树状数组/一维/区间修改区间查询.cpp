#include <bits/stdc++.h>
using namespace std;
typedef long long  LL;
const int maxn = 1e6 + 7;
inline int lowbit(int x) {
    return x & (-x);
}
LL sum1[maxn], sum2[maxn];
int arr[maxn], n, q;
void add(int pos, int val) {
    int pre = pos;

    while (pos <= n) {
        sum1[pos] += 1ll * val;
        sum2[pos] += 1ll * pre * val;
        pos += lowbit(pos);
    }
}
void range_add(int l, int r, int val) {
    add(l, val);
    add(r + 1, -val);
}
LL ask(int pos) {
    int pre = pos;
    LL res = 0;

    while (pos >= 1) {
        res += 1ll * (pre + 1) * sum1[pos] - sum2[pos];
        pos -= lowbit(pos);
    }

    return res;
}
LL range_ask(int L, int R) {
    return ask(R) - ask(L - 1);
}
int main() {
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &arr[i]);
        add(i, arr[i] - arr[i - 1]);
    }

    while (q --) {
        int ope, l, r, val;
        scanf("%d", &ope);

        if (ope == 1) {
            scanf("%d %d %d", &l, &r, &val);
            range_add(l, r, val);
        } else {
            scanf("%d %d", &l, &r);
            printf("%lld\n", range_ask(l, r));
        }
    }

#ifdef iyua
    system("pause");
#endif
    return 0;
}