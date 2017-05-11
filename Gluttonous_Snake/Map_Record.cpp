#include"Map_Record.h"
#include"Game.h"
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>

int map[1][30] = { { 0,0, 0,479, 480,479, 480,0 } };
extern struct game mygame;
void initmap()
{
	setlinecolor(BLUE);
	polygon((POINT*)map[0], 4);
	switch (mygame.whichmap)
	{
	case 0:
		break;
	case 1:
		line(0, 235, 225, 235);
		line(480, 235, 255, 235);
		break;
	case 2:
		line(0, 235, 215, 235);
		line(480, 235, 255, 235);
		line(235, 0, 235, 225);
		line(235, 480, 235, 255);
		break;
	}
	//polygon((POINT*)map[map_which], 4);
	
}

int chooseMap()
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
	outtextxy(200, 140, _T("Map1"));
	outtextxy(200, 240, _T("Map2"));
	outtextxy(200, 340, _T("Map3"));

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
				if (num == 1) return num-1; 
				if (num == 2) return num-1; 
				if (num == 3) return num-1;
			case ESC:
				return num;
			}
		}
	//}
}

void initscore() {
	//mygame.score = (mygame.snakeLen - 2) * 100;
	switch (mygame.score) {
	case 1200:
		mygame.grade++; mygame.speed -= 100; 
		mygame._isover = NEXTGG;
		break;
	case 2500:
		mygame.grade++; mygame.speed -= 100; 
		mygame._isover = NEXTGG;
		break;
	case 5000:
		mygame._isover = SUCCESS;
		break;
	}
}

void drawscore()
{
	settextstyle(20, 0, _T("楷体"));
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), mygame.score);
	outtextxy(490, 0, _T("score:"));
	outtextxy(560, 0, s);
	_stprintf_s(s, _T("%d"), mygame.grade);
	outtextxy(490, 30, _T("grade:"));
	outtextxy(560, 30, s);

	setlinecolor(BLUE);
	line(480, 60, 640, 60);

	setfillcolor(WHITE);
	solidcircle(485, 100, 5);
	outtextxy(495, 90, _T("食物"));

	setfillcolor(BLACK);
	solidcircle(485, 130, 5);
	outtextxy(495, 120, _T("毒草"));

	setfillcolor(BACKCOLOR);
	solidcircle(485, 160, 5);
	outtextxy(495, 150, _T("炸弹"));

	line(480, 200, 640, 200);
	outtextxy(500, 220, _T("移动：方向键"));

	outtextxy(500, 260, _T("存档：ESC"));
}

void showrecord()
{
	drawBackground();
	settextstyle(20, 0, _T("楷体"));
	outtextxy(20, 20, _T("ESC"));
	
	FILE *fp;
	fopen_s(&fp,"Record.rec", "rb");
	int score=0;
	settextstyle(80, 22, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(250, 30, _T("RECORD"));

	settextstyle(60, 22, _T("楷体"));
	settextcolor(BLACK);
	for (int k = 0;k < 5;k++)
	{
		int i = 0;
		char name[30] = {};
		do {
			fread(&name[i], 1, 1, fp);
		} while (name[i++] != ' ');
		TCHAR name1[30];
		_stprintf_s(name1, _T("%s"), name);
		outtextxy(150, 100+k*60, name1);
		fscanf_s(fp, "%d", &score);
		TCHAR score1[7];
		_stprintf_s(score1, _T("%d"), score);
		outtextxy(350, 100+k*60, score1);
	}
	fclose(fp);
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == 224)ch = _getch();
		if (ch == ESC) return;
	}
}

void writerecord()
{
	struct player {
		int score;
		char name[10];
	};
	
	
	struct player players[5];
	struct player temptt;
	FILE *fp;
	fopen_s(&fp, "Record.rec", "rb");
	for (int k = 0;k < 5;k++)
	{
		for (int i = 0;i < 10;i++)
		{
			char ch;
			fread(&ch, 1, 1, fp);
			while (ch == '\r' || ch == '\n')
			{
				fread(&ch, 1, 1, fp);
			}
			players[k].name[i] = ch;
		}
		fscanf_s(fp, "%d", &players[k].score);
		 temptt = players[k];
	}
	
	if (mygame.score <= players[4].score)
	{
		char ch;
		InputBox(&ch, 1, "抱歉您未进入排行榜，请继续加油", NULL, NULL, 0, 0, true);
	}
	else
	{
		players[4].score = mygame.score;
		InputBox(players[4].name, 10, "恭喜您进入排行榜，请输入您的姓名", NULL, NULL, 0, 0, true);
		temptt = players[4];
		for (int i = 0;i < 10;i++)
		{
			if (players[4].name[i] == '\0' || players[4].name[i] == '\n' || players[4].name[i] == '\r')
			{
				players[4].name[i] = ' ';
			}
		}
		struct player temp= players[4];
		for (int i = 4;i >= 1;i--)
		{
			if (players[i].score > players[i - 1].score)
			{
				temp = players[i - 1];
				players[i - 1] = players[i];
				players[i] = temp;
			}
		}
		fclose(fp);
		fopen_s(&fp, "Record.rec", "wb");
		for (int i = 0;i < 5;i++)
		{
			fwrite(players[i].name, 10 * sizeof(char), 1, fp);
			fprintf_s(fp,"%d", players[i].score);
			fwrite("\n", sizeof(char), 1, fp);
		}
	}
	fclose(fp);
}

void memory(struct snake *head, struct food *prt1)
{
	FILE *fp;
	fopen_s(&fp, "Memory.mem", "wb");

	fprintf_s(fp, "%d  ", mygame.grade);
	fprintf_s(fp, "%d  ", mygame.isPosExist);
	fprintf_s(fp, "%d  ", mygame.score);
	fprintf_s(fp, "%d  ", mygame.snakeLen);
	fprintf_s(fp, "%d  ", mygame.speed);
	fprintf_s(fp, "%d  ", mygame.whichmap);
	fprintf_s(fp, "%d  ", mygame._isgamecon);
	fprintf_s(fp, "%d  ", mygame._isover);
	fwrite("\n", sizeof(char), 1, fp);

	while (head != NULL)
	{
		fprintf_s(fp, "%d  ",head->x );
		fprintf_s(fp, "%d  ",head->y );
		head = head->next;
	}
	fwrite("\n", sizeof(char), 1, fp);
	while (prt1 != NULL)
	{
		fprintf_s(fp, "%d  ",prt1->x);
		fprintf_s(fp, "%d  ", prt1->y);
		fprintf_s(fp, "%d  ", prt1->kind);
		prt1 = prt1->next;
	}
	fclose(fp);
}

