#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define LINE 15
#define ROL 15
#define TIME 800
//打印地图和，角色和目标
void role_move(char init[LINE][ROL],int x,int y,int _x,int _y,int *ret) {
    for(int i=0; i<x; ++i) {
        for(int j=0; j<y; ++j) {
            if(i==_x&&j==_y) {
                printf("%c",init[i][j]='p');
            } else if(i==ret[0]&&j==ret[1]) {
                printf("%c",init[ret[0]][ret[1]]='*');
            } else {
                printf("%c",init[ret[0]][ret[1]]='.');
            }
        }
        printf("\n");
    }
}
void clearScreen() {
    system("cls");//windows清屏
}
//初始化地图
void init_role(int init[LINE][ROL],int x,int y,int *ret) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            init[i][j]='.';
        }
    }
}
int main() {
    //初始化地图大小，角色位置，目标位置
    char init[LINE][ROL] = { '\0' };
    int line = LINE;
    int rol = ROL;
    int x_location = 0;
    int y_location = 0;
    srand((unsigned)time(NULL));
    int x=rand()%line;
    int y=rand()%rol;
    int target[2]= {x,y};
    char key = '\0';
	//游戏主循环
    while(1) {
        clearScreen();
        role_move(init,line,rol,x_location,y_location,target);
        key=_getch();
        switch(key) {
        case 'a':
            y_location--;
            if(y_location<0) {
                y_location=rol-1;
            }
            break;
        case 'd':
            y_location++;
            if(y_location>rol-1) {
                y_location=0;
            }
            break;
        case 'w':
            x_location--;
            if(x_location<0) {
                x_location=line-1;
            }
            break;
        case 's':
            x_location++;
            if(x_location>line-1) {
                x_location=0;
            }
            break;
        case 'q':
            exit(0);
        default:
            break;
        }
        //判断角色与目标是否相遇，相遇目标则消失，并随机下一次目标位置
        if(x_location==x&&y_location==y) {
            //init_role(init,line,rol,target);
            x=rand()%line;
            y=rand()%rol;
            target[0]= x;
            target[1]=y;
        }
    }
    return 0;
}
