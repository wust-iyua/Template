inline int lowbit(int x) {
    return x & (-x);
}
LL tree[maxn], n, q;
void updata(int x, LL val) {
    while (x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}
LL query(int x) {
    LL res = 0;

    while (x >= 1) {
        res += tree[x];
        x -= lowbit(x);
    }

    return res;
}
void solve() {
    ms(tree, 0);
    scanf("%lld %lld", &n, &q);
    rep(i, 1, n) {
        int tmp ;
        scanf("%d", &tmp);
        updata(i, tmp);
    }

    while (q --) {
        int pos, l, r;
        scanf("%d %d %d", &pos, &l, &r);

        if (pos == 1) {
            updata(l, r);
        } else {
            printf("%lld\n", query(r) - query(l - 1));
        }
    }
}