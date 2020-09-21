//没通过，不知道哪里错了
//题目P3388 【模板】割点（割顶）
//链接：https://www.luogu.com.cn/record/38344432
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>
//#include <unordered_map>
#include <cstring>
#define min(a,b) (a>b?b:a)
using namespace std;
const int N=2e4+5;
const int M=2e5+5;
int dfn[N],low[N],head[N],nex[M],to[M];
bool is_gedian[N];
int from,des,cnt,n,m,root,ans;
inline void add(){
    to[++cnt]=des;
    nex[cnt]=head[from];
    head[from]=cnt;
    
    to[++cnt]=from;
    nex[cnt]=head[des];
    head[des]=cnt;    
}
void tarjan(int cur){
    dfn[cur]=++cnt;
    low[cur]=cnt;
    int son=0;
    for(int i=head[cur];i;i=nex[i]){
        int want=to[i];
        if(!dfn[want]){
            tarjan(want);
            low[cur]=min(low[cur],low[want]);
            son++;
            if(!is_gedian[cur] && ((cur==root && son>1) || (cur!=root && low[want]>=dfn[cur]))){
                is_gedian[cur]=true;
                ans++;
            }
        }else{
            low[cur]=min(low[cur],dfn[want]);
        }
    }
}
int main(){
    scanf("%d %d\n",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d\n",&from,&des);
        add();
    }
    cnt=0;
    int temp=0;
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            root=i;
            tarjan(i);
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(is_gedian[i]){
            if(temp) printf(" %d",i);
            else printf("%d",i);
            temp++;
        } 
    }
    printf("\n");
    return 0;
}
	