//区间min
struct Jry_Tree {
#define ls      (rt << 1)
#define rs      (rt << 1|1)
#define md      (l + r >> 1)
#define lson    ls, l, md
#define rson    rs, md + 1, r
        struct SegTree {
                int l, r, tag, mx1, mx2, cnt;
                LL sum;
        }Tree[maxn << 2];
        inline void push_up(int rt) {
                int l = Tree[rt].l, r = Tree[rt].r;
                if(l == r) return ;
                Tree[rt].sum = Tree[ls].sum + Tree[rs].sum;
                if(Tree[ls].mx1 == Tree[rs].mx1) {
                        Tree[rt].mx1 = Tree[ls].mx1;
                        Tree[rt].mx2 = max(Tree[ls].mx2, Tree[rs].mx2);
                        Tree[rt].cnt = Tree[ls].cnt + Tree[rs].cnt;
                } else if(Tree[ls].mx1 > Tree[rs].mx1) {
                        Tree[rt].mx1 = Tree[ls].mx1;
                        Tree[rt].cnt = Tree[ls].cnt;
                        Tree[rt].mx2 = max(Tree[ls].mx2, Tree[rs].mx1);
                } else {
                        Tree[rt].mx1 = Tree[rs].mx1;
                        Tree[rt].cnt = Tree[rs].cnt;
                        Tree[rt].mx2 = max(Tree[ls].mx1, Tree[rs].mx2);
                }
        }
        void Build(int rt, int l, int r) {
                Tree[rt] = (SegTree) {l, r, -1, -1, -1, 1, 0};
                if(l == r) {
                        Tree[rt].mx1 = Tree[rt].sum = read();
                } else {
                        Build(lson);
                        Build(rson);
                        push_up(rt);
                }
        }
        inline void addtag(int rt, int tag) {
                if(Tree[rt].mx1 <= tag) return ;
                Tree[rt].sum -= 1ll * Tree[rt].cnt * (Tree[rt].mx1 - tag);
                Tree[rt].mx1 = tag;
                Tree[rt].tag = tag;
        }
        inline void push_down(int rt) {
                int l = Tree[rt].l, r = Tree[rt].r;
                if(l == r || Tree[rt].tag == -1) return ;
                addtag(ls, Tree[rt].tag);
                addtag(rs, Tree[rt].tag);
                Tree[rt].tag = -1;
        }
        void updata(int rt, int L, int R, int tag) {
                //cerr << "  updata  " << L << "   " << R << endl;
                if(Tree[rt].mx1 <= tag) return ;
                int l = Tree[rt].l, r = Tree[rt].r;
                if(l == r) {
                        Tree[rt].mx1 = tag;
                        Tree[rt].mx2 = -1;
                        Tree[rt].cnt = 1;
                        Tree[rt].sum = tag;
                        Tree[rt].tag = -1;
                        return ;
                }
                if(l == L && r == R && Tree[rt].mx2 < tag) {
                        addtag(rt, tag);
                        return ;
                }
                push_down(rt);
                if(R <= md) updata(ls, L, R, tag);
                else if(L >= md + 1) updata(rs, L, R, tag);
                else {
                        updata(ls, L, md, tag);
                        updata(rs, md + 1, R, tag);
                }
                push_up(rt);
        }
        LL query(int rt, int L, int R) {
        //      cerr << "  query  " << L << "   " << R << endl;
                int l = Tree[rt].l, r = Tree[rt].r;
                if(l == L && r == R) return Tree[rt].sum;
                push_down(rt);
                if(R <= md) return query(ls, L, R);
                else if(L >= md + 1) return query(rs, L, R);
                else {
                        return query(ls, L, md) + query(rs, md + 1, R);
                }
        }
}jry;