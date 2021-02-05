//  洛谷P5494
// 一般是将第一个树前 cnt 个元素留下来，其余分割给新的点
// 分割出来的用动态开点维护，前cnt个直接在树上二分递归就可以了
#include <bits/stdc++.h>
#define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 2e5 + 7;
int tot, Cnt, cup[maxn * 32], n, m;
int ls[maxn * 32], rs[maxn * 32];
LL val[maxn * 32];
int root[maxn];
inline int newnode() {
    return Cnt ? cup[Cnt --] : ++ tot;
}
inline void del(int x) {
    cup[++ Cnt] = x;
    ls[x] = rs[x] = val[x] = 0;
}
void ins(int& rt, int l, int r, int pos, LL be) {
    if(!rt) {
        rt = newnode();
    }
    val[rt] += be;
    if(l == r) return ;
    int mid = l + r >> 1;
    if(pos <= mid) ins(ls[rt], l, mid, pos, be);
    else {
        ins(rs[rt], mid + 1, r, pos, be);
    }
}
LL querycnt(int& rt, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return 0;
    if(ql <= l && r <= qr) return val[rt];
    int mid = l + r >> 1;
    LL res = 0;
    if(ql <= mid) res += querycnt(ls[rt], l, mid, ql, qr);
    if(qr >= mid + 1) res += querycnt(rs[rt], mid + 1, r, ql, qr);
    return res;
}
int kth(int rt, int l, int r, LL k) {
    if(k > val[rt]) return -1;
    if(l == r) return l;
    int mid = l + r >> 1;
    if(val[ls[rt]] >= k) return kth(ls[rt], l, mid, k);
    else {
        return kth(rs[rt], mid + 1, r, k - val[ls[rt]]);
    }
}
int Merge(int u, int v) {
    if(!u || !v) return u | v;
    val[u] += val[v];
    ls[u] = Merge(ls[u], ls[v]);
    rs[u] = Merge(rs[u], rs[v]);
    del(v);
    return u;
}
void Split(int u, int& v, LL k) {
    if(!u) return ;
    v = newnode();
    LL cnt = val[ls[u]];
    if(cnt < k) {
        Split(rs[u], rs[v], k - cnt);
    } else {
        swap(rs[u], rs[v]);
    }
    if(cnt > k) Split(ls[u], ls[v], k);
    val[v] = val[u] - k;
    val[u] = k;
}
int main () {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x);
        ins(root[1], 1, n, i, x);
    }
    int now = 1;
    while(m --) {
        int op; scanf("%d", &op);
        if(op == 0) {
            int p, x, y;
            scanf("%d %d %d", &p, &x, &y);
            LL num1 = querycnt(root[p], 1, n, 1, y);
            LL num2 = querycnt(root[p], 1, n, x, y);
            ++ now;
            Split(root[p], root[now], num1 - num2);
            int tmp = 0;
            Split(root[now], tmp, num2);
            root[p] = Merge(root[p], tmp);
        } else if(op == 1) {
            int x, y; scanf("%d %d", &x, &y);
            root[x] = Merge(root[x], root[y]);
        } else if(op == 2) {
            int p, x, q; scanf("%d %d %d", &p, &x, &q);
            ins(root[p], 1, n, q, x);
        } else if(op == 3) {
            int p, x, y;
            scanf("%d %d %d", &p, &x, &y);
            printf("%lld\n", querycnt(root[p], 1, n, x, y));
        } else {
            int p, x; scanf("%d %d", &p, &x);
            printf("%d\n", kth(root[p], 1, n, x));
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}