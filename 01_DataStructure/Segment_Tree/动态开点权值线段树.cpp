//  给出权值线段树动态开点  普通线段树同理
// 可传引用 或 返回值来表示新节点
//  CF915E
//  https://www.luogu.com.cn/problem/CF915E
#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 3e5 + 7;
int top = 0;
#define ls(x)   Tree[x].l
#define rs(x)   Tree[x].r
#define sum(x)  Tree[x].sum
struct SegTree {
    int l, r, lazy;
    int sum;
} Tree[maxn * 55];
inline void push_down(int rt, int l, int r) {
    if(Tree[rt].lazy == -1) return ;
    int md = l + r >> 1, tag = Tree[rt].lazy;
    if(!ls(rt)) {
        ls(rt) = ++ top;
        // assert(top < maxn * 35);
        Tree[top] = (SegTree) {0, 0, tag, 1ll * (md - l + 1) * tag};
    } else {
        Tree[ls(rt)].lazy = tag;
        Tree[ls(rt)].sum = 1ll * (md - l + 1) * tag;
    }
    if(!rs(rt)) {
        rs(rt) = ++ top;
        // assert(top < maxn * 35);
        Tree[top] = (SegTree) {0, 0, tag, 1ll * (r - md) * tag};
    } else {
        Tree[rs(rt)].lazy = tag;
        Tree[rs(rt)].sum = 1ll * (r - md) * tag;
    }
    Tree[rt].lazy = -1;
}
inline void push_up(int rt) {
    sum(rt) = sum(ls(rt)) + sum(rs(rt));
}
void Insert(int& rt, int l, int r, int L, int R, int tag) {
    if(!rt) {
        rt = ++ top;
        // assert(top < maxn * 35);
        Tree[top] = (SegTree) {0, 0, -1, 0};
    }
    if(l == L && r == R) {
        Tree[rt].sum = 1ll * (r - l + 1) * tag;
        Tree[rt].lazy = tag;
        return ;
    }
    push_down(rt, l, r);
    int md = l + r >> 1;
    if(R <= md) Insert(ls(rt), l, md, L, R, tag);
    else if(L >= md + 1) Insert(rs(rt), md + 1, r, L, R, tag);
    else {
        Insert(ls(rt), l, md, L, md, tag);
        Insert(rs(rt), md + 1, r, md + 1, R, tag);
    }
    push_up(rt);
}
int main () {
    int root = 0;
    int n, Q; scanf("%d %d", &n, &Q);
    Insert(root, 1, n, 1, n, 1);
    while(Q --) {
        int op, l, r; scanf("%d %d %d", &l, &r, &op);
        if(op == 1) {
            Insert(root, 1, n, l, r, 0);
        } else {
            Insert(root, 1, n, l, r, 1);
        }
        printf("%d\n", Tree[root].sum);
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}