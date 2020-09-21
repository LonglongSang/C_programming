#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <stack>
//#10091. 「一本通 3.5 例 1」受欢迎的牛
//https://loj.ac/problem/10091#submit_code
//思想，先tarjan算法求强连通向量个数，然后对强连通向量进行Flody算法
using namespace std;
vector<int> nex[10001];
bool vis[10001];
int first[10001];
int early[10001];
int circle[10001];
stack<int> S;
int cnt=1;
int circle_cnt=0;
void tarjan(int ori){
    vis[ori]=true;
    S.push(ori);
    first[ori]=cnt;
    early[ori]=cnt++;
    for(int i=0;i<nex[ori].size();i++){
        int b=nex[ori][i];
        if(first[b]==0){
            tarjan(b);
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
        if(!first[i]) tarjan(i);
    }
    int t[circle_cnt];
    fill(t,t+circle_cnt,0);
    for(int i=1;i<=n;i++) t[circle[i]]++;
    //for(int i=0;i<circle_cnt;i++) printf("%d\n",t[i]);
    
    bool dist[circle_cnt][circle_cnt];
    //printf("%d\n",circle_cnt);
    
    fill(&dist[0][0],&dist[0][0]+circle_cnt*circle_cnt,0);
    
    for(int i=0;i<circle_cnt;i++) dist[i][i]=true;
    
    for(int i=1;i<=n;i++){
        for(int j=0;j<nex[i].size();j++){
            if(circle[i] != circle[nex[i][j]]){
                dist[circle[i]][circle[nex[i][j]]]=true;
            }
        }
    }
    
    for(int k=0;k<circle_cnt;k++){
        for(int i=0;i<circle_cnt;i++){
            if(!dist[i][k]) continue;
            for(int j=0;j<circle_cnt;j++){
                if(!dist[k][j]) continue;
                dist[i][j]=true;
            }
        }
    }
    int ans=0;
    for(int i=0;i<circle_cnt;i++){
        bool good=true;
        for(int j=0;j<circle_cnt;j++){
            if(!dist[j][i]){
                good=false;
                break;
            }
        }
        if(good){
            ans += t[i];
        }
    }
    
    //printf("%d\n",t.size());
    printf("%d\n",ans);
    return 0;
}