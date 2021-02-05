// 洛谷P3402
/*
	1.  合并 a b
	2. 回到第k次操作之后
	3. 查询此时 a b
*/
#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "  ==  " << x << endl;
using namespace std; 
const int maxn = 3e5 + 7;
int top = 0, root[maxn * 30];
struct ChairManDSU {
    #define ls(x)   Tree[x].l
    #define rs(x)   Tree[x].r
    struct DSUTree {
        int rt, l, r;
    } Tree[maxn * 30];
    int hei[maxn * 30], fa[maxn * 30];
    void build(int& rt, int l, int r) {
        rt = ++ top;
        if(l == r) {
            fa[rt] = l;
            hei[rt] = 1;
        } else {
            int md = l + r >> 1;
            build(ls(rt), l, md);
            build(rs(rt), md + 1, r);
        }
    }
    void Merge(int& rt, int fr, int l, int r, int pos, int to) {
        rt = ++ top;
        ls(rt) = ls(fr), rs(rt) = rs(fr);
        if(l == r) {
            fa[rt] = to;
            hei[rt] = hei[fr];
            return ;
        }
        int md = l + r >> 1;
        if(pos <= md) Merge(ls(rt), ls(fr), l, md, pos, to);
        else {
            Merge(rs(rt), rs(fr), md + 1, r, pos, to);
        }
    }
    int seekid(int rt, int l, int r, int pos) {
        if(l == r) return rt;
        int md = l + r >> 1;
        if(pos <= md) return seekid(ls(rt), l, md, pos);
        else {
            return seekid(rs(rt), md + 1, r, pos);
        }
    }
    int seekfaid(int rt, int n, int pos) {
        int id = seekid(rt, 1, n, pos);
        return fa[id] == pos ? id : seekfaid(rt, n, fa[id]);
    }
    void addhei(int rt, int l, int r, int pos) {
        if(l == r) {
            ++ hei[rt];
            return ;
        }
        int md = l + r >> 1;
        if(pos <= md) addhei(ls(rt), l, md, pos);
        else {
            addhei(rs(rt), md + 1, r, pos);
        }
    }
}DSU;
int main () {
    int n, m; scanf("%d %d", &n, &m);
    DSU.build(root[0], 1, n);
    for (int i = 1; i <= m; ++ i) {
        int op, a, b; scanf("%d %d", &op, &a);
        if(op^2) scanf("%d", &b);
        if(op == 1) {
            int faid = DSU.seekfaid(root[i - 1], n, a), fbid = DSU.seekfaid(root[i - 1], n, b);
            int fa = DSU.fa[faid], fb = DSU.fa[fbid];
            if(fa == fb) {
                root[i] = root[i - 1];
            } else {
                if(DSU.hei[faid] == DSU.hei[fbid]) {
                    DSU.Merge(root[i], root[i - 1], 1, n, fa, fb);
                    DSU.addhei(root[i], 1, n, fb);
                } else if (DSU.hei[faid] > DSU.hei[fbid]) {
                    DSU.Merge(root[i], root[i - 1], 1, n, fb, fa);
                } else {
                    DSU.Merge(root[i], root[i - 1], 1, n, fa, fb);
                }
            }
        } else if(op == 2) {
            root[i] = root[a];
        } else {
            root[i] = root[i - 1];
            int fa = DSU.seekfaid(root[i], n, a), fb = DSU.seekfaid(root[i], n, b);
            fa = DSU.fa[fa], fb = DSU.fa[fb];
            printf("%d\n", fa == fb);
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}