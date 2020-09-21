#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <stack>
//https://www.luogu.com.cn/problem/P2002
//思想，先tarjan算法求强连通向量个数，之后统计强连通向量入度为零的个数，然后输出
using namespace std;
const int N=1e5+10;
const int M=(1e5)*5+10;
int head[M],to[M],nex[M],dfn[N],low[N],S[N],circle[N];
bool vis[N];
int top,cnt,circle_cnt,jump;
void tarjan(int ori){
    vis[ori]=true;
    S[top++]=ori;
    dfn[ori]=++cnt;
    low[ori]=cnt;
    for(int i=head[ori];i;i=nex[i]){
        int b=to[i];
        if(!dfn[b]){
            tarjan(b);
            low[ori]=min(low[ori],low[b]);
        }else if(vis[b]){
            low[ori]=min(low[ori],dfn[b]);
        }
    }
    if(low[ori]==dfn[ori]){
        int temp;
        do{
            temp=S[--top];
            vis[temp]=false;
            circle[temp]=circle_cnt;
            
        }while(temp!=ori);
        circle_cnt++;
    }
}
struct edge{
    int from,to;
};
void add(int from,int to1){
    to[++jump]=to1;
    nex[jump]=head[from];
    head[from]=jump;
}
int main() {
    int n,m;
    scanf("%d %d\n",&n,&m);
    int from,to;
    edge e[m];
    for(int i=0;i<m;i++){
        scanf("%d %d\n",&e[i].from,&e[i].to);
        add(e[i].from,e[i].to);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    int t[circle_cnt];
    fill(t,t+circle_cnt,0);
    for(int i=0;i<m;i++){
        if(circle[e[i].from] != circle[e[i].to]){
            t[circle[e[i].to]]++;
        }
    }
    int ans=0;
    for(int i=0;i<circle_cnt;i++) if(t[i]==0) ans++;
    printf("%d\n",ans);
    return 0;
}