#define AI_exist
#include "func.h"

using namespace std;

int mp[N1][N1]; //0 empty   1 o   -1 x
int idmap[N1][N1];
// previous
int anxt[]={0, 40000000, 1000000, 400000, 50000, 100, 60, 3, 1};
int anow[]={0, 17000000, 120000, 3500, 3000, 120, 72, 5, 1};
// int anxt[]={0, 40000000, 1000000, 400000, 50000, 120, 30, 6, 1};
// int anow[]={0, 17000000, 120000, 3500, 3000, 100, 25, 4, 1};
int val[N1];
//val: 
// 1:连5
// 2:活4
// 3:冲4
// 4:活3
// 5:眠3
// 6:连续活2
// 7:散2
// 8:活1
int de;

namespace zob{
ull Rand[2][N1][N1];
unordered_map<ull,int>val;
ull hash(int mp[N1][N1])
{
    ull ans=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
    {
        switch(mp[i][j])
        {
            case 0: break;
            case 1: ans^=Rand[0][i][j]; break; 
            case -1: ans^=Rand[1][i][j]; break; 
        }
    }
    return ans;
}
//后期此函数已经被替换掉 无需每一次都重新对整个棋盘进行哈希
void updhash(ull &ha,int i,int j,int w) 
{
    switch(w)
    {
        case 0: break;
        case 1: ha^=Rand[0][i][j]; break; 
        case -1: ha^=Rand[1][i][j]; break; 
    }
}
int find(ull ha)
{
    itm k=val.find(ha);
    if(k==val.end()) return inf;
    return (*k).second;
}
};

void zobinit()
{
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
        zob::Rand[0][i][j]=rand64(), zob::Rand[1][i][j]=rand64();
}
namespace assess{
int end4[N1][N1], ed[N1] ,num[N1], o,x;

//连五
ll check1(int *row,int len) 
{
    ll ans=0; int fl;
    for(int i=1;i<=len;i++) 
    {
        fl=1; for(int j=0;j<5;j++) if(row[i+j]!=o){ fl=0; break; } 
        if(fl){ ans+=val[1]; i+=4; continue; }
    }
    return ans;
}
//连四 冲四
void check23(int *row,int len) 
{
    int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        //活四
        fl=1; 
        for(int j=0;j<4;j++) if(row[i+j]!=o){ fl=0; break; } 
        if(fl && (!row[i-1] || !row[i+4]) )
        {
            if(!row[i-1]) ed[i-1]=1;
            if(!row[i+4]) ed[i+4]=1;
            i+=4; continue;
        } 
        //冲四
        cnt=0; fl=1;
        for(int j=0;j<5;j++) 
            if(row[i+j]==o) cnt++;
            else if(row[i+j]==x){ fl=0; break; }
        if(!fl) continue;
        if(cnt==4)
        {
            for(int j=0;j<5;j++) 
            {
                if(!row[i+j]){ ed[i+j]=1; break; }
            }
            continue;
            // i+=4; continue;
        }
    }
    // return ans;
}
//活三 冲三 眠三
ll check45(int *row,int len)
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        //活三
        fl=1;
        for(int j=0;j<3;j++) if(row[i+j]!=o){ fl=0; break; }
        if(fl && !row[i-1] && !row[i+3]){ ans+=val[4]; continue; }
        
        //中空活三 眠三
        cnt=0; fl=1;
        for(int j=0;j<4;j++) 
            if(row[i+j]==o) cnt++;
            else if(row[i+j]==x){ fl=0; break; } 
        if(!fl) continue;
        // 不要跳不要跳不要跳
        if(cnt==3)
        {
            //双向活三威胁值更高，后续调整
            //中空活三
            if(!row[i-1] && !row[i+4]){ //_ o o _ o _ 
                ans+=val[4]/4;
                continue;
            }else if(!row[i-1] || !row[i+4]){ //_ o o _ o   or    o o o _ _
            //眠三
                ans+=val[5];
                continue;
            }
        }
        
    }
    return ans;
}
//二 一
//连续2的得分应该更高
ll check67(int *row,int len) 
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        fl=1; cnt=0;
        if(row[i]==o && row[i+1]==o) ans+=val[6];
        for(int j=0;j<6;j++) 
            if(row[i+j]==o){ cnt++; }
            else if(row[i+j]==x){ fl=0; break; }
        if(!fl) continue;
        if(cnt==2) ans+=val[7]; else if(cnt==1) ans+=val[8];
    }
    return ans;
}
ll Row(int *row,int len) 
{
    ll ans=0; 
    memset(ed,0,sizeof(ed));
    ans+=check1(row,len);
    check23(row,len);
    ans+=check45(row,len);
    ans+=check67(row,len);
    return ans;
}
const int L1=25;
int row[L1];
ll Direct(int cs,int rs,int px,int py)
{
    ll ans=0; 
    if(!(px==1&&py==0))
    for(int r=1;r<=n;r++)
    {
        row[0]=x; int cnt=1;
        for(int i=r,j=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,cnt++)
        {
            row[cnt]=mp[i][j]; 
        }
        for(int i=cnt;i<L1;i++) row[i]=x; // 堵
        ans+=Row(row,cnt);
        for(int i=r,j=1,k=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,k++)
        {
            if(ed[k]) 
                end4[i][j]=1;
        }
    }
    for(int c=cs;c<=n;c++)
    {
        row[0]=x; int cnt=1;
        for(int i=rs,j=c;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,cnt++)
        {
            row[cnt]=mp[i][j]; 
        }
        for(int i=cnt;i<L1;i++) row[i]=x; // 堵
        ans+=Row(row,cnt);
        for(int i=rs,j=c,k=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,k++)
        {
            if(ed[k]) 
                end4[i][j]=1;
        }
    }
    return ans;
}
ll Map()
{
    ll ans=0;
    memset(end4,0,sizeof(end4));
    if(mp[12][7]==-1)
        de=1;
    ans+=Direct(2,1,1,1); //向右下
    ans+=Direct(2,n,-1,1); //向右上
    ans+=Direct(n+1,0,0,1); //向右
    ans+=Direct(1,1,1,0); //向下
    num[4]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(end4[i][j]) num[4]++;
    if(num[4]>1) ans+=val[2]; else if(num[4]==1) ans+=val[3];
    return ans;
}
//   x: current player    o: next player  
ll totMap(ull ha,int now,int nxt) 
{
    ll ans = zob::find(ha);
    if(ans!=inf) return ans;
    // ll ans;
    memcpy(val,anow,sizeof(anow)); 
    o=now; x=nxt;
    ans=Map();
    
    //calc nxt
    memcpy(val,anxt,sizeof(anxt)); 
    o=nxt; x=now;
    ans-=Map();
    
    zob::val[ha]=ans;
    return ans;
}
};
//记录不同位置落子的结果信息

