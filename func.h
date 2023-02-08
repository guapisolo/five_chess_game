#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <unordered_map>
// #include <tr1/unordered_set>
// #include <tr1/unordered_map>
#include <algorithm>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define ull unsigned long long
#define ll int 
#define dd double 
#define itm unordered_map<ull,int>::iterator
// using namespace std::tr1;
using namespace std;

#define FG FOREGROUND_GREEN
#define FR FOREGROUND_RED
#define FB FOREGROUND_BLUE
#define FI FOREGROUND_INTENSITY
#define BG BACKGROUND_GREEN
#define BR BACKGROUND_RED
#define BB BACKGROUND_BLUE
#define BI BACKGROUND_INTENSITY
#define dd double

const int n=15, N1=17, inf=0x3f3f3f3f, eps=15000;
const int M1=17, m=15;

//func in AI.cpp
// #ifndef AI_exist
extern int checkwinner();
extern void PLAY(int type,int now);
extern ull rand64();
extern void zobinit();
// #endif

//func in db.cpp
// #ifndef DB_exist
extern void dprintf(const char *s,int len,int Foreground_color,int Background_color,int is_end);
extern void initconsolveScreenBuffer();
// #endif

//func in front.cpp
// #ifndef front_exist
extern int get_command();
extern int get_toward();
extern int inputmap();
extern void savecurmap();
extern void outputcurmap();
extern void printmap(int mp[17][17],int n,int id);
extern void place_piece(int mp[M1][M1],int now,int n);
extern void push_inform(int i,int j,ll val,ll tmp);
extern void inform_out();
// #endif

struct ChessMap{ int a[17][17]; };
extern ChessMap cur[N1];
extern int realmap[N1][N1];
extern int nx,ny;
extern int idmap[N1][N1];

//想定义一个全局变量结果报错，发现是在头文件中定义，却没有在别的.c文件中初始化。

// extern struct ChessMap{ int a[N1][N1]; }cur[N1];
