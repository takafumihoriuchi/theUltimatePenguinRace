#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "head.h"

GLfloat icecolor[] = {0.6, 0.9, 1, 0.8};
GLfloat coingold[] = {0.7, 0.7, 0.1, 0.95};
GLfloat woodbrown[] = {0.54, 0.27, 0.07, 0.8};

//球
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);

//円柱
void cylinder(float radius,float height,int sides){
	double pi = 3.1415;
	//上面
	glNormal3d(0.0, 1.0, 0.0);
 	glBegin(GL_POLYGON);
 	for(double i = sides; i >= 0; i--) {
  		double t = pi*2/sides * (double)i;
  		glVertex3d(radius * cos(t), height, radius * sin(t));
 	}
 	glEnd();
 	//側面
 	glBegin(GL_QUAD_STRIP);
 	for(double i=0;i<=sides;i=i+1){
  		double t = i*2*pi/sides;
   		glNormal3f((GLfloat)cos(t),0.0,(GLfloat)sin(t));
  		glVertex3f((GLfloat)(radius*cos(t)),-height,(GLfloat)(radius*sin(t)));
  		glVertex3f((GLfloat)(radius*cos(t)),height,(GLfloat)(radius*sin(t)));
 	}
 	glEnd();
 	//下面
  	glNormal3d(0.0, -1.0, 0.0);
 	glBegin(GL_POLYGON);
 	for(double i = 0; i < sides; i++) {
  		double t = pi*2/sides * (double)i;
  		glVertex3d(radius * cos(t), -height, radius * sin(t));
 	}
 	glEnd();
}

//トーラス
void glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint stacks);


void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3])
{
	GLdouble v2v[2][3];
	GLdouble vt[3];
	double abs;
	int i;
	for (i = 0; i < 3; i++)
	{
		v2v[0][i] = v1[i] - v0[i];
		v2v[1][i] = v2[i] - v0[i];
	}
	vt[0] = v2v[0][1] * v2v[1][2] - v2v[0][2] * v2v[1][1];
	vt[1] = v2v[0][2] * v2v[1][0] - v2v[0][0] * v2v[1][2];
	vt[2] = v2v[0][0] * v2v[1][1] - v2v[0][1] * v2v[1][0];
	abs = sqrt(vt[0] * vt[0] + vt[1] * vt[1] + vt[2] * vt[2]);
	for (i = 0; i < 3; i++)
		n[i] = vt[i] / abs;
}

void drawGround()
{

	int i, j;
	GLdouble normal[3] = { 0.0, 0.0, 1.0 };

	glPushMatrix();

	glNormal3dv(normal);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, woodbrown);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	for (i=-10; i<=0; i++) { //start platform
		for (j=-5; j<=X+5; j++) {
			glPushMatrix();
				glTranslatef(j+0.5, i+0.5, -0.5);
				glutSolidCube(1); //タイル状からブロック状に変更した
			glPopMatrix();
		}
	}
	for (i=Y; i<=Y+10; i++) {  //finish platform
		for (j=-5; j<=X+5; j++) {
			glPushMatrix();
				glTranslatef(j+0.5, i+0.5, -0.5);
				glutSolidCube(1); //タイル状からブロック状に変更した
			glPopMatrix();
		}
	}
	
	//ここが滑走路を描画する部分
	// draw icey ground when '*' is read
	glMaterialfv(GL_FRONT, GL_DIFFUSE, icecolor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, icecolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, icecolor);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	for (i=0; i<Y; i++)	{		// 1 ~ Y (LENGTH)
		for (j=0; j<X; j++)	{	// 0 ~ X (WIDTH)
			if (sliderMap[i][j]=='*') {
				glPushMatrix();
					glTranslatef(j+0.5, Y-i+0.5, -0.5);
					glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

void drawTeki(void)
{
    int i;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, icecolor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    for (i = 0; i < tekiIndex; i++)
    {
        glPushMatrix();
        glTranslatef(tekiList[i][0], tekiList[i][1], tekiList[i][2]);
        glScalef(1.0, 1.0, 1.7);
        glutSolidSphere(0.6, 8, 8);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawCoin(void)
{

	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, coingold);
	glMaterialfv(GL_FRONT, GL_AMBIENT, coingold);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	for (i = 0; i < coinIndex; i++)
	{
		glPushMatrix();
		glTranslatef(coinList[i][0], coinList[i][1], coinList[i][2]+1);
		glScalef(1.0, 0.2, 1.0);
		glutSolidSphere(0.3, 8, 8);
		glPopMatrix();
	}
	glPopMatrix();
}

void drawPenguin(void)
{
	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0);

	glScalef(1.0, 1.1, 1.0);
	glTranslatef(4.0+px, 0.0+py, 0.8); //move penguin
	glutSolidSphere(1.2, 4, 4);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[WHITE]);
	glTranslatef(0.0, 0.0, -0.2);
	glutSolidSphere(1.2, 4, 4);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[YELLOW]);
	glScalef(1.0, 0.5, 1.0);
	glTranslatef(-0.7, -1.4, 0.2);
	glutSolidSphere(0.5, 3, 3);
	glTranslatef(1.4, 0.0, 0.0);
	glutSolidSphere(0.5, 3, 3);

	glPopMatrix();
}