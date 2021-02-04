// 板子题 洛谷P3809  https://www.luogu.com.cn/problem/P3809
// 学习博客  https://www.cnblogs.com/zwfymqz/p/8413523.html
#include <bits/stdc++.h>
#define de(x)   cout << "   debug    " << #x << " == " << x << endl;
using namespace std;
const int N = 1e6 + 7;
struct SuffixArray {
    // 文本串  注意下标是从1开始
    char str[N];
    // 后缀数组  sa[i] -- 排名i的下标
    // 名次     rk[i] -- 下标i的排名
    // 第二关键字(基数排序)
    // 每个名次的数目(基数排序计数)
    // 字符串长度和最大元素大小  'Z' < 'z' == 122   m可以取130
    int sa[N], rk[N], y[N], cnt[N], n, m;
    // height[i] -->  sa[i]起始与sa[i-1]起始的最长前缀长度
    int height[N];
    // 基数排序
    void Qsort() {
        for (int i = 0; i <= m; ++ i) cnt[i] = 0;
        for (int i = 1; i <= n; ++ i) ++ cnt[rk[i]];
        for (int i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; -- i) sa[cnt[rk[y[i]]] --] = y[i];
    }
    // 获取后缀数组
    void GetSa() {
        m = 130;
        n = strlen(str + 1);
        for (int i = 1; i <= n; ++ i) rk[i] = str[i], y[i] = i;
        Qsort();
        // w代表目前已经倍增出来的长度  此时需要进行2*w的倍增
        // p表示此时不同排名的后缀的个数  p == n时则不需要继续下去了
        // m = p 属于常数小优化
        for (int w = 1, p = 0; p < n; m = p, w <<= 1) {
            // 此时p仅仅是一个计数变量
            p = 0;
            // 求得第二关键字
            for (int i = 1; i <= w; ++ i) y[++ p] = n - w + i;
            for (int i = 1; i <= n; ++ i) {
                if(sa[i] > w) {
                    y[++ p] = sa[i] - w;
                }
            }
            // 用上一轮的排名和这一轮的第二关键字来倍增
            Qsort();
            swap(y, rk); 
            rk[sa[1]] = p = 1;
            for (int i = 2; i <= n; ++ i) {
                rk[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + w] == y[sa[i] + w]) ? p : ++ p;
            }
        }
        for (int i = 1; i <= n; ++ i) rk[sa[i]] = i;
    }
    void GetHeight() {
        int k = 0; // 上一个h[i]
        height[1] = 0;
        for (int i = 1; i <= n; ++ i) {
            if(rk[i] == 1) continue;
            if(k) -- k;
            int j = sa[rk[i] - 1];
            while(i + k <= n && j + k <= n && str[i + k] == str[j + k]) ++ k;
            height[rk[i]] = k;
        }
    }
    // 传入点  注意左边rk会加一
    int LCP(int a, int b) {
        int u = min(rk[a], rk[b]), v = max(rk[a], rk[b]);
        int res = 0x7fffffff;
        for (int i = u + 1; i <= v; ++ i) res = min(res, height[i]);
        return res;
    }
    // ST表 
    int LCP[N][20], Log[N];
    void buildLCP() {
        Log[1] = 0;
        for (int i = 2; i <= n; ++ i) Log[i] = Log[i/2] + 1;
        for (int i = 1; i <= n; ++ i) LCP[i][0] = height[i];
        for (int j = 1; (1 << j) <= n; ++ j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++ i) {
                LCP[i][j] = min(LCP[i][j-1], LCP[i + (1 << j - 1)][j-1]);
            }
        }
    }
    // 传入点  注意排名左端点需要加一
    int queryLCP(int u, int v) {
        if(rk[u] > rk[v]) swap(u, v);
        u = rk[u] + 1, v = rk[v];
        int k = Log[v - u + 1];
        return min(LCP[u][k], LCP[v - (1 << k) + 1][k]);
    }
}SA;
int main () {
    scanf("%s", SA.str + 1);
    SA.n = strlen(SA.str + 1);
    SA.GetSa();
    for (int i = 1; i <= SA.n; ++ i) printf("%d%c", SA.sa[i], i == SA.n ? '\n' : ' ');
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}