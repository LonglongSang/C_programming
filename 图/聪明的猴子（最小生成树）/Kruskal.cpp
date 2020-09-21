	//题目httpswww.luogu.com.cnproblemP2504
#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int monkey[505];
int tree_par[1005];
int find_par(int a){
    if(tree_par[a] == -1) return a;
    else return find_par(tree_par[a]);
}
bool uni(int a,int b){
    int x=find_par(a);
    int y=find_par(b);
    if(x!=y){
        tree_par[x]=y;
        return true;
    }else{
        return false;
    }
}

struct pos{
    int from;
    int to;
    int dist;
};
int temp[1001][2];
int main() {
    int n,m;//树的个数，猴子的个
    int a,b;
    scanf("%d\n",&m);
    for(int i=0;i<m;i++){
        scanf("%d",monkey+i);
        getchar();
    }
    
    scanf("%d\n",&n);
    fill(tree_par,tree_par+n,-1);
    
    for(int i=0;i<n;i++){
        scanf("%d %d\n",&temp[i][0],&temp[i][1]);
    }
    int size=n*(n-1)/2;
    pos dp[size];
    int cnt=0;
    
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            dp[cnt].from=i;
            dp[cnt].to=j;
            dp[cnt++].dist=(temp[i][0]-temp[j][0])*(temp[i][0]-temp[j][0])+(temp[i][1]-temp[j][1])*(temp[i][1]-temp[j][1]);
        }
    }
    sort(dp,dp+size,[](pos &a,pos &b){
      return a.dist<b.dist;  
    });
    cnt=0;
    int compare[n-1];
    int big=0;
    for(int i=0;i<size;i++){
        if(uni(dp[i].from,dp[i].to)){
            compare[cnt++]=dp[i].dist;
            big=max(big,dp[i].dist);
        }
        if(cnt==n-1) break;
    }
    int ans=0;
    for(int i=0;i<m;i++){
       if(monkey[i]*monkey[i]>=big) ans++;
    }
    printf("%d\n",ans);
    return 0;
}