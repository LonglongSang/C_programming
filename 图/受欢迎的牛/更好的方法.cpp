#include <cstdio>
#include <iostream>
using namespace std;
//https://loj.ac/problem/10091
//受欢迎的牛
//先tarjan算法连点，然后统计强连通分量的入度，若有一个入度为零的强连通分量，则输出该强连通
//分量里的点数。如果存在多个强连通分量的入度都为0，则输出0
const int N = 1E4 + 10;
const int M = 5E4 + 10;

struct node {
    int to, nxt;
} e[M];
int head[N], tot;

void add(int u, int v) {
    e[++tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}

int dfn[N], low[N], dfncnt, s[N], tp;
int scc[N], sc;
int sz[N], n, m, out[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++sc;
        while (s[tp] != u) scc[s[tp]] = sc, sz[sc]++, --tp;
        scc[s[tp]] = sc, sz[sc]++, --tp;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (scc[u] == scc[v])
                continue;
            out[scc[u]]++;
        }

    int ans = 0;
    for (int i = 1; i <= sc; i++)
        if (!out[i])
            if (!ans)
                ans = i;
            else {
                cout << 0;
                return 0;
            }
    cout << sz[ans];
}