#include "Snake_Food.h"
#include<stdlib.h>
#include<time.h>
#include"Game.h"
#include"Map_Record.h"
extern struct game mygame;
struct food* initFood(struct food *prt1, struct snake* head) {
	int x, y;
	srand((unsigned)time(NULL));
	struct food *prt2;
	prt1 = prt2 = (struct food *)malloc(sizeof(struct food));
	for (int j = 0; j < 1 + (450 - mygame.speed) / 25; j++) {
		while (1) {
			struct snake *pts = head;
			struct food *ptf = prt1;
			int i = 1;
			x = (rand() % LEN)*10+5;
			y = (rand() % LEN)*10+5;
			while (pts != NULL)
			{
				if (pts->x == x&&pts->y == y)
				{
					i = 0;break;
				}
				pts = pts->next;
			}
			while (j!=0&&ptf != NULL)
			{
				if (ptf->x == x&&ptf->y == y)
				{
					i = 0;break;
				}
				ptf = ptf->next;
			}
			if (getpixel(x, y) == BLUE)i = 0;
			if (i)break;
		}
		prt2->x = x;
		prt2->y = y;
		if (j == 0) {
			prt2->kind = 6;
			//setfillcolor(WHITE);
			//solidcircle(prt2->x, prt2->y, 5);

		}
		else if (j <=(450 - mygame.speed) / 50) {
			prt2->kind = 7;
			//setfillcolor(RED);
			//solidcircle(prt2->x, prt2->y, 5);
		}
		else {
			prt2->kind = 8;
			//setfillcolor(BLACK);
			//solidcircle(prt2->x, prt2->y, 5);
		}
		if (j != (450 - mygame.speed) / 25) {
			prt2->next = (struct food *)malloc(sizeof(struct food));
			prt2->next->next = NULL;
		}
		prt2 = prt2->next;
	}
	return prt1;
}

void moveSnake(struct snake * head, struct food *prt1) {
	struct snake add;

	int dir1 = RIGHT;
	int dir2 = dir1;
	while (1)
	{
		add = *head;
		//if (_kbhit()) {
			dir2 = _getch();
			if (dir2 == 224) 
			{
				dir2 = _getch();
				if (dir1 == UP&&dir2 == DOWN);
				else if (dir1 == RIGHT&&dir2 == LEFT);
				else if (dir1 == LEFT&&dir2 == RIGHT);
				else if (dir1 == DOWN&&dir2 == UP);
				else dir1 = dir2;
			}
			else if (dir2 == ESC)
			{
				dir1 = dir2;
			}
//		}
		switch (dir1)
		{
		case LEFT:
			add.x-=10;
			break;
		case UP:
			add.y-=10;
			break;
		case DOWN:
			add.y+=10;
			break;
		case RIGHT:
			add.x+=10;
			break;
		case ESC:
			memory(head, prt1);
			return;
		default:
			break;
		}
		if (isover(add, head))break;
		else
		{
			head = insert(head, add);
			int i = 0;
			if ( i=eatIsWhich(head,prt1)) {
				prt1 = changeFood(prt1, head,i);
			}
			head = eatFood(head, prt1, i);
		}
		draw(head, prt1);
		if (mygame.isPosExist == 1)changeFood(prt1, head, 8);
	}
	switch (mygame._isover)
	{
	case DEATH:
		failure();
		writerecord();
		break;
	case NEXTGG:
		drawBackground();
		settextcolor(BLACK);
		settextstyle(30, 20, _T("楷体"));
		outtextxy(10, 200, _T("恭喜进入下一关，按任意键继续"));
		_getch();
		startgame();
		break;
	case SUCCESS:
		writerecord();
		break;
	}
	
}

int isover(struct snake add, struct snake * head)
{
	if (add.x==-5||add.x==485||add.y==-5||add.y==485)mygame._isover = 1;
	if (getpixel(add.x, add.y) == BLUE)mygame._isover = 1;
	if (mygame._isover == 0 && mygame.score == 5000) {
		mygame._isover = 10;
	}
	return mygame._isover;
}

struct snake * insert(struct snake *head, struct snake add)
{
	struct snake * temp;
	temp = (struct snake *)malloc(sizeof(struct snake));
	*temp = add;
	temp->next = head;
	
	return temp;
}

