
#define front_exist
#include "func.h"

ull rand64()
{
    return (ull)rand() | ((ull)rand()<<15) | ((ull)rand()<<30) | ((ull)rand()<<45) | ((ull)rand()<<60);
}
int get_command()
{
    int input=getch(),to;
    switch(input)
    {
        case '1': to=1; break;
        case '2': to=2; break;
        case '3': to=3; break;
        case '4': to=4; break;
        case '0': to=0; break;
        default : to=-1; break; 
    }
    return to;
}
int get_toward()
{
    int input=getch(),to=0;
    switch(input)
    {
        case 'w': to=1; break;
        case 's': to=2; break;
        case 'a': to=3; break;
        case 'd': to=4; break;
        case 13: to=5; break;
        case 'p': to=6; break;
        case '0': to=0; break; //退出程序
        case 224:
        {
            input=getch();
            switch(input)
            {
                case 72: to=1; break;
                case 80: to=2; break;
                case 75: to=3; break;
                case 77: to=4; break;
            }
            break; 
        }
        default : to=-1; break; 
    }
    return to;
}

struct Inform{ int i,j,val,tmp; }info[N1]; int inf_cnt=0;
void push_inform(int i,int j,ll val,ll tmp)
{
    inf_cnt++;
    info[inf_cnt]=(Inform){i,j,val,tmp};
}
void inform_out()
{
    FILE *fout; fout = fopen("infrom.out","w");
    for(int i=1;i<=inf_cnt;i++)
    {
        fprintf(fout,"%d %d %d %d\n",info[i].i,info[i].j,info[i].val,info[i].tmp);
    }
    fclose(fout);
}

int inputmap()
{
    FILE *fout; fout = fopen("curmap.out","r");
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) 
    {
        fscanf(fout,"%d",&realmap[i][j]);
        if(realmap[i][j]==2) realmap[i][j]=-1;
        else if(realmap[i][j]==3) nx=i, ny=j, realmap[i][j]=0;
    }
    fclose(fout);
    // return -1;
    return 1;
}
void savecurmap()
{
    // freopen("curmap.out","w",stdout);
    FILE *fout; fout = fopen("curmap.out","w");
    char outstr[5];
    for(int i=1;i<=n;i++,fprintf(fout,"\n")) 
    {
        for(int j=1;j<=n;j++)
        {
            if(realmap[i][j]<0) fprintf(fout,"2 ");
            else fprintf(fout,"%d ",realmap[i][j]); 
        }
    }
    fclose(fout);
}
clock_t time_now,time_pre,time_calc[2];
void printmap(int mp[17][17],int n,int id)
{
    int fl=0;
    char outstr[10]; 
    time_now=clock(); 
    time_calc[id] += time_now-time_pre; time_pre=time_now;
    for(int i=0;i<2;i++)
    {
        sprintf(outstr,"Player%d: %.7lfs\n",i+1,(double)(time_calc[i])/CLOCKS_PER_SEC);
        dprintf(outstr,0,FB|FG|FR|FI,0,0);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(idmap[i][j]<=9) sprintf(outstr," %d",idmap[i][j]);
            else sprintf(outstr,"%d",idmap[i][j]);
            
            switch(mp[i][j])
            {
                case -1 : dprintf(outstr,0,0,BB|BG|BR|BI,fl); break;
                case 0  : dprintf("  ",0,0,BB|BR,fl); break;
                case 1  : dprintf(outstr,0,FB|FG|FR|FI,0,fl); break;
                
                case 2  : dprintf(outstr,0,0,BB|BG|BR|BI,fl); break;
                case 3  : dprintf("  ",0,0,BG,fl); break;
                case 4  : dprintf(outstr,0,FB|FG|FR|FI,0,fl); break;

            }
            //没有数字但是有棋子的界面
            // switch(mp[i][j])
            // {
            //     case -1 : dprintf("● ",0,FB|FG|FR|FI,BB|BR,fl); break;
            //     case 0  : dprintf("  ",0,0,BB|BR,fl); break;
            //     case 1  : dprintf("● ",0,0,BB|BR,fl); break;
                
            //     case 2  : dprintf("● ",0,FB|FG|FR|FI,BG,fl); break;
            //     case 3  : dprintf("  ",0,0,BG,fl); break;
            //     case 4  : dprintf("● ",0,0,BG,fl); break;

            // }
        }
        if(i==n) fl=1;
        dprintf("\n",0,0,BB|BR,fl);
    }
}
void outputcurmap()
{
    char outstr[5];
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=n;j++)
        {
            sprintf(outstr,"%d ",realmap[i][j]); 
            dprintf(outstr,0,FG|FB|FR|FI,0,0);
        }
        dprintf("\n",0,FG|FB|FR|FI,0,i==n?1:0);
    }
}


int outmap[M1][M1];
int fx[6] = {0,-1,1,0,0,0}, fy[6] = {0,0,0,-1,1,0}; //*wsad

int checkposition(int x,int y)
{
    if(1<=x && x<=m && 1<=y && y<=m) return 1;
    return 0;
}
int checkchess(int x,int y)
{
    if(1<=x && x<=m && 1<=y && y<=m) return 1;
    return 0;
}

void place_piece(int mp[M1][M1],int now,int n)
{
    int to;
    // memcpy(outmap,mp,sizeof(outmap)); outmap[nx][ny]+=3;
    mp[nx][ny]+=3;
    printmap(mp,n,now==1?0:1);
    while(1)
    {
        to = get_toward();
        if(to==6){ savecurmap(); continue; }
        if(!checkposition(nx+fx[to],ny+fy[to])) continue;
        memcpy(outmap,mp,sizeof(outmap));
        if(1<=to && to<=4){
            mp[nx][ny]-=3;
            nx+=fx[to], ny+=fy[to];
            mp[nx][ny]+=3;
            printmap(mp,n,now==1?0:1);
        }else if(to==5){
            if(mp[nx][ny]==3){
                mp[nx][ny]=now+3;
                return;
            }else{
                continue;
            }
        }else continue;
    }
}
