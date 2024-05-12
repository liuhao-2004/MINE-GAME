#define _CRT_SECURE_NO_WARNINGS 1
include <stdio.h>
include <stdlib.h>
include <time.h>
include <graphics.h>
pragma comment(lib,"winmm.lib")

define ROW 15//行
define COL 15//列
define ROWS ROW+2
define COLS COL+2
define SUM 25//雷的个数
define SIZE 35


int count = 0;//点开的个数
int mine[ROWS][COLS];//定义二维数组
IMAGE img[12];//存放12张图片


//初始化函数
void initmine()//数组赋值为0
{
	srand((unsigned int)time(NULL));//随机数
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			mine[i][j] = 0;
		}
	}



	//布雷，-1表示雷，SUM个雷
	
	int num = SUM;
	while (num)
	{
		//随机行和列
		int x = rand() % ROW +1 ;
		int y = rand() % COL +1;
		if (mine[x][y]==0)
		{
			mine[x][y] = -1;
			num--;
		}
	}





	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)//遍历数组
		{
			if (mine[i][j] != -1)//找到不为雷的元素
			{
				//遍历九宫格
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (mine[m][n] == -1)//找到一个雷
						{
							mine[i][j]++;
						}
					}
				}
			}
		}
	}


	//简单的加密
	for (int i = 1; i < ROW + 1; i++)
	{
		for (int j = 1; j < COL + 1; j++)
		{
			mine[i][j] += 20;
		}
	}

}


void gameDraw()//打印数组
{
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			printf("%d ",mine[i][j]);
			if (mine[i][j]==-1)
			{
				putimage((i-1)*SIZE,(j-1)*SIZE,&img[9]);//雷的图片
			}
			else if (mine[i][j] >= 0 && mine[i][j] <= 8)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[mine[i][j]]);//数字的图片
			}
			else if (mine[i][j] >= 19 && mine[i][j] <= 28)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[10]);//空白图片
			}
			else if (mine[i][j]>30)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[11]);//标记图片
			}
		}
		printf("\n");
	}
}

void OpenZeio(int r,int c)
{
	//先打开格子
	mine[r][c] -= 20;
	count++;
	//辅助区为0，不能动
	for (int m = r - 1; m <= r+1; m++)
	{
		for (int n = c - 1; n <= c + 1; n++)//九宫格
		{
			if (m >= 1 && m <= ROW && n>=1 && n <= COL)//游戏区的内容
			{
				if (mine[m][n] >= 19 && mine[m][n] <= 28)//空白的
				{
					if (mine[m][n]!=20)
					{
						mine[m][n] -= 20;
						count++;
					}
					else
					{
						OpenZeio(m,n);
					}
				}
			}
		}
	}
}


int PlayGame()
{
	//定义一个鼠标消息
	MOUSEMSG msg = {0};
	int r, c;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://翻开扫雷  空白照片  19-28
			r = msg.x / SIZE + 1;
			c = msg.y / SIZE + 1;
			if (mine[r][c]>=19&&mine[r][c]<=28)
			{
				if (mine[r][c] == 20)//点到的是0
				{
					OpenZeio(r,c);
					
				}
				else
				{
					mine[r][c] -= 20;//-1 -- 8
					count++;
				}
			}
			return mine[r][c];//-1 -- 8
			break;
		case WM_RBUTTONDOWN://标记一个空白图片 取消一个标记图片 
			r = msg.x / SIZE + 1;
			c = msg.y / SIZE + 1;
			if (mine[r][c] >= 19 && mine[r][c] <= 28)
			{
				mine[r][c] += 50;//>30
			}
			else if (mine[r][c]>30)
			{
				mine[r][c] -= 50;
			}
			return mine[r][c];
			break;
		}
	}
}


int main()
{
	//打开一个图像窗口
	HWND hwnd = initgraph(ROW*SIZE,COL*SIZE,SHOWCONSOLE);
	mciSendString(L"open music.mp3 alias music",0,0,0);
	mciSendString(L"play music", 0, 0, 0);
	//加载图片
	loadimage(&img[0], L"0.jpg", SIZE, SIZE);
	loadimage(&img[1], L"1.jpg", SIZE, SIZE);
	loadimage(&img[2], L"2.jpg", SIZE, SIZE);
	loadimage(&img[3], L"3.jpg", SIZE, SIZE);
	loadimage(&img[4], L"4.jpg", SIZE, SIZE);
	loadimage(&img[5], L"5.jpg", SIZE, SIZE);
	loadimage(&img[6], L"6.jpg", SIZE, SIZE);
	loadimage(&img[7], L"7.jpg", SIZE, SIZE);
	loadimage(&img[8], L"8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"9.jpg", SIZE, SIZE);
	loadimage(&img[10], L"10.jpg", SIZE, SIZE);
	loadimage(&img[11], L"11.jpg", SIZE, SIZE);
	initmine();
	while (1)
	{
		gameDraw();
		if (PlayGame() == -1)
		{
			gameDraw();
			MessageBox(hwnd,L"你失败了！！",L"",MB_OK);
			break;
		}
		if (ROW * COL - SUM == count)
		{
			gameDraw();
			MessageBox(hwnd, L"你赢了！！", L"", MB_OK);
			break;
		}
	}
	return 0;
}