const int dfs_deep=7;
const int bfs_num=5;
struct Play{ int x,y; int val; }; 

//plan A: 迭代加深搜索，每次搜4个最优状态
int cmpmin(Play &s1,Play &s2)
{ return s1.val < s2.val; }
int cmpmax(Play &s1,Play &s2)
{ return s1.val > s2.val; }

int checkwinner();
void outputcurmap();
void savecurmap();

int step=0,lx=8,ly=8;
int posx, posy;
//改为 启发式搜索 + alpha-beta剪枝
ll AlphaBeta(int dep,int now,int Alpha,int Beta,ull ha)
{
    // check(now,nxt);
    ll threat, ma=-inf, tmp; 
    Play piece[N1*N1]; memset(piece,0,sizeof(piece)); int pcnt=0;
    //malloc
    int tx=0,ty=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!cur[dep-1].a[i][j]) 
    {
        memcpy(mp,cur[dep-1].a,sizeof(mp)); mp[i][j]=now;
        zob::updhash(ha,i,j,now);
        threat = assess::totMap(ha,now,-now);
        zob::updhash(ha,i,j,now);
        if(threat>ma) tx = i, ty = j;
        ma = max(ma,threat); 
        piece[++pcnt] = (Play){i,j,threat}; //记录当前落子的估值
    }
    //threat：当前局面评分 越高越好
    //对 对手威胁值 最大 
    sort(piece+1,piece+pcnt+1,cmpmax);
    int id=0;
    if( ma <= -anxt[4]+eps || ma >= anow[2]-eps )
    {
        if(dep==1) posx = tx, posy = ty;
        return ma;
    }
    if(dep==dfs_deep) return ma;
    //一些提升可调试性的随机化，可有可无
    // if(step<8) 
    // {
    //     int fl=rand()%10;
    //     if(fl==0) swap(piece[4],piece[6]);
    //     if(fl==1) swap(piece[5],piece[7]);
    // }
    for(int k=1;k <= bfs_num+(step>=8?(step-8)/6:0);k++)
    {
        int i = piece[k].x, j = piece[k].y;
        memcpy(cur[dep].a,cur[dep-1].a,sizeof(mp)); cur[dep].a[i][j]=now;
        zob::updhash(ha,i,j,now);
        tmp = -AlphaBeta(dep+1,-now,-Beta,-Alpha,ha);
        zob::updhash(ha,i,j,now);
        if(tmp >= Beta) return Beta;
        if(tmp > Alpha){
            Alpha = tmp;
            id = k;
        } 
    }
    if(dep==1)
    { 
        if(Alpha <= -anxt[4]+eps) id=1;
        posx = piece[id].x; posy = piece[id].y; 
    }
    return Alpha;
}

ull now_map_hash;
int computer_move(int now)
{
    int id = AlphaBeta(1,now,-inf,inf,now_map_hash);
    realmap[posx][posy] = now;
    idmap[posx][posy]=++step;
    printmap(realmap,n,now==1?0:1);
    nx = posx, ny = posy;
    zob::updhash(now_map_hash,nx,ny,now);
    
    inform_out();
    int fl = checkwinner(); if(fl) return fl;
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    return 0;
}
int player_move(int now)
{
    place_piece(realmap,now,n);
    realmap[nx][ny] = now;
    idmap[nx][ny]=++step;
    zob::updhash(now_map_hash,nx,ny,now);
    printmap(realmap,n,now==1?0:1);
    int fl = checkwinner(); if(fl) return fl;
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    return 0;
}

int tmp;
void PLAY(int type,int now)
{
    if((type&1)) tmp = computer_move(now);
    else tmp = player_move(now);
    if(tmp) return;
    if((type&2)) tmp = computer_move(-now);
    else tmp = player_move(-now);
    if(tmp) return;
    if(tmp)
    {
        Sleep(100000);
        de=1;
    }
    PLAY(type, now);
}

int checkwinner() //O(map)
{
    memcpy(mp,realmap,sizeof(mp)); 
    memcpy(val,anxt,sizeof(anxt)); assess::o=-1; assess::x=1;
    ll nval = assess::Map();
    if(nval >= anxt[1]-eps) return -1;
    
    memcpy(val,anxt,sizeof(anxt)); assess::o=1; assess::x=-1;
    nval = assess::Map();
    if(nval >= anxt[1]-eps) return 1;
    
    return 0;
}

#ifdef __AI_H
int main()
{
    freopen("a.in","r",stdin);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&realmap[i][j]);
    initconsolveScreenBuffer();
    printmap(realmap,n);
    return 0;
}
#endif
