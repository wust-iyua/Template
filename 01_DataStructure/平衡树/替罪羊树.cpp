// 洛谷P3369
// https://www.luogu.com.cn/problem/P3369
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define ls(x)   Tree[x].son[0]
#define rs(x)   Tree[x].son[1]
using namespace std;
const int maxn = 1e5 + 7;
const double alpha = 0.75;
int top, Q, cup[maxn], rt, st, cnt;
int cur[maxn];
inline void init () {
    top = 0;
    for (int i = maxn - 1; i > 0; -- i) {
        cup[++ top] = i;
    }
}
struct Scapegoat {
    int son[2], fac, siz, exist, val;
}Tree[maxn];
inline void push_up(int x) {
    Tree[x].fac = Tree[ls(x)].fac + Tree[rs(x)].fac + 1;
    Tree[x].siz = Tree[ls(x)].siz + Tree[rs(x)].siz + 1;
}
inline bool balance(int x) {
    return (double)Tree[x].fac * alpha > (double)max(Tree[ls(x)].fac, Tree[rs(x)].fac);
}
inline void build(int x) {
    Tree[x].son[0] = Tree[x].son[1] = 0;
    Tree[x].fac = Tree[x].siz = 1;
}
inline void insert(int& x, int val) {
    if(!x) {
        x = cup[top --];
        Tree[x].val = val;
        Tree[x].exist = 1;
        build(x);
        return ;
    }
    ++ Tree[x].fac;
    ++ Tree[x].siz;
    if(val <= Tree[x].val) insert(ls(x), val);
    else {
        insert(rs(x), val);
    }
}
// 中序遍历
inline void Trave(int x) {
    if(!x) return ;
    Trave(ls(x));
    if(Tree[x].exist) {
        cur[++ cnt] = x;
    } else {
        cup[++ top] = x;
    }
    Trave(rs(x));
}
inline void setup(int& x, int l, int r) {
    int mid = l + r >> 1;
    x = cur[mid];
    if(l == r) {
        build(x);
        return ;
    }
    if(l < mid) setup(ls(x), l, mid - 1);
    else {
        ls(x) = 0;
    }
    setup(rs(x), mid + 1, r);
    push_up(x);
}
inline void rebuild(int& x) {
    cnt = 0;
    Trave(x);
    if(cnt) {
        setup(x, 1, cnt);
    } else {
        x = 0;
    }
}
inline void check(int x, int val) {
    int id = val <= Tree[x].val ? 0 : 1;
    while(Tree[x].son[id]) {
        if(!balance(Tree[x].son[id])) {
            rebuild(Tree[x].son[id]);
            return ;
        }
        x = Tree[x].son[id];
        id = val <= Tree[x].val ? 0 : 1;
    }
}
inline int getrak(int val) {
    int rk = 1, x = rt;
    while(x) {
        if(Tree[x].val >= val) x = ls(x);
        else {
            rk += Tree[ls(x)].fac + Tree[x].exist;
            x = rs(x);
        }
    }
    return rk;
}
inline int getval(int rk) {
    int x = rt;
    while(x) {
        if(Tree[x].exist && Tree[ls(x)].fac + 1 == rk) {
            return Tree[x].val;
        } else if(Tree[ls(x)].fac >= rk) {
            x = ls(x);
        } else {
            rk -= Tree[ls(x)].fac + Tree[x].exist;
            x = rs(x);
        }
    }
    return 0;
}
inline void Delete (int rk) {
    int x = rt;
    while(x) {
        -- Tree[x].fac;
        if(Tree[x].exist && Tree[ls(x)].fac + 1 == rk) {
            Tree[x].exist = 0;
            return ;
        }
        if(rk <= Tree[ls(x)].fac + Tree[x].exist) {
            x = ls(x);
        } else {
            rk -= Tree[ls(x)].fac + Tree[x].exist;
            x = rs(x);
        }
    }
}
inline void del(int x) {
    x = getrak(x);
    Delete(x);
    if((double)Tree[rt].siz * alpha > (double)Tree[rt].fac) {
        rebuild(rt);
    }
}
int main () {
    init();
    scanf("%d", &Q);
    rt = 0;
    int option, x;
    while(Q --) {
        scanf("%d %d", &option, &x);
        if(option == 1) {
            st = rt;
            insert(rt, x);
            check(st, x);
        } else if(option == 2) {
            del(x);
        } else if(option == 3) {
            printf("%d\n", getrak(x));
        } else if(option == 4) {
            printf("%d\n", getval(x));
        } else if(option == 5) {
            printf("%d\n", getval(getrak(x) - 1));
        } else {
            // 注意此处是x + 1 不是  rk + 1
            printf("%d\n", getval(getrak(x + 1)));
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}