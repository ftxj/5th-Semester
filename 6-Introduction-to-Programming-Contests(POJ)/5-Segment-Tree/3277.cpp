#include <queue>  
#include <stack>  
#include <math.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>  
#include <limits.h>  
#include <string.h>  
#include <string>  
#include <algorithm>  
#define MID(x,y) ( ( x + y ) >> 1 )  
#define L(x) ( x << 1 )  
#define R(x) ( x << 1 | 1 )  
  
using namespace std;  
  
const long long MAX = 80100;  
struct Tnode{ long long l,r,h;};  
struct Sline{ long long x,y,h;};  
Tnode node[MAX<<2];  
Sline l[MAX<<1];  
long long x[MAX<<2];  
  
void init(){  
    memset(node,0,sizeof(node));  
}  
void Build(long long t,long long l,long long r){
    node[t].l = l; node[t].r = r;  
    node[t].h = 0;  
    if( l == r - 1 ) return ;  
    long long mid = MID(l,r);  
    Build(L(t),l,mid);  
    Build(R(t),mid,r);  
}  
  
void Updata(long long t,long long l,long long r,long long h){  
    if( h < node[t].h ) return ;  
    if( node[t].l >= l && node[t].r <= r ){  
        node[t].h = max(node[t].h,h);  
        return ;  
    }  
    if( node[t].l == node[t].r - 1 ) return ;  
    if( node[t].h > 0 ){  
        node[R(t)].h = node[L(t)].h = node[t].h;  
        node[t].h = 0;  
    }     
    long long mid = MID(node[t].l,node[t].r);  
    if( l <= mid )  Updata(L(t),l,r,h);  
    if( r > mid )  Updata(R(t),l,r,h);  
}  
  
long long Query(long long t,long long l,long long r) {  
    if( node[t].h > 0 )  
        return ( x[node[t].r] - x[node[t].l] )*1ll*node[t].h;  
    if( node[t].l == node[t].r - 1 ) return 0;  
    int mid = MID(node[t].l,node[t].r);  
    long long ans = 0ll;  
    if( l <= mid )  
        ans += Query(L(t),l,r);  
    if( r > mid )  
        ans += Query(R(t),l,r);  
    return ans;  
}  
long long solve(int n,int cnt){  
    init();  
    Build(1,0,cnt-1);  
    for(int i=0; i<n; i++){  
        long long xx = lower_bound(x,x+cnt,l[i].x) - x;  
        long long yy = lower_bound(x,x+cnt,l[i].y) - x;  
        Updata(1,xx,yy,l[i].h);  
    }  
    long long ans = Query(1,0,cnt-1);  
    return ans;  
}  
bool cmp(Sline a,Sline b) {  
    return a.h < b.h;  
}  
int main() {  
    int n;  
    while( ~scanf("%d",&n) ){  
        int cnt = 0;  
        for(int i=0; i<n; i++){  
            scanf("%lld%lld%lld",&l[i].x,&l[i].y,&l[i].h);  
            x[cnt++] = l[i].x; x[cnt++] = l[i].y;  
        }  
        sort(x,x+cnt);  
        sort(l,l+n,cmp);  
        cnt = unique(x,x+cnt) - x;  
        long long ans = solve(n,cnt);  
        printf("%lld\n",ans);  
    }  
    return 0;  
}  