#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "head.h"

clock_t start;

int main(int argc, char *argv[])
{
	soundPlay("sound/sm64_enter_course.wav");
	glutInitWindowPosition(0, 0); //cordinate of left-upper corner of window
	glutInitWindowSize(850, 850); //size of window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("The Penguin Race");
	glutDisplayFunc(display);
	init();
	start = clock();
	soundPlay("sound/06-slider.mp3");
	glutMainLoop();
	return 0;
}
