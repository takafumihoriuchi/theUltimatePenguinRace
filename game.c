#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "head.h"
#include "sliderPixel.h"
#include <unistd.h> //system-calls below
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
GLfloat color[][4] = {
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 0.0, 0.0, 1.0 },
	{ 0.0, 1.0, 0.0, 1.0 },
	{ 0.0, 0.0, 1.0, 1.0 },
	{ 1.0, 1.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0, 1.0 },
	{ 0.7, 0.7, 0.7, 1.0 },
	{ 0.0, 0.0, 0.0, 1.0 } };
int X = 20; //width of stage in x-axis
int Y = 400; //length of stage in y-axis
double L = 1;
double x = 7; //initialize position of mario
double y = -7; //initialize position of mario
double z = 0; //initialize position of mario
int mySpecialValue = 0;
double tekiList[][3] = { //障害物の配置座標のリスト。
		{ 2.0, 89.0, 0.0 },
		{ 8.0, 325.0, 0.0 }, 
		{ 3.0, 375.0, 0.0 },
		{ 12.0, 125.0, 0.0 }, 
		{ 12.0, 240.0, 0.0 },
		{ 11.0, 340.0, 0.0 },
		{ 12.0, 101.0, 0.0 }, 
		{ 5.0, 160.0, 0.0 }, };
int tekiIndex = 8; //障害物の個数
double coinList[][3] = { //コインの配置座標のリスト。ランダムに変更？
		{ 1.0, 3.0, 0.7 },
		{ 4.0, 6.0, 0.7 },
		{ 2.0, 7.0, 0.7 },
		{ 1.0, 12.0, 0.7 },
		{ 2.0, 15.0, 0.7 },
		{ 1.0, 16.0, 0.7 },
		{ 3.0, 19.0, 0.7 },
		{ 3.0, 22.0, 0.7 },
		{ 3.0, 23.0, 0.7 },
		{ 3.0, 24.0, 0.7 },
		{ 3.0, 25.0, 0.7 },
		{ 4.0, 38.0, 0.7 },
		{ 2.0, 44.0, 0.7 },
		{ 1.0, 58.0, 0.7 },
		{ 3.0, 61.0, 0.7 },
		{ 0.0, 70.0, 0.7 },
		{ 4.0, 75.0, 0.7 },
		{ 2.0, 81.0, 0.7 },
		{ 4.0, 84.0, 0.7 },
		{ 2.0, 89.0, 0.7 },
		{ 7.0, 100.0, 0.0 },
		{ 7.0, 103.0, 0.0 },
		{ 7.0, 106.0, 0.0 },
		{ 7.0, 109.0, 0.0 },
		{ 7.0, 112.0, 0.0 },
		{ 7.0, 115.0, 0.0 },
		{ 7.0, 118.0, 0.0 },
		{ 7.0, 121.0, 0.0 } };
int coinIndex = 28; //コインの個数
int ncoin = 0; //コインの枚数
int rcoin = 0; //コインの回転角度

double v = 0;
double theta;

int cclear = 0; //0=>cleared, 1=>blocked //stop scrolling on collsion
clock_t start, end;
int jflg = 0; //jump flag
double velocity = 0;
int gflg = 0; //goal flag, 0:playing, 1:win, 2:lose, -1:gameover
//int sdflg = 0; //sound stop flag //still working on this

//penguin
double py = 0;
double px = 0;
int pencry = 0; //penguin cry (sound)

//variables of mario motion
double rightleg = 0;
double leftleg = 0;
double rightarm = 0;
double leftarm = 0;
double lean = 0;
double leanlr = 0;
double mdeg; //face direction of mario
int wcheck = 1; //walk check

char buffer1[30];
char buffer2[30];

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();

	drawMario();
	drawPenguin();

	drawTeki();
	drawCoin();

	//文字列の描画
	sprintf(buffer1, "%d", ncoin); //うまい描画方法がわからない。配置や文字フォントを変更したい。
	drawBitmapString(GLUT_BITMAP_HELVETICA_18, "     coins collected"); //文字列の描画
	drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer1); //文字列の描画
	if (gflg == 1) {
		drawBitmapString(GLUT_BITMAP_HELVETICA_18, "                               　/ CONGRATS! YOU'VE JUST DEFEATED THE P!"); //文字列の描画
	} else if (gflg == 2) {
		drawBitmapString(GLUT_BITMAP_HELVETICA_18, "                               　/ SORRY... YOU'VE GOT DEFEATED BY THE P"); //文字列の描画
	} //冗長に思える空白記号は、文字列の配置を適切に設定できれば整理できる。

	glPopMatrix();
	glutSwapBuffers();
}

void idle(void)
{
	glutPostRedisplay();
}

void drawBitmapString(void *font, char *string)
{
	glPushAttrib(GL_CURRENT_BIT);
	while (*string) glutBitmapCharacter(font, *string++); //ビットマップ文字列の描画
	glPopAttrib();
}

