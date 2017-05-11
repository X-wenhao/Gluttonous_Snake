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
				int whichgame = choosegame();
				startgame(whichgame);
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
}

void highlight(int pos, int kind)
{
	if (kind == 0)setlinecolor(WHITE);
	else setlinecolor(BLUE);
	rectangle(140, 20 + pos * 100, 480, 120 + pos * 100);
}

void startgame(int whichgame)
{
	struct snake first;
	struct snake second;
	struct snake *head=NULL ;
	struct food *prt1=NULL;
	if(whichgame)
	{
		FILE *fp;
		fopen_s(&fp, "Memory.mem", "rb");
		fscanf_s(fp, "%d", &mygame.grade);
		fscanf_s(fp, "%d", &mygame.isPosExist);
		fscanf_s(fp, "%d", &mygame.score);
		fscanf_s(fp, "%d", &mygame.snakeLen);
		fscanf_s(fp, "%d", &mygame.speed);
		fscanf_s(fp, "%d", &mygame.whichmap);
		fscanf_s(fp, "%d", &mygame._isgamecon);
		fscanf_s(fp, "%d", &mygame._isover);
		struct snake *temphead = NULL;
		for (int i = 1;i <= mygame.snakeLen;i++)
		{
			struct snake* temp = (struct snake*)malloc(sizeof(struct snake));
			temp->next = NULL;
			fscanf_s(fp, "%d", &temp->x);
			fscanf_s(fp, "%d", &temp->y);
			if (i == 1) {
				head =temphead= temp;
			}
			else
			{
				temphead->next = temp;
				temphead = temphead->next;
			}
		}

		struct food *tempfood = NULL;
		for (int i = 1;i <= 1 + (450 - mygame.speed) / 25;i++)
		{
			struct food* temp = (struct food*)malloc(sizeof(struct food));
			temp->next = NULL;
			fscanf_s(fp, "%d", &temp->x);
			fscanf_s(fp, "%d", &temp->y);
			fscanf_s(fp, "%d", &temp->kind);
			if (i == 1) {
				prt1 = tempfood = temp;
			}
			else
			{
				tempfood->next = temp;
				tempfood = tempfood->next;
			}
		}
		fclose(fp);
		
	}
	else
	{
		mygame._isover = 0;
		mygame.snakeLen = 2;
		drawBackground();
		initmap();
		//initrecord();
		first = { 245,245,NULL };
		second = { 235,245,NULL };
	    head = &first;
		first.next = &second;
		prt1 = NULL;
		prt1 = initFood(prt1, head);
	}
	moveSnake(head, prt1);
}

int choosegame()
{
	drawBackground();
	TCHAR text[] = _T("Gluttonous Snake");
	settextstyle(80, 22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(140, 30, text);
	settextstyle(20, 0, _T("楷体"));
	outtextxy(500, 440, _T("By X-wenhao"));
	settextstyle(20, 0, _T("楷体"));
	outtextxy(20, 20, _T("ESC"));

	rectangle(140, 120, 480, 420);
	line(140, 220, 480, 220);
	line(140, 320, 480, 320);
	settextstyle(60, 22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(200, 140, _T("New Game"));
	outtextxy(200, 240, _T("Old Game"));
	outtextxy(200, 340, _T("Can't choose"));

	int ch = UP;
	int num = 1;
	while (1)
	{
		highlight(num, 1);
		///if (_kbhit())
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
			if (num == 1) return num - 1;
			if (num == 2) return num - 1;
			if (num == 3) break;
		case ESC:
			return num;
		}
	}
}

