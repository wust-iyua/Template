// CF915E
// 注意离散化后每个节点代表的是一个左闭右开的区间
// 同时由于读入了 n 次   n * 2个元素  开四倍空间， 所以最终应该是 n 的八倍空间
#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 3e5 + 7;
const int maxm = 1e4 + 7;
int a[maxn << 1], n, len;
struct Node {
    int l, r, k;
}cup[maxn];
vector<int> G[maxn];
#define ls  (rt << 1)
#define rs  (rt << 1|1)
#define md  (l + r >> 1)
#define Len(x)  (a[Tree[x].r] - a[Tree[x].l])
struct SegTree {
    int l, r, sum, tag;
} Tree[maxn << 3];

void push_up(int rt) {
    int l = Tree[rt].l, r = Tree[rt].r;
    Tree[rt].sum = Tree[ls].sum + Tree[rs].sum;
}
void push_down(int rt) {
    int l = Tree[rt].l, r = Tree[rt].r;
    if(Tree[rt].tag == -1) return ;
    Tree[ls].sum = Len(ls) * Tree[rt].tag;
    Tree[rs].sum = Len(rs) * Tree[rt].tag;
    Tree[ls].tag = Tree[rs].tag = Tree[rt].tag;
    Tree[rt].tag = -1;
}
void build(int rt, int l, int r) {
    Tree[rt] = (SegTree) {l, r, 0, -1};
    if(l + 1 == r) {
        Tree[rt].sum = Len(rt);
        return ;
    }
    build(ls, l, md);
    build(rs, md, r);
    push_up(rt);
}
void updata(int rt, int L, int R, int tag) {
    int l = Tree[rt].l, r = Tree[rt].r;
    if(l == L && r == R) {
        Tree[rt].sum = (a[r] - a[l]) * tag;
        Tree[rt].tag = tag;
        return ;
    }
    push_down(rt);
    if(R <= md) updata(ls, L, R, tag);
    else if(L >= md) updata(rs, L, R, tag);
    else {
        updata(ls, L, md, tag);
        updata(rs, md, R, tag);
    }
    push_up(rt);
}
int main () {
    int N, Q;
    scanf("%d %d", &N, &Q);
    len = 0;
    for (int i = 1; i <= Q; ++ i) {
        scanf("%d %d %d", &cup[i].l, &cup[i].r, &cup[i].k);
        ++ cup[i].r;
        a[++ len] = cup[i].l;
        a[++ len] = cup[i].r;
        -- cup[i].k;
    }
    a[++ len] = 1;
    a[++ len] = N + 1;
    sort(a + 1, a + len + 1);
    len = unique(a + 1, a + len + 1) - a - 1;
    build(1, 1, len);
    for (int i = 1; i <= Q; ++ i) {
        int l = lower_bound(a + 1, a + len + 1, cup[i].l) - a;
        int r = lower_bound(a + 1, a + len + 1, cup[i].r) - a;
        updata(1, l, r, cup[i].k);
        printf("%d\n", Tree[1].sum);
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}