void soundPlay(char *fname)
{
	pid_t pid;
	if ((pid = fork()) == 0) {
		execlp("afplay", "afplay", fname, NULL); //works only for UNIX environment?
	}
}

void soundStop()
{
	pid_t pid;
	//int status;
	if ((pid = fork()) == 0) { //child-process
		execlp("killall", "killall", "afplay", NULL); //works only for UNIX environment?
		//sdflg = 1;
	} else { //parent-process
		//while(1) {
		//	if (sdflg == 1) break;
		//}
		//sdflg = 0;
		return;
		//wait(&status); //機能していない
	}
}

void myTimerFunc(int value)
{
	rcoin += 2; //コインが回る
	pointup(); //コインとの当たり判定
	collision(); //障害物との当たり判定
	double MARGIN = 0.05;

	//penguin-moves
	if (y>0 && y<80) {
		if (pencry == 0) {
			pencry = 1;
			soundPlay("sound/sm64_mama_penguin.wav");
		}
		px += 0.02;
		py += 0.4;
	} else if (y>=80 && py<=Y-28) {
		if (pencry == 1) {
			pencry = 2;
			soundPlay("sound/sm64_mama_penguin.wav");
		}
		py += 0.7;
	}

	//mario-motion
	if (y>0 && y<Y && Y*L > y && cclear==0) y += 0.4;
	if (y>0 && y<Y && Y*L > y && cclear==0) y += velocity;

	//落下処理
	if (y>0 && y<Y && z<=0) { //z<=0は、枠外にジャンプ中に落下を強めることを防止する。
		if (x>=0 && x<=X && sliderMap[(int)(Y-y)][(int)x]=='*' && z==0) {
		} else {
			z -= 0.2; //sliderPixel.hを使った落下判定
		}
		/*
		if (sliderMap[(int)y][(int)x]!='*' || z<0) { //こちらのz<0は、落ちた後に枠内での戻った時に引っかかってしまうことを防止する
			z -= 0.2; //sliderPixel.hを使った時の落下判定
		}
		*/
	}

	if (z < -1) {
		if (gflg!=-1) {
			printf("GAME OVER...\n"); //コースから落下したらゲームオーバー
			soundPlay("sound/sm64_mario_falling.wav");
		}
		gflg = -1;
		if (z<-36) {
			//sleep(1); //sleepを使えば上手くいくが、反応が良くない
			soundStop(); //子プロセスが、親プロセスがsoundPlay()を読んだ後に、killall afplayを実行してしまっている。
			soundPlay("sound/sm64_exit_course.wav");
			exit(0); //強制終了
		}
	}
	
	//key-imput moves
	if (mySpecialValue & (1 << 0)) //up
	{
		if (y<=0 || y>=Y) {
			y += 0.1; //プラットフォームにいる時の処理
		} else {
			velocity += 0.001; //スライダーにいる時の処理
		}
		
		if (collision()) y -= 0.1+0.07; //collsion to the snow-man; modify effect

		if (Y < y && z>=0 && gflg==0) {
			//y -= 0.1;
			end = clock();
			double time = (double)(end - start)/CLOCKS_PER_SEC;
			double record = ncoin*6.2 - time*1.3;
			printf("\n******************************************\n");
			if (py+12 < y) { //??? offset?
				printf("CONGRATS! You've beat the PENGUIN!!!\n");
				record += 60.0;
				gflg = 1;
				soundPlay("sound/sm64_high_score.wav");
			} else {
				printf("Sorry... You've lost to the penguin...\n");
				record -= 1.0;
				gflg = 2;
			}
			printf("Coin: %d\nTime: %.2f sec\nRecord: %.2f\n", ncoin, time, record); //timer is not relevant to the real time
			printf("******************************************\n\n");
			//マリオとペンギンがそれぞれゴールした時間を変数に格納しておいて、引き算をして、正だったら。。。負だったら。。。でも良い。
		}
	}

	if (mySpecialValue & (1 << 1)) //left
	{
		x -= 0.1;
		if (collision())x += 0.1;
	}
	if (mySpecialValue & (1 << 2)) //right
	{
		x += 0.1;
		if (collision())x -= 0.1;
	}
	if (mySpecialValue & (1 << 3)) //down
	{
		if (y<=0 || y>=Y)
			y -= 0.1;
		else
			velocity -= 0.001;
		if (collision()) y += 0.1+0.07;
	}

	if (z > 0) {//able to jump
		v -= 0.01;
		z += v;
		if (collision()) {
			z -= v;
			v = 0;
		}
		if (z <= 0) {
			z = 0;
			v = 0;
			jflg = 0; //reset jump flag
		}
	}

	glLoadIdentity();
	
	//camera-works
	if (y>-3 && y<-1) {
		gluLookAt(x, y+1, 1, px, py, 3, 0.0, 0.0, 1.0);
	} else if (y>0 && y<Y) {
		gluLookAt(0.0 + x, -16.0 + y, 9.0, x, y, 3, 0.0, 0.0, 1.0); //（カメラの位置、焦点、垂直方向？）
	} else {
		gluLookAt(0.0 + x, -16.0 + y, 9.0, x, y, 3, 0.0, 0.0, 1.0);
	}

	glutTimerFunc(10, myTimerFunc, 0);
}

