//  洛谷P1494
// 主要在于add del函数的书写  快速求出相邻区间的贡献
#include <bits/stdc++.h>
using namespace std;
typedef long long   LL;
const int maxn = 5e4 + 7;
int n, m, L, R;
LL ans, cnt[maxn], belong[maxn], block, a[maxn], res_up[maxn], res_down[maxn];
struct Node {
    int l, r, id;
    bool operator < (const Node& b) const {
        if(belong[l] == belong[b.l]) {
            return r < b.r;
        } else {
            return belong[l] < belong[b.l];
        }
    }
}Q[maxn];
void add(LL x) {
    ans -= cnt[x] * (cnt[x] - 1) / 2;
    ++ cnt[x];
    ans += cnt[x] * (cnt[x] - 1) / 2;
}
void del(LL x) {
    ans -= cnt[x] * (cnt[x] - 1) / 2;
    -- cnt[x];
    ans += cnt[x] * (cnt[x] - 1) / 2;
}
int main () {
    scanf("%d %d", &n, &m);
    block = sqrt(n);
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &a[i]);
        belong[i] = (i - 1) / block + 1;
    }
    for(int i = 1; i <= m; ++ i) {
        scanf("%d %d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
    }

    ans = 0;
    memset(cnt, 0, sizeof(cnt));
    sort(Q + 1, Q + m + 1);
    L = 1, R = 0;
    for(int i = 1; i <= m; ++ i) {
        int l = Q[i].l, r = Q[i].r, id = Q[i].id;
        if(l == r) {
            res_up[id] = 0;
            res_down[id] = 1;
            continue;
        }
        while(L < l) {
            del(a[L ++]);
        }
        while(L > l) {
            add(a[-- L]);
        }
        while(R > r) {
            del(a[R --]);
        }
        while(R < r) {
            add(a[++ R]);
        }
        res_up[id] = ans;
        res_down[id] = 1ll * (r - l + 1) * (r - l) / 2ll;
        LL gcd = __gcd(res_up[id], res_down[id]);
        res_up[id] /= gcd;
        res_down[id] /= gcd;
    }
    for(int i = 1; i <= m; ++ i) {
        printf("%lld/%lld\n", res_up[i], res_down[i]);
    }
    return 0;
}