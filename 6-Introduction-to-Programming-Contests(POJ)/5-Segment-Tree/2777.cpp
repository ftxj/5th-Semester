#include <cstdio>  
#include <cstring>  
#include <algorithm>
#define MAXN 101000
using namespace std;  
  
int lazy[MAXN << 2];  
int color[MAXN << 2];  
void PushUp(int rt){  
    color[rt] = color[rt<<1] | color[rt<<1|1];
}  
void PushDown(int rt,int m) {  
    if(lazy[rt]) {  
        lazy[rt<<1] = lazy[rt];  
        lazy[rt<<1|1] = lazy[rt];  
        color[rt<<1] = lazy[rt];  
        color[rt<<1|1] = lazy[rt];  
        lazy[rt] = 0;
    }  
}  
void build(int l,int r,int rt) {  
    lazy[rt] = 0;
    if (l == r)  {  
        color[rt] = 1;
        return ;  
    }  
    int mid = (l + r) >> 1;  
    build(l , mid , rt << 1);  
    build(mid + 1 , r , rt << 1 | 1);  
    PushUp(rt);  
}  
void update(int L,int R,int c,int l,int r,int rt){  
    if (L <= l && r <= R){  
        lazy[rt] =1<<(c-1);
        color[rt] =1<<(c-1);  
        return ;  
    }  
    PushDown(rt , r - l + 1);
    int mid = (l + r) >> 1;  
    if (L <= mid)  
        update(L , R , c , l , mid , rt << 1);
    if (mid < R)  
        update(L , R , c , mid + 1 , r , rt << 1 | 1);
    PushUp(rt);  
}  
int query(int L,int R,int l,int r,int rt){  
    if (L <= l && r <= R){  
        return color[rt];  
    }  
    PushDown(rt , r - l + 1);  
    int mid = (l + r) >> 1;  
    int ret = 0;  
    if (L <= mid)  
        ret |= query(L , R , l , mid , rt << 1);  
    if (mid < R)  
        ret |= query(L , R , mid + 1 , r , rt << 1 | 1  );  
    return ret;  
}  
void swap(int &a, int &b){
  int t = a;
  a = b;
  b = a;
}
int main(){  
  int L, T, Q;  
  int a, b, c;  
  while(~scanf("%d%d%d",&L,&T,&Q)){  
    build(1, L, 1);
    while(Q--){  
      char op[2];  
      scanf("%s", &op);  
      if(op[0] == 'P'){  
        scanf("%d %d", &a, &b);  
        if(a > b) swap(a, b);
        int tt=query(a, b, 1, L, 1);  
        int ans = 0;  
        while(tt){  
            if(tt & 1) ans++;
            tt >>= 1;  
        }  
        printf("%d\n",ans);  
      }  
      else{  
        scanf("%d %d %d",&a,&b,&c);  
        if(a > b) swap(a, b);
        update(a, b, c, 1, L, 1);  
      }  
    }  
  }  
  return 0;  
}  