//  求所有生成树个数
const int N = 305;
const int mod = 1e9 + 7;
// 对于每条边 u v   则 a[u][u]  a[v][v] 度数加1  a[u][v] a[v][u] 度数减1
// 可处理重边  不可处理自环  要特判
int n, m, a[N][N];

int Gauss(int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int k = i + 1; k <= n; k++) {
            while (a[k][i]) {
                int d = a[i][i] / a[k][i];
                for (int j = i; j <= n; j++) {
                    a[i][j] = (a[i][j] - 1LL * d * a[k][j] % mod + mod) % mod;
                }
                swap(a[i], a[k]);
                ans = -ans;
            }
        }
        ans = 1LL * ans * a[i][i] % mod;
    }
    return (ans % mod + mod) % mod;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        a[u][v]--, a[v][u]--;
        a[u][u]++, a[v][v]++;
    }
    printf("%d\n", Gauss(n - 1));
    return 0;
}
//  变元矩阵树定理 求生成树权值积之和
//  洛谷P3317
// 可重边  需处理自环
//  对于边  u -> v  w     a[u][u]和a[v][v] 加w    a[u][v]和a[v][u] 减w
// 求生成树总边积的和  一般不会出板子题  要自己转换公式
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e2 + 7;
const double EPS = 1e-6;
double a[maxn][maxn];
double Gauss(int n) {
    double ans = 1.0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            int t = i;
            if(fabs(a[j][i]) > fabs(a[t][i])) t = j;
            if(t != i) {
                swap(a[t], a[i]);
                ans = -ans;
            }
        }
        for (int j = i + 1; j <= n; ++ j) {
            double t = a[j][i] / a[i][i];
            for (int k = i; k <= n; ++ k) {
                a[j][k] -= t * a[i][k];
            }
        }
        ans *= a[i][i];
    }
    return fabs(ans);
}
int main () {
    double res = 1.0;
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            scanf("%lf", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            double tmp = (1.0 - a[i][j]);
            if(fabs(tmp) < EPS) tmp = EPS;
            if(i < j) res *= tmp;
            a[i][j] /= tmp;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if(i != j) {
                a[i][i] += a[i][j];
                a[i][j] = -a[i][j];
            }
        }
    }
    printf("%.10f\n", Gauss(n - 1) * res);
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}