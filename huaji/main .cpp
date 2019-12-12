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

	HWND hwnd = GetConsoleWindow();//��ȡ���ھ��
	HDC hdc = GetDC(hwnd);//��ȡ����DC
	GetWindowRect(hwnd, &rect);//��ȡ���ڿ��
	HBITMAP hbitmap =
		(HBITMAP)::
		LoadImage(NULL, "huaji.bmp", IMAGE_BITMAP, KUANG, GAO, LR_LOADFROMFILE);
	//����ͼƬ
	HDC comp_hdc = CreateCompatibleDC(hdc);//�����ڴ�DC
	SelectObject(comp_hdc, hbitmap);//ѡ��ͼƬ

	int width = rect.right - rect.left;//���ڿ��
	int height = rect.bottom - rect.top;//���ڸ߶�

	int i = width / 2;//ͼƬ������
	int j = height / 2;//ͼƬ������

	int move_right = 0;
	int move_down = 0;

	RECT image_rect;
	image_rect.left = 0;
	image_rect.right = 0;
	image_rect.top = 0;
	image_rect.bottom = 0;

	BitBlt(hdc, i, j, KUANG, GAO, comp_hdc, 0, 0, SRCCOPY);//����λ��ת��
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));//��ˢ��ɫ

	HANDLE gb = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(gb, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;//���ؿ���̨���
	SetConsoleCursorInfo(gb, &CursorInfo);//���ؿ���̨���

	while (1)
	{
		GetWindowRect(hwnd, &rect);//��ȡ���ڿ��
		width = rect.right - rect.left;//���ڿ��
		height = rect.bottom - rect.top;//���ڸ߶�

		gotoxy(6, 3);
		printf("x:%5d   y:%5d", p.x, p.y);
		gotoxy(6, 6);
		printf("x:%5d   y:%5d", i + rect.left, j + rect.top);

		GetCursorPos(&p);//��ȡ�������

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

		FillRect(hdc, &image_rect, brush);//ʹ��ָ����ˢ��������
		image_rect.left = i;
		image_rect.right = i + KUANG;
		image_rect.top = j;
		image_rect.bottom = j + GAO;
		BitBlt(hdc, i, j, KUANG, GAO, comp_hdc, 0, 0, SRCCOPY);//����λ��ת��

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

	ReleaseDC(hwnd, hdc);//�ͷ��ڴ�DC

	return 0;
}