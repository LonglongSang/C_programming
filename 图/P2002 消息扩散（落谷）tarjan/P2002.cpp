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
vector<int> nex[100001];
bool vis[100001];
int first[100001];
int early[100001];
int circle[100001];
int indeg[100001];
stack<int> S;
int cnt=1;
int circle_cnt=0;
void dfs(int ori){
    vis[ori]=true;
    S.push(ori);
    first[ori]=cnt;
    early[ori]=cnt++;
    //printf("vis:%d %d\n",ori,cnt);
    for(int i=0;i<nex[ori].size();i++){
        int b=nex[ori][i];
        if(first[b]==0){
            dfs(b);
            early[ori]=min(early[ori],early[b]);
        }else if(vis[b]){
            early[ori]=min(early[ori],first[b]);
        }
    }
    if(early[ori]==first[ori]){
        int temp;
        do{
            temp=S.top();
            S.pop();
            vis[temp]=false;
            circle[temp]=circle_cnt;
        }while(temp!=ori);
        circle_cnt++;
    }
}
int main() {
    int n,m;
    scanf("%d %d\n",&n,&m);
    int from,to;
    for(int i=0;i<m;i++){
        scanf("%d %d\n",&from,&to);
        nex[from].push_back(to);
    }
    for(int i=1;i<=n;i++){
        if(!first[i]) dfs(i);
    }
    //unordered_map<int,int> t;
    //for(int i=1;i<=n;i++){
    //    t[early[i]]++;
    //    printf("%d %d\n",i,circle[i]);
    //}
    for(int i=1;i<=n;i++){
        for(int j=0;j<nex[i].size();j++){
            if(circle[i] != circle[nex[i][j]]){
                indeg[circle[nex[i][j]]]++;
            }
        }
    }
    int ans=0;
    //unordered_map<int,int>::iterator it;
    //for(it = t.begin(); it != t.end(); it++){
    //    ans+= it->second*(it->second-1)/2;
   //}
    for(int i=0;i<circle_cnt;i++) if(indeg[i]==0) ans++;
    //printf("%d\n",t.size());
    printf("%d\n",ans);
    return 0;
}