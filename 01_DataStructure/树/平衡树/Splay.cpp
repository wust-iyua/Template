/*
    1.插入x
    2.删除x(只删除一个)
    3.查询x的排名
    4.查询排名为x的数
    5.求x的前驱(小于x的最大的数)
    6.求x的后驱(大于x的最小的数)
*/
const int N = 1e5 + 7;
struct SplayTree {
    #define ls(u)   ch[u][0]
    #define rs(u)   ch[u][1]
    #define IMX     INT_MAX
    #define IMN     INT_MIN
    int ch[N][2], fa[N], val[N], cnt[N], siz[N], cup[N], top, root;
    SplayTree() : root(0) {}
    // 判断x是它父亲的什么儿子
    inline int chk(int x) {
        return ls(fa[x]) == x ? 0 : 1;
    }
    inline void push_up(int x) {
        siz[x] = siz[ls(x)] + siz[rs(x)] + cnt[x];
    }
    inline void Rotate(int x) {
        int y = fa[x], z = fa[y], sx = chk(x), sy = chk(y), s = ch[x][sx^1];
        ch[y][sx] = s; fa[s] = y;
        ch[z][sy] = x; fa[x] = z;
        ch[x][sx^1] = y; fa[y] = x;
        // 注意先更新y
        push_up(y); push_up(x);
    }
    void splay(int x, int ed) {
        while(fa[x] != ed) {
            int y = fa[x], z = fa[y];
            if(z != ed) {
                // 判断是否三点共线
                if(chk(x) == chk(y)) Rotate(y);
                else {
                    Rotate(x);
                }
            }
            Rotate(x);
        }
        if(!ed) root = x;
    }
    void insert(int x) {
        int cur = root, f = 0;
        while(cur && val[cur] != x) {
            f = cur;
            cur = ch[cur][x > val[cur]];
        }
        if(cur) {
            ++ cnt[cur];
        } else {
            cur = cup[top --];
            if(f) ch[f][x > val[f]] = cur;
            ch[cur][0] = ch[cur][1] = 0;
            fa[cur] = f; val[cur] = x;
            cnt[cur] = siz[cur] = 1;
        }
        splay(cur, 0);
    }
    void seek(int x) {
        int cur = root;
        // 找到x值的节点
        while(ch[cur][x > val[cur]] && x != val[cur]) {
            cur = ch[cur][x > val[cur]];
        }
        splay(cur, 0);
    }
    // 求第k大的值的下标
    int kth(int k) {
        int cur = root;
        if(siz[root] < k) return -1;
        while(1) {
            if(ch[cur][0] && k <= siz[ls(cur)]) {
                cur = ls(cur);
            } else if(k > siz[ls(cur)] + cnt[cur]) {
                k -= siz[ls(cur)] + cnt[cur];
                cur = rs(cur);
            } else {
                break;
            }
        }
        return cur;
    }
    // 查询前后驱  0~前驱  1~后驱
    int Find(int x, int f) {
        seek(x);
        if(val[root] < x && !f) return root;
        if(val[root] > x && f) return root;
        int cur = ch[root][f];
        while(ch[cur][f^1]) cur = ch[cur][f^1];
        return cur;
    }
    void del(int x) {
        int pre = Find(x, 0), nxt = Find(x, 1);
        splay(pre, 0); splay(nxt, pre);
        int id = ch[nxt][0];
        if(!id) return ;
        if(cnt[id] > 1) {
            -- cnt[id];
            splay(id, 0);
        } else {
            cup[++ top] = ch[nxt][0];
            ch[nxt][0] = 0;
        }
    }
    int getrk(int x) {
        seek(x);
        // 因为开始会insert两个极值
        return siz[ls(root)];
    }
    // 动态开点 && 可回收
    inline void clear() {
        top = 0;
        ls(0) = rs(0) = 0;
        for (int i = N - 1; i > 0; -- i) cup[++ top] = i;
        insert(IMX);
        insert(IMN);
    }
    #undef IMX
    #undef IMN
}splay;
int main () {
    splay.clear();
    int option, x;
    int Q; scanf("%d", &Q); while(Q --) {
        scanf("%d %d", &option, &x);
        if(option == 1) {
            splay.insert(x);
        } else if(option == 2) {
            splay.del(x);
        } else if(option == 3) {
            printf("%d\n", splay.getrk(x));
        } else if(option == 4) {
            printf("%d\n", splay.val[splay.kth(x + 1)]);
        } else if(option == 5) {
            printf("%d\n", splay.val[splay.Find(x, 0)]);
        } else {
            printf("%d\n", splay.val[splay.Find(x, 1)]);
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}
