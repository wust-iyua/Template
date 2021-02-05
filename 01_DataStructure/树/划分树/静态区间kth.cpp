const int maxn = 2e5 + 7;
int num[21][maxn], val[21][maxn], n, m;
int V[maxn];
void build(int dep, int l, int r) {
    if(l == r) return ;
    int mid = l + r >> 1, same = mid - l + 1, nl = l, nr = mid + 1;
    for (int i = l; i <= r; ++ i) same -= (val[dep][i] < V[mid]);
    for (int i = l; i <= r; ++ i) {
        if(i == l) num[dep][i] = 0;
        else {
            num[dep][i] = num[dep][i - 1];
        }
        if(val[dep][i] < V[mid] || same && val[dep][i] == V[mid]) {
            ++ num[dep][i];
            val[dep + 1][nl ++] = val[dep][i];
            same -= (val[dep][i] == V[mid]);
        } else {
            val[dep + 1][nr ++] = val[dep][i];
        }
    }
    build(dep + 1, l, mid);
    build(dep + 1, mid + 1, r);
}
#define md(x, y)    (x + y >> 1)
int querykth(int dep, int L, int R, int l, int r, int k) {
    if(L == R) return val[dep][L];
    int tmp = 0;
    if(l != L) tmp = num[dep][l - 1];
    int mid = l + r >> 1, cnt = num[dep][r] - tmp;
    if(cnt >= k) {
        return querykth(dep + 1, L, md(L, R), tmp + L, L + num[dep][r] - 1, k);
    } else {
        int lp1 = (l - L) - tmp;
        int lp2 = (r - l + 1) - cnt;
        return querykth(dep + 1, md(L, R) + 1, R, md(L, R) + 1 + lp1, md(L, R) + 1 + lp1 + lp2 - 1, k - cnt);
    }
}
void solve () {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", V + i);
        val[0][i] = *(V + i);
    }
    sort(V + 1, V + n + 1);
    build(0, 1, n);
    while(m --) {
        int l, r, k; scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", querykth(0, 1, n, l, r, k));
    }
}