#pragma once
#include"Map_Record.h"
#include"Snake_Food.h"
#include<conio.h>
#include<graphics.h>
#include<easyx.h>
#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80//224
#define ESC   27
#define ENTER 13
#define CHOICE_REC_HEIGHT 
#define CHOICE_REC_LENGTH
#define G 10
#define BACKCOLOR RGB(171, 245, 243)
#define SUCCESS 100
#define NEXTGG 10
#define DEATH 1
struct game {
	int whichmap;
	int score;
	int grade;
	int speed;
	int _isover;
	int isPosExist;
	int snakeLen;
	int _isgamecon;
};

void game();
void welcome();
void menu();
void choose();
void drawBackground();
void highlight(int pos,int kind);
void startgame();

void failure();