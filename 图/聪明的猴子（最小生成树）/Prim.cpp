//题目httpswww.luogu.com.cnproblemP2504
#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int monkey[505];
bool vis[1005];
struct pos{
    int x;
    int d;
};
struct cmp{
    bool operator()(pos&a,pos&b){
        return a.d>b.d;
    }
};
int temp[1001][2];
int dist[1000][1000];
int main() {
    int n,m;//树的个数，猴子的个
    int a,b;
    scanf("%d\n",&m);
    for(int i=0;i<m;i++){
        scanf("%d",monkey+i);
        getchar();
    }
    scanf("%d\n",&n);
    for(int i=0;i<n;i++){
        scanf("%d %d\n",&temp[i][0],&temp[i][1]);
    }
    int size=n*(n-1)/2;
    int cnt=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            dist[i][j]=(temp[i][0]-temp[j][0])*(temp[i][0]-temp[j][0])+(temp[i][1]-temp[j][1])*(temp[i][1]-temp[j][1]);
            dist[j][i]=dist[i][j];
        }
    }
    cnt=0;
    int big=0;
    priority_queue< pos, vector<pos>, cmp> heap;
    heap.push({0,0});
    pos cur;
    while(cnt!=n){
        cur=heap.top();
        heap.pop();
        if(vis[cur.x])continue;//重要
        vis[cur.x]=true;
        big = max(big,cur.d);
        cnt++;
        big=max(big,cur.d);
        for(int i=0;i<n;i++){
            if(!vis[i]){
                heap.push({i,dist[cur.x][i]});
            }
        }
    }
    int ans=0;
    for(int i=0;i<m;i++){
       if(monkey[i]*monkey[i]>=big) ans++;
    }
    printf("%d\n",ans);
    return 0;
}