int eatIsWhich(struct snake*head, struct food*prt1) {
	while (prt1 != NULL)
	{
		if (head->x == prt1->x&&head->y == prt1->y)
		{
			return prt1->kind;
		}
		prt1 = prt1->next;
	}
	return 0;
}

struct snake* eatFood(struct snake* head, struct food*prt1, int kind)
{
	struct snake* temp = head;
	switch (kind)
	{
	case 0:
		while (head->next->next != NULL)head = head->next;
		head->next = NULL;
		break;
	case 6:
		mygame.snakeLen++;
		mygame.score += 100;
		initscore();
		break;
	case 7:
			if (mygame.snakeLen == 1)
			{
				mygame._isover = DEATH;
			}
			else
			{
				for (int i = 1;i <= (mygame.snakeLen+1) / 2 -1;i++)head = head->next;
				head->next = NULL;
				mygame.score -= (int)(mygame.snakeLen /2) * 100;
				mygame.snakeLen -= (mygame.snakeLen + 1) / 2 - 1;
				initscore();
			}
		break;
	case 8:
		if (mygame.isPosExist <= 20)
		{
			if (mygame.snakeLen == 1)
			{
				mygame._isover = DEATH;
			}
			else
			{
				while (head->next->next->next != NULL)head = head->next;
				head->next = NULL;
				mygame.snakeLen--;
				mygame.score -= 100;
				initscore();
			}
		}
		else
		{
			while (head->next->next != NULL)head = head->next;
			head->next = NULL;
			initscore();
		}
		break;
	case 9:
		break;
	}
	return temp;
}

struct food* changeFood(struct food*prt1, struct snake* head, int kind)
{
	int x, y;
	//srand((unsigned)time(NULL));
	struct food *prt2=prt1;
	do {
		while (prt2->kind != kind)prt2 = prt2->next;
		struct snake *pts = head;
		struct food *ptf = prt1;
		int i = 1;
		x = (rand() % LEN) * 10 + 5;
		y = (rand() % LEN) * 10 + 5;
		while (pts != NULL)
		{
			if (pts->x == x&&pts->y == y)
			{
				i = 0;break;
			}
			pts = pts->next;
		}
		while (ptf != NULL)
		{
			if (ptf->x == x&&ptf->y == y)
			{
				i = 0;break;
			}
			ptf = ptf->next;
		}
		if (getpixel(x,y) == BLUE)i = 0;
		if (i==0)continue;
		prt2->x = x;
		prt2->y = y;
		if(prt2->next==NULL)break;
		prt2 = prt2->next;
	} while (prt2->kind == kind);
	return prt1;
}

void drawFood(struct food* prt1)
{
	while (prt1!= NULL)
	{
		switch (prt1->kind)
		{
		case 6:
			setfillcolor(WHITE);
			break;
		case 7:
			setfillcolor(BLACK);
			break;
		case 8:
			setfillcolor(BACKCOLOR);
			break;
		case 9:
			setfillcolor(RED);
			break;
		}
		solidcircle(prt1->x, prt1->y,5);
		prt1 = prt1->next;
	}
}

void drawSnake(struct snake*head)
{
	setfillcolor(GREEN);
	while (head != NULL)
	{
		solidcircle(head->x, head->y,5);
		head = head->next;
	}
}

void draw(struct snake*head, struct food*prt1)
{
	for (int i = 1;i <= 1;i++) {
		drawBackground();
		initmap();
		drawSnake(head);
		drawFood(prt1);
		drawscore();
		lightPosi(prt1);
		//Sleep(mygame.speed);
	}
	//Sleep(mygame.speed );
}

void lightPosi(struct food*prt1)
{
	while (prt1->kind != 8)prt1 = prt1->next;

	for (int m = 1;m <= 10;m++)
	{
		struct food* temp = prt1;
		if (mygame.isPosExist <= 20) {
			setfillcolor(RGB(22, 255 - 10 * m, 10 * m));
		}
		else if (mygame.isPosExist == 40)
		{
			setfillcolor(BACKCOLOR);
		}
		else
		{
			setfillcolor(BACKCOLOR);
		}
		while (temp != NULL)
		{
			solidcircle(temp->x, temp->y, 5);
			temp = temp->next;
		}
		setfillcolor(RGB(22, 255 - 10 * m, 10 * m));
		solidcircle(485, 160, 5);
		Sleep(mygame.speed / 10);
	}
	if (mygame.isPosExist == 40)
	{
		mygame.isPosExist = 0;
	}
	mygame.isPosExist++;	
}