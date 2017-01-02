#include "Game.h"
struct game mygame {
	0,0,1,300,0,1,2,1
};
int isGameCon = 1;
void game()
{
	initgraph(640, 480);
	
	do{
		int maptemp = mygame.whichmap;
		mygame = {
			0,0,1,300,0,1,2,1
		};
		mygame.whichmap = maptemp;
		welcome();
		menu();
		choose();
	} while (mygame._isgamecon);
	closegraph();
}

void welcome()
{
	drawBackground();
	TCHAR text[] =_T( "Gluttonous Snake");
	settextstyle(80,22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(140, 30, text);
	settextstyle(20,0, _T("楷体"));
	outtextxy(20, 20, _T("ESC"));
	outtextxy(500, 440, _T("By X-wenhao"));

}

void drawBackground()
{
	setfillcolor(RGB(171, 245, 243));
	setbkcolor(RGB(171, 245, 243));
	solidrectangle(0, 0, 640, 480);
	setlinecolor(WHITE);
	rectangle(0, 0, 639, 479);
}

void menu()
{
	
	rectangle(140, 120, 480,420 );
	line(140, 220, 480, 220);
	line(140,320, 480, 320);
	settextstyle(60, 22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(200, 140, _T("Start"));
	outtextxy(200, 240, _T("ChooseMap"));
	outtextxy(200, 340, _T("Record"));
	settextstyle(20, 0, _T("楷体"));
	outtextxy(20, 20, _T("ESC"));
}

void choose()
{
	int ch = UP;
	int num = 1;
	int is=1;
	while (is)
	{
		highlight(num, 1);
		//if (_kbhit())
		//{
			ch = _getch();
			if (ch == 224)ch = _getch();
			switch (ch)
			{
			case UP:
				if (num == 1);
				else
				{
					highlight(num, 0);
					num--;
				}
				continue;
			case DOWN:
				if (num == 3);
				else
				{
					highlight(num, 0);
					num++;
				}
				continue;
			case ENTER:
				if (num == 1)
				{
					startgame();
					is--;
				}
				if (num == 2) {
					mygame.whichmap = chooseMap();
					is--;
				}
				if (num == 3)
				{
					showrecord();
					is--;
				}
				break;
			case ESC:
				is--;
				mygame._isgamecon = 0;
				break;
			}
		}
	//}
	
}

void highlight(int pos, int kind)
{
	if (kind == 0)setlinecolor(WHITE);
	else setlinecolor(BLUE);
	rectangle(140, 20 + pos * 100, 480, 120 + pos * 100);
}

void startgame()
{
	mygame._isover = 0;
	mygame.snakeLen = 2;
	drawBackground();
	initmap();
	//initrecord();
	struct snake first = { 245,245,NULL };
	struct snake second = { 235,245,NULL };
	struct snake *head = &first;
	first.next = &second;
	struct food *prt1 = NULL;
	prt1 = initFood(prt1, head);
	moveSnake(head, prt1);
}

void failure()
{
	drawBackground();
	settextstyle(80, 22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(200, 200, _T("YOU LOSE!!"));
	_getch();
}