void swingmotion(void) { //歩行アニメーションのための関数
	lean = 15;
	if (leftleg == 30.0 || rightleg == 30.0) wcheck = 1-wcheck; //切り替え
	if (wcheck == 1) {
		leftleg -= 6.0;
		rightleg += 6.0;
		rightarm -= 6.0;
		leftarm += 6.0;
	} else {
		leftleg += 6.0;
		rightleg -= 6.0;
		leftarm -= 6.0;
		rightarm += 6.0;
	}
}

void pointup() //collision to coin
{
	int i;
	double MARGIN = 0.05;
	for (i = 0; i < coinIndex; i++)
	{
		if ((coinList[i][0] - x < 1) && (coinList[i][0] - x > -1)
			&& (coinList[i][1] - y < 1) && (coinList[i][1] - y > -1)
			&& (coinList[i][2] - z < 1) && (coinList[i][2] - z > -1))
		{
			coinList[i][2] = -100; //move coin to z = -100 (to pretend that it disappeared)
			ncoin++;
			soundPlay("sound/sm64_coin.wav");
		}
	}
}

int collision() //障害物とのcollision
{
	int i;
	double MARGIN = 0.05;
	if (z > 1) {
		cclear = 0;
		return 0;
	}
	for (i = 0; i < tekiIndex; i++) {
		if ((tekiList[i][0] - x <0.8 - MARGIN) && (tekiList[i][0] - x >-0.8 + MARGIN)
			&& (tekiList[i][1] - y <0.8 - MARGIN) && (tekiList[i][1] - y >-0.8 + MARGIN)) {
			cclear = 1;
			return 1;
		}
	}
	cclear = 0;
	return 0;
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		if (jflg == 0)  { //if statement for disabling continueus multiple jumps
			v = 0.2;
			z += v; //add 0.2 to z while space key is pressed
			jflg = 1;
			lean = -10;
			rightleg = -18;
			leftleg = -18;
			rightarm = 0;
			leftarm = 0;
			soundPlay("sound/sm64_mario_hoohoo.wav");
		}
		break;
	case '\033': //close when pressed escape or Q, q
	case 'q':
	case 'Q':
		soundStop();
		exit(0);
	}
}

void mySpcialFunc(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue |= 1 << 0;
		if (y<=0 || y>=Y) {
			mdeg = 180.0;
			swingmotion();
		} else {
			rightleg = 40;
			leftleg = 40;
			rightarm = 0;
			leftarm = 0;
			lean = 10;
			leanlr = 0;
		}
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;
		if (y<=0 || y>=Y) {
			mdeg = 270.0;
			swingmotion();
		} else {
			rightleg = 40;
			leftleg = 40;
			rightarm = 0;
			leftarm = 0;
			leanlr = 15;
		}
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;
		if (y<=0 || y>=Y) {
			mdeg = 90.0;
			swingmotion();
		} else {
			rightleg = 40;
			leftleg = 40;
			rightarm = 0;
			leftarm = 0;
			leanlr = -15;
		}
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;
		if (y<=0 || y>=Y) {
			mdeg = 0.0;
			swingmotion();
		} else {
			rightleg = 40;
			leftleg = 40;
			rightarm = 0;
			leftarm = 0;
			lean = -10;
			leanlr = 0;
		}
		break;
	default:
		break;
	}
}

void mySpcialUpFunc(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue &= ~(1 << 0);
		if (y<=0 || y>=Y) {
			lean = 0;
			rightleg = 0;
			leftleg = 0;
			rightarm = 0;
			leftarm = 0;
		}
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);
		if (y<=0 || y>=Y) {
			lean = 0;
			rightleg = 0;
			leftleg = 0;
			rightarm = 0;
			leftarm = 0;
		}
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);
		if (y<=0 || y>=Y) {
			lean = 0;
			rightleg = 0;
			leftleg = 0;
			rightarm = 0;
			leftarm = 0;
		}
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);
		if (y<=0 || y>=Y) {
			lean = 0;
			rightleg = 0;
			leftleg = 0;
			rightarm = 0;
			leftarm = 0;
		}
		break;
	default:
		break;
	}

}

void init(void)
{
	glClearColor(0.6, 0.6, 0.6, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpcialFunc);
	glutSpecialUpFunc(mySpcialUpFunc);

	glutIdleFunc(idle);

	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, .1, 90.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, -10.0, 2.0, 0.0, 0.0, 1.5, 0.0, 0.0, 1.0);

	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	myTimerFunc(0);

	glEnable(GL_BLEND); //these two lines enable alpha settings
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}