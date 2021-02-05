// https://www.luogu.com.cn/problem/P3834
// 洛谷P3834
// 区间第k大/小
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
#define ls(rt)   Tree[rt].l
#define rs(rt)   Tree[rt].r
struct PresidentTree {
    int l, r, sum;
}Tree[maxn * 60];
int a[maxn], b[maxn], root[maxn], n, m, Q, top = 0;
void build(int& rt, int l, int r) {
    rt = ++ top;
    if(l == r) return ;
    int md = l + r >> 1;
    build(ls(rt), l, md);
    build(rs(rt), md + 1, r);
}
void updata(int& rt, int fr, int l, int r, int pos) {
    rt = ++ top;
    ls(rt) = ls(fr), rs(rt) = rs(fr), Tree[rt].sum = Tree[fr].sum + 1;
    int md = l + r >> 1;
    if(l == r) return ;
    if(pos <= md)   updata(ls(rt), ls(fr), l, md, pos);
    else {
        updata(rs(rt), rs(fr), md + 1, r, pos);
    }
}
int query(int u, int v, int l, int r, int k) {
    if(l == r) return l;
    int md = l + r >> 1;
    // // k小
    // int x = Tree[ls(v)].sum - Tree[ls(u)].sum;
    // if(x >= k) return query(ls(u), ls(v), l, md, k);
    // else {
    //     return query(rs(u), rs(v), md + 1, r, k - x);
    // }
    // k大
    int x = Tree[rs(v)].sum - Tree[rs(u)].sum;
    if(x >= k) return query(rs(u), rs(v), md + 1, r, k);
    else {
        return query(ls(u), ls(v), l, md, k - x);
    }
}
int main () {
    scanf("%d %d", &n, &Q);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    build(root[0], 1, m);
    for (int i = 1; i <= n; ++ i) updata(root[i], root[i - 1], 1, m, lower_bound(b + 1, b + m + 1, a[i]) - b);
    while(Q --) {
        int l, r, k; scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", b[query(root[l - 1], root[r], 1, m, k)]);
    }
    #ifdef iyuacpp
        system("pause");
    #endif 
    return 0;
}