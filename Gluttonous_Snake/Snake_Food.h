#pragma once
#define LEN 48

struct snake
{
	int x, y;
	struct snake * next;
};

struct food
{
	int x, y;
	int kind;//6==食物；7==地雷；8==毒草；9==幸运草
	struct food *next;
};

struct food* initFood(struct food*,struct snake*);
struct food* changeFood(struct food*, struct snake*,int );
void drawFood(struct food*);
void lightPosi(struct food*);

void moveSnake(struct snake*,struct food*prt1);
struct snake* eatFood(struct snake*, struct food*,int kind);
int eatIsWhich(struct snake*, struct food*);
void drawSnake(struct snake*);
int isover(struct snake, struct snake *);
struct snake * insert(struct snake *head, struct snake add);


void draw(struct snake*, struct food*);
