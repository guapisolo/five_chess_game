
#include "func.h"

// extern ChessMap cur[N1];
// extern struct ChessMap cur[N1];
// extern struct ChessMap *cur;

int main()
{
    // freopen("map.in","r",stdin);
    // freopen("curmap.out","r",stdin);
    srand(time(NULL));
    zobinit();
    int step=1; 
    // step=inputmap();
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    int to;
    initconsolveScreenBuffer();
    // PLAY(3,1);
    // trail = 1;
    while(1)
    {
        system("cls");
        puts("Press [1] to start a two-player battle");
        puts("Press [2] to play with computer with back hand");
        puts("Press [3] to play with computer with first move");
        puts("Press [4] to watch computer battle with itself");
        puts("Press [0] to exit");
        to=get_command();
        switch(to)
        {
            // case 1: two_player(); break;
            case 1: PLAY(0,step); Sleep(1000000); break;
            case 2: PLAY(1,step); Sleep(1000000); break;
            case 3: PLAY(2,step); Sleep(1000000); break;
            case 4: PLAY(3,step); Sleep(1000000); break;
        }
        if(to==0) break;
    }
    return 0;
}
