#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "   ==   " << x << endl;
using namespace std;
// https://www.luogu.com.cn/problem/P3690
// 洛谷P3690
/*
    0. 查询边权信息  sum / max / min / xor
    1. 开链
    2. 断链
    3. 修改点权
*/
#define ls(x)   son[x][0]
#define rs(x)   son[x][1]
template<typename T, const size_t MAX = 300007>
class Link_Cut_Tree {
    public :
        // 点值与路径权值
        T val[MAX], sum[MAX];
        // 栈  splay要从上往下放标记， 所以单独开的栈来push_down
        int sta[MAX], top;
        inline void clear(int n) {
            for (int i = 0; i <= n; ++ i) {
                val[i] = sum[i] = 0;
                revtag[i] = 0;
                ls(i) = rs(i) = Fa[i] = 0;
            }
        }
        inline void Splay(int x) {
            int y = x;
            top = 0; sta[++ top] = y;
            while(!isroot(y)) {
                sta[++ top] = Fa[y];
                y = Fa[y];
            }
            while(top) push_down(sta[top --]);
            while(!isroot(x)) {
                y = Fa[x]; int z = Fa[y];
                if(!isroot(y)) Rotate((chk(x) ^ chk(y)) ? x : y);
                Rotate(x);
            }
        }
        // 换根  使x变成这个树的根
        // 森林 > 树 > 若干splay
        inline void makeroot(int x) {
            Access(x); Splay(x);
            Rev(x);
        }
        // 提取边  单独拎出来
        // Splitʱ��תy���˶���  �Ҹ��º���  ��ʱy����ľ�����������Ϣ
        inline void Split(int x, int y) {
            makeroot(x);
            Access(y); Splay(y);
        }
        // // 是否有边
        // inline bool islink(int x, int y) {
        //     makeroot(x);
        //     return findroot(y) == x && Fa[y] == x && !ls(y);
        // }
        // 连边
        inline void Link(int x, int y) {
            makeroot(x);
            if(findroot(y) != x) Fa[x] = y;
        }
        // 断边
        inline void cut(int x, int y) {
            makeroot(x);
            if(findroot(y) == x && Fa[y] == x && !ls(y)) {
                Fa[y] = rs(x) = 0;
                push_up(x);
            }
        }
        // 维护信息
        inline void push_up(int x) {
            sum[x] = (sum[ls(x)] ^ sum[rs(x)] ^ val[x]);
        }
    private :
        int Fa[MAX], son[MAX][2], revtag[MAX];
        // 判断是否为 splay 的根  只需父亲节点不含这个儿子即可
        // 即父子边为虚
        inline bool isroot(int x) {
            return ls(Fa[x]) != x && rs(Fa[x]) != x;
        }
        // 换根后反转 splay 维持性质
        inline void Rev(int x) {
            swap(ls(x), rs(x));
            revtag[x] ^= 1;
        }
        // 下放标记
        inline void push_down(int x) {
            if(revtag[x]) {
                if(ls(x)) Rev(ls(x));
                if(rs(x)) Rev(rs(x));
                revtag[x] ^= 1;
            }
        }
        // 判断是 左/右 儿子
        inline int chk(int x) {
            return rs(Fa[x]) == x;
        }
        // 上旋
        inline void Rotate(int x) {
            int y = Fa[x], z = Fa[y];
            int sx = chk(x), sy = chk(y), s = son[x][sx ^ 1];
            if(!isroot(y)) {
                son[z][sy] = x;
            }
            son[x][sx ^ 1] = y;
            son[y][sx] = s;
            if(s) Fa[s] = y;
            Fa[y] = x; Fa[x] = z;
            push_up(y);
            push_up(x);
        }
        // 开辟 根到x  这条路为重链
        inline void Access(int x) {
            for (int y = 0; x; x = Fa[y = x]) {
                Splay(x);
                rs(x) = y;
                push_up(x);
            }
        }
        // 找到这个点所处的树的根
        inline int findroot(int x) {
            Access(x); Splay(x);
            //  因为lazy标记是覆盖的同时反转
            //  所以这里可以直接判断左儿子
            while(ls(x)) {
                push_down(x);
                x = ls(x);
            }
            Splay(x);
            return x;
        }
};
Link_Cut_Tree<int> LCT;
int main () {
    int n, m; scanf("%d %d", &n, &m);
    LCT.clear(n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &LCT.val[i]);
        LCT.sum[i] = LCT.val[i];
    }
    while(m --) {
        int op, x, y; scanf("%d %d %d", &op, &x, &y);
        // 查询 x~y  异或之和
        // Splitʱ��תy���˶���  �Ҹ��º���  ��ʱy����ľ�����������Ϣ
        if(op == 0) {
            LCT.Split(x, y);
            printf("%d\n", LCT.sum[y]);
        } else if(op == 1) {
            // 链接 x~y
            LCT.Link(x, y);
        } else if(op == 2) {
            // 断开 x~y
            LCT.cut(x, y);
        } else {
            //  修改点x
            LCT.Splay(x);
            LCT.val[x] = y;
            LCT.push_up(x); 
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}
