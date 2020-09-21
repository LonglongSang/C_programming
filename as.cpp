#include <vector>
#include <algorithm>
#include <stdio.h>
#include <queue>
#include <bitset>
#include <map>
#include <iostream>
#include <stack>
using namespace std;
inline void swap(int *a,int *b){
    *a+=*b;
    *b=*a-*b;
    *a-=*b;
}
void quicksort(int *arr,int low,int high){
    stack< pair<int,int> > S;
    S.push(make_pair(low,high));
    pair<int,int> cur;
    while(!S.empty()){
        cur=S.top();
        S.pop();
        low=cur.first,high=cur.second;
        if(low>=high) continue;
        int pivot=arr[low];
        while(high>low){
            while(high>low && arr[high]>=pivot) high--;
            if(high>low) swap(&arr[high],&arr[low]);
            while(high>low && arr[low]<pivot) low++;
            if(high>low) swap(&arr[high],&arr[low]);
        }
		arr[low]=pivot;
        S.push(make_pair(cur.first,low-1));
        S.push(make_pair(low+1,cur.second));
    }
}
void quicksort1(int *arr,int low,int high){
	int pivot=arr[low];
    while(high>low){
        while(high>low && arr[high]>=pivot) high--;
        if(high>low) swap(&arr[high],&arr[low]);
        while(high>low && arr[low]<pivot) low++;
        if(high>low) swap(&arr[high],&arr[low]);
    }
	
	//return low;
}
int main()
{   
    int size=100000000;
    int *a=(int *)malloc(sizeof(int)*size);
    for(int i=0;i<size;i++) a[i]=(int)rand()%1000000000;
    //quicksort(a,0,size-1);
    free(a);
    //for(int i=0;i<size;i++) printf("%d ",a[i]);
	printf("yes\n");
	return 0;
}




