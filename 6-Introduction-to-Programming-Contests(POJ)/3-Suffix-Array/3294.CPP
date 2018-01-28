#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#define MAXM 1000
#define MAXN 100
using namespace std;

#define MEM(a,x) memset(a,x,sizeof(a))
#define N 1000005

int wa[N],wb[N],wsf[N],wv[N],sa[N];
int RANK[N],height[N],s[N],a[N];

int cmp(int *r,int a,int b,int k){
    return r[a]==r[b]&&r[a+k]==r[b+k];
}
void getsa(int *r,int *sa,int n,int m){
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++)  wsf[i]=0;
    for(i=0; i<n; i++)  wsf[x[i]=r[i]]++;
    for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
    for(i=n-1; i>=0; i--)  sa[--wsf[x[i]]]=i;
    p=1;
    j=1;
    for(; p<n; j*=2,m=p){
        for(p=0,i=n-j; i<n; i++)  y[p++]=i;
        for(i=0; i<n; i++)  if(sa[i]>=j)  y[p++]=sa[i]-j;
        for(i=0; i<n; i++)  wv[i]=x[y[i]];
        for(i=0; i<m; i++)  wsf[i]=0;
        for(i=0; i<n; i++)  wsf[wv[i]]++;
        for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
        for(i=n-1; i>=0; i--)  sa[--wsf[wv[i]]]=y[i];
        t=x;
        x=y;
        y=t;
        x[sa[0]]=0;
        for(p=1,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)? p-1:p++;
    }
}
void getheight(int *r,int n){
    int i,j,k=0;
    for(i=1; i<=n; i++)  RANK[sa[i]]=i;
    for(i=0; i<n; i++)
    {
        if(k)
            k--;
        else
            k=0;
        j=sa[RANK[i]-1];
        while(r[i+k]==r[j+k])
            k++;
        height[RANK[i]]=k;
    }
}

char str[N];
int len[105],Size,ans[N];
bool vis[105];

int check(int mid,int n,int k){
    int i,j;
    int Size = 0,cnt = 0;
    MEM(vis,false);
    for(i = 1; i<=n; i++){
        if(height[i]>=mid){
            for(j = 1; j<=k; j++){
                //把sa[i-1]或sa[i]所在的字符串给标记，同样的串不重复累加
                if(sa[i]>len[j-1]&&sa[i]<len[j]) cnt+=(vis[j]?0:1),vis[j]=true;
                if(sa[i-1]>len[j-1]&&sa[i-1]<len[j]) cnt+=(vis[j]?0:1),vis[j]=true;
            }
        }
        else{
            if(cnt>k/2) ans[++Size] = sa[i-1];
            cnt = 0;
            MEM(vis,false);
        }
    }
    if(cnt>k/2) ans[++Size] = sa[n];
    if(Size){
        ans[0] = Size;
        return 1;
    }
    return 0;
}

int main(){
    int n,k,i,j,flag = 0;
    while(~scanf("%d",&k),k){
        n = 0;
        Size = 0;
        for(i = 1; i<=k; i++){
            scanf("%s",str+n);
            for(; str[n]!='\0'; n++)
                s[n] = str[n];
            s[n] = '#'+i;
            len[++Size] = n;
            n++;
        }
        s[n-1] = 0;
        getsa(s,sa,n,255);
        getheight(s,n-1);
        int l=1,r=n,mid;
        while(l<=r){
            mid = (l+r)/2;
            if(check(mid,n,k)) l = mid+1;
            else r = mid-1;
        }
        if(flag)
            puts("");
        flag = 1;
        if(l==1)
            puts("?");
        else{
            for(i = 1; i<=ans[0]; i++){
                for(j = ans[i]; j<ans[i]+l-1; j++)
                    printf("%c",s[j]);
                puts("");
            }
        }
    }

    return 0;
}
