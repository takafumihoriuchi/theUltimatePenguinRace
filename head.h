#include <time.h>

#ifndef PART_H
#define PART_H

enum COLOR { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK };

extern GLfloat pos0[];
extern GLfloat pos1[];
extern GLfloat color[][4];
extern int X;
extern int Y;
extern double L;

extern int mySpecialValue;
extern double tekiList[][3];
extern int tekiIndex;
extern double coinList[][3];
extern int coinIndex;
extern double v;
extern double theta;
extern char sliderMap[400][20]; //[Y][X], ドットペインティング状にコースを描画するようの配列

//variables of mario
extern double x;
extern double y;
extern double z;
extern double rightleg;
extern double leftleg;
extern double rightarm;
extern double leftarm;
extern double lean;
extern double leanlr;
extern double mdeg; //マリオの正面の向き
extern int wcheck; //walk check
extern int jflg; //jump flag
extern double velocity;
extern int gflg; //goal flag ゴールしたか否かの判定に利用するフラグ（ブールの使い方がわからないのでintで代用しています）

extern int ncoin; //集めたコインの枚数。
extern int rcoin; //rotation of coin。コインの回転角度
extern clock_t start, end; //タイム計測用の変数

extern int cclear;

//variables of penguin
extern double py;
extern double px;

void swingmotion();
void soundPlay(char *fname);
void soundStop();

void cylinder(float radius,float height,int sides);
void glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint stacks);

void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3]);
void drawGround();

void drawMario();
void drawTeki();
void drawCoin();
void drawPenguin();
void eda();
void heta();
void apple();
void orange();
void grape();

int collision();
void pointup();
void display(void);
void myTimerFunc(int value);
void myKeyboardFunc(unsigned char key, int x, int y);
void mySpcialFunc(int key, int xx, int yy);
void mySpcialUpFunc(int key, int xx, int yy);
void init(void);

#endif
