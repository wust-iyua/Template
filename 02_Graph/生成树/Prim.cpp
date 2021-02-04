const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;
int e[maxn][maxn], dis[maxn], vis[maxn];
int n, m;
void prim(int st)
{
    for (int i = 1; i <= n; i++)
    {
        vis[i] = 0;
        dis[i] = e[1][i];
    }
    vis[1] = 1;
    int sum = 0, cnt = 0;
    while (true)
    {
        int mn = inf, pos = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i] && dis[i] < mn)
            {
                mn = dis[i];
                pos = i;
            }
        }
        if (pos == -1)
        {
            break;
        }
        vis[pos] = 1;
        sum += dis[pos];
        cnt++;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i] && dis[i] > e[pos][i])
            {
                dis[i] = e[pos][i];
            }
        }
    }
    if (cnt != n - 1)
    {
        puts("无法构成最小生成树");
    }
    else
    {
        printf("最小生成树的权值为%d\n", sum);
    }
}
void solve()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                e[i][j] = 0;
            }
            else
            {
                e[i][j] = inf;
            }
        }
    }
    while (m--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        e[a][b] = e[b][a] = min(e[a][b], c);
    }
    prime(1);
}