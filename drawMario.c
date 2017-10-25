#include <GL/glut.h>
#include <time.h>
#include "head.h"

//colors
GLfloat face[] = { 1.0, 0.8, 0.7, 1.0 };
GLfloat yellow[] = { 0.9, 0.9, 0.6, 1.0 };
GLfloat blue[] = { 0.1, 0.1, 1.0, 1.0 };
GLfloat red[] = {1.0, 0.2, 0.2, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat black[] = {0, 0, 0, 1.0};
GLfloat lightblue[] = {0.5, 0.5, 1, 1.0};
GLfloat brown[] = {0.54, 0.27, 0.07, 1.0};

void drawMario(void)
{
	glPushMatrix();

	glTranslatef(x, y, z);

	glTranslatef(0.0, 0.0, 1);
	glScalef(0.2,0.2,0.2);
	glRotatef(90,1,0,0);
	glRotatef(-90+mdeg,0,1,0);

	glRotatef(-1*lean, 0,0,1);
	glRotatef(leanlr, -1,1,0);
	
		//hat
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glMaterialfv(GL_FRONT, GL_AMBIENT, red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, red);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			glTranslatef(0.0, 1.9, 0.0);
			glScalef(1.2, 0.4, 1.0);
			glutSolidSphere(2.2, 6, 6); //back of hat
			glPushMatrix();
				glTranslatef(0.8, 1.3, 0.0);
				glScalef(1, 2, 1.3);
				glutSolidSphere(1.8, 6, 6); //top of hat
			glPopMatrix();
			glPushMatrix();
				glRotatef(17, 0, 0, 1);
				glTranslatef(2, -1.2, 0.0);
				glScalef(0.8, 0.3, 1);
				glutSolidSphere(2, 6, 6); //front of hat
			glPopMatrix();
		glPopMatrix();

		//hair
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
			glMaterialfv(GL_FRONT, GL_AMBIENT, black);
			glMaterialfv(GL_FRONT, GL_SPECULAR, black);
			glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
			glTranslatef(-0.3, 0.7, 0.0);
			glScalef(1, 1, 1.2);
			glutSolidSphere(1.5, 6, 6);
			glPushMatrix(); //side
				glRotatef(20, 0, 0, 1);
				glTranslatef(1.4, -0.1, 1.2);
				glScalef(0.8, 1.0, 0.5);
				glutSolidSphere(0.6, 6, 6);
			glPopMatrix();
			glPushMatrix(); //side
				glRotatef(20, 0, 0, 1);
				glTranslatef(1.4, -0.1, -1.2);
				glScalef(0.8, 1.0, 0.5);
				glutSolidSphere(0.6, 6, 6);
			glPopMatrix();
		glPopMatrix();


		//face
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, face);
			glMaterialfv(GL_FRONT, GL_AMBIENT, face);
			glMaterialfv(GL_FRONT, GL_SPECULAR, face);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			glTranslatef(0.7, 0.9, 0.0);
			glScalef(1.2, 1.1, 1);
			glutSolidSphere(1.7, 6, 6);
			glPushMatrix(); //nose
				glRotatef(10, 0, 0, 1);
				glTranslatef(2, -0.3, 0.0);
				glScalef(0.8, 0.9, 1.2);
				glutSolidSphere(0.6, 6, 6);
			glPopMatrix();
			glPushMatrix(); //ear
				glRotatef(10, 0, 0, 1);
				glTranslatef(-0.2, 0.0, 1.5);
				glScalef(0.8, 1.2, 1.3);
				glutSolidSphere(0.5, 6, 6);
			glPopMatrix();
			glPushMatrix(); //ear
				glRotatef(10, 0, 0, 1);
				glTranslatef(-0.2, 0.0, -1.5);
				glScalef(0.8, 1.2, 1.3);
				glutSolidSphere(0.5, 6, 6);
			glPopMatrix();
			glPushMatrix(); //mastach
				glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
				glMaterialfv(GL_FRONT, GL_AMBIENT, black);
				glMaterialfv(GL_FRONT, GL_SPECULAR, black);
				glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
				//glRotatef(10, 0, 0, 1);
				glTranslatef(1.5, -0.5, 0.0);
				glScalef(0.6, 0.6, 2.0);
				glutSolidSphere(0.6, 6, 6);
			glPopMatrix();
			glPushMatrix(); //eye
				glMaterialfv(GL_FRONT, GL_DIFFUSE, lightblue);
				glMaterialfv(GL_FRONT, GL_AMBIENT, lightblue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, lightblue);
				glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
				//glRotatef(10, 0, 0, 1);
				glTranslatef(1.2, 0.1, 0.9);
				glScalef(0.7, 0.9, 0.8);
				glutSolidSphere(0.3, 6, 6);
			glPopMatrix();
			glPushMatrix(); //eye
				glMaterialfv(GL_FRONT, GL_DIFFUSE, lightblue);
				glMaterialfv(GL_FRONT, GL_AMBIENT, lightblue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, lightblue);
				glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
				//glRotatef(10, 0, 0, 1);
				glTranslatef(1.2, 0.1, -0.9);
				glScalef(0.7, 0.9, 0.8);
				glutSolidSphere(0.3, 6, 6);
			glPopMatrix();
		glPopMatrix();

		//body
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			//glRotatef(30, 0,0,1);
			glTranslatef(0.7, -2.2, 0.0);
			glScalef(1.0, 1.2, 1);
			glutSolidSphere(1.3, 6, 6);
		glPopMatrix();
		glPushMatrix(); //button
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
			glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
			glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
			glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
			//glRotatef(30, 0,0,1);
			glTranslatef(1.4, -1.4, 0.5);
			glScalef(1, 1, 1);
			glutSolidSphere(0.3, 6, 6);
		glPopMatrix();
		glPushMatrix(); //button
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
			glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
			glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
			glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
			//glRotatef(30, 0,0,1);
			glTranslatef(1.4, -1.4, -0.5);
			glScalef(1, 1, 1);
			glutSolidSphere(0.3, 6, 6);
		glPopMatrix();
		glPushMatrix(); //neck(red)
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glMaterialfv(GL_FRONT, GL_AMBIENT, red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, red);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			//glRotatef(30, 0,0,1);
			glTranslatef(1.2, -1.1, 0.0);
			glScalef(1, 1, 1.2);
			glRotatef(65, 0,0,1);
			glutSolidCube(0.4);
		glPopMatrix();

		//arm
		glPushMatrix(); //right arm
			glRotatef(rightarm, 0,0,1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glMaterialfv(GL_FRONT, GL_AMBIENT, red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, red);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			//glRotatef(30, 0,0,1);
			glRotatef(15, 1,0,0);
			//glRotatef();
			glTranslatef(0.7, -1.1, 1.7);
			glScalef(1.4, 1.4, 3.3);
			glutSolidSphere(0.4, 6, 6);
			glPushMatrix(); //hand
				glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
				glMaterialfv(GL_FRONT, GL_AMBIENT, white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.0, 0.0, 0.3);
				glScalef(1.2, 1, 0.4);
				glutSolidSphere(0.4, 6, 6);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix(); //left arm
			glRotatef(leftarm, 0,0,1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			glMaterialfv(GL_FRONT, GL_AMBIENT, red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, red);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
			//glRotatef(30, 0,0,1);
			glRotatef(-15, 1,0,0);
			//glRotatef();
			glTranslatef(0.7, -1.1, -1.7);
			glScalef(1.4, 1.4, 3.3);
			glutSolidSphere(0.4, 6, 6);
			glPushMatrix(); //hand
				glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
				glMaterialfv(GL_FRONT, GL_AMBIENT, white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.0, 0.0, -0.3);
				glScalef(1.2, 1, 0.4);
				glutSolidSphere(0.4, 6, 6);
			glPopMatrix();
		glPopMatrix();

		//leg
		glPushMatrix(); //right leg
			glRotatef(rightleg, 0,0,1);
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.7, -3.6, 0.6);
				glScalef(1.1, 1.6, 0.7);
				glutSolidSphere(0.8, 6, 6);
			glPopMatrix();
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
				glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
				glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.9, -4.6, 0.6);
				glScalef(1.3, 0.7, 0.7);
				glutSolidSphere(0.8, 6, 6);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix(); //left leg
			glRotatef(leftleg, 0,0,1);
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.7, -3.6, -0.6);
				glScalef(1.1, 1.6, 0.7);
				glutSolidSphere(0.8, 8, 8);
			glPopMatrix();
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
				glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
				glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
				glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
				//glRotatef(30, 0,0,1);
				glTranslatef(0.9, -4.6, -0.6);
				glScalef(1.3, 0.7, 0.7);
				glutSolidSphere(0.8, 6, 6);
			glPopMatrix();
		glPopMatrix();

		glPopMatrix();
}