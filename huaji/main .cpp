#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define SPEED 6
#define KUANG 60
#define GAO 60

RECT rect;
POINT p;

void gotoxy(int x, int y)
{
	COORD zb;
	zb.X = x - 1;
	zb.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), zb);
}

int main()
{
	system("color f0");

	HWND hwnd = GetConsoleWindow();//获取窗口句柄
	HDC hdc = GetDC(hwnd);//获取窗口DC
	GetWindowRect(hwnd, &rect);//获取窗口宽高
	HBITMAP hbitmap =
		(HBITMAP)::
		LoadImage(NULL, "huaji.bmp", IMAGE_BITMAP, KUANG, GAO, LR_LOADFROMFILE);
	//载入图片
	HDC comp_hdc = CreateCompatibleDC(hdc);//创建内存DC
	SelectObject(comp_hdc, hbitmap);//选择图片

	int width = rect.right - rect.left;//窗口宽度
	int height = rect.bottom - rect.top;//窗口高度

	int i = width / 2;//图片横坐标
	int j = height / 2;//图片纵坐标

	int move_right = 0;
	int move_down = 0;

	RECT image_rect;
	image_rect.left = 0;
	image_rect.right = 0;
	image_rect.top = 0;
	image_rect.bottom = 0;

	BitBlt(hdc, i, j, KUANG, GAO, comp_hdc, 0, 0, SRCCOPY);//进行位块转换
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));//笔刷颜色

	HANDLE gb = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(gb, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false;//隐藏控制台光标
	SetConsoleCursorInfo(gb, &CursorInfo);//隐藏控制台光标

	while (1)
	{
		GetWindowRect(hwnd, &rect);//获取窗口宽高
		width = rect.right - rect.left;//窗口宽度
		height = rect.bottom - rect.top;//窗口高度

		gotoxy(6, 3);
		printf("x:%5d   y:%5d", p.x, p.y);
		gotoxy(6, 6);
		printf("x:%5d   y:%5d", i + rect.left, j + rect.top);

		GetCursorPos(&p);//获取光标坐标

		if (!(i > 0 && i < width - 2 * KUANG && j > 0 && j < height - 2 * GAO))
		{
			if (i < 0)
			{
				move_right = 1;
			}
			else if(i > width - 2 * KUANG)
			{
				move_right = 0;
			}
			if (j < 0)
			{
				move_down = 1;
			}
			else if (j > height - 2 * GAO)
			{
				move_down = 0;
			}
		}
		else
		{
			if (p.x > rect.left + i)
			{
				move_right = 1;
			}
			else
			{
				move_right = 0;
			}
			if (p.y > rect.top + j)
			{
				move_down = 1;
			}
			else
			{
				move_down = 0;
			}
		}

		FillRect(hdc, &image_rect, brush);//使用指定的刷子填充矩形
		image_rect.left = i;
		image_rect.right = i + KUANG;
		image_rect.top = j;
		image_rect.bottom = j + GAO;
		BitBlt(hdc, i, j, KUANG, GAO, comp_hdc, 0, 0, SRCCOPY);//进行位块转换

		if (move_right)
		{
			i += SPEED;
		}
		else
		{
			i -= SPEED;
		}
		if (move_down)
		{
			j += SPEED;
		}
		else
		{
			j -= SPEED;
		}

		Sleep(10);
	}

	ReleaseDC(hwnd, hdc);//释放内存DC

	return 0;
}