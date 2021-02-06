#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "   ==   " << x << endl;
using namespace std;
// https://www.luogu.com.cn/problem/P3690
// ??P3690
/*
    0. ??????  sum / max / min / xor
    1. ??
    2. ??
    3. ????
*/
#define ls(x)   son[x][0]
#define rs(x)   son[x][1]
template<typename T, const size_t MAX = 300007>
class Link_Cut_Tree {
    public :
        // ???????
        T val[MAX], sum[MAX];
        // ?  splay????????? ????????push_down
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
        // ??  ?x???????
        // ?? > ? > ??splay
        inline void makeroot(int x) {
            Access(x); Splay(x);
            Rev(x);
        }
        // ???  ?????
    	// Split???y????  ?????  ??y??????????
        inline void Split(int x, int y) {
            makeroot(x);
            Access(y); Splay(y);
        }
        // // ????
        // inline bool islink(int x, int y) {
        //     makeroot(x);
        //     return findroot(y) == x && Fa[y] == x && !ls(y);
        // }
        // ??
        inline void Link(int x, int y) {
            makeroot(x);
            if(findroot(y) != x) Fa[x] = y;
        }
        // ??
        inline void cut(int x, int y) {
            makeroot(x);
            if(findroot(y) == x && Fa[y] == x && !ls(y)) {
                Fa[y] = rs(x) = 0;
                push_up(x);
            }
        }
    	// ????
        inline void push_up(int x) {
            sum[x] = (sum[ls(x)] ^ sum[rs(x)] ^ val[x]);
        }
    private :
        int Fa[MAX], son[MAX][2], revtag[MAX];
        // ????? splay ??  ??????????????
        // ??????
        inline bool isroot(int x) {
            return ls(Fa[x]) != x && rs(Fa[x]) != x;
        }
        // ????? splay ????
        inline void Rev(int x) {
            swap(ls(x), rs(x));
            revtag[x] ^= 1;
        }
        // ????
        inline void push_down(int x) {
            if(revtag[x]) {
                if(ls(x)) Rev(ls(x));
                if(rs(x)) Rev(rs(x));
                revtag[x] ^= 1;
            }
        }
        // ??? ?/? ??
        inline int chk(int x) {
            return rs(Fa[x]) == x;
        }
        // ??
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
        // ?? ??x  ??????
        inline void Access(int x) {
            for (int y = 0; x; x = Fa[y = x]) {
                Splay(x);
                rs(x) = y;
                push_up(x);
            }
        }
        // ???????????
        inline int findroot(int x) {
            Access(x); Splay(x);
            //  ??lazy??????????
            //  ?????????????
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
        // ?? x~y  ????
        if(op == 0) {
            // Split???y????  ?????  ??y??????????
            LCT.Split(x, y);
            printf("%d\n", LCT.sum[y]);
        } else if(op == 1) {
            // ?? x~y
            LCT.Link(x, y);
        } else if(op == 2) {
            // ?? x~y
            LCT.cut(x, y);
        } else {
            //  ???x
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