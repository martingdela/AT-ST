/*
 * Fernando Martin Garcia Del Angel
 * A01334390
 * TC3022. Computer Graphics Course.
 * Flags of the world
 */

// Please don't change lines 9-31 (It helps me to grade)
#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
	#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
	#include "GL/freeglut.h"
	#include "GL/gl.h"
#endif

#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
#include <string.h>
#include <math.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

/* Declare body parts height */
#define BODY_HEIGHT 5.0
#define BODY_RADIUS 3.0
#define UPPER_GUN_HEIGHT 5.0
#define UPPER_GUN_RADIUS 0.5

#define UPPER_LEG_RADIUS 0.5
#define LOWER_LEG_RADIUS 0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0


/* Initial joint angles */
typedef float point[3];
static GLfloat theta[11] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,
            180.0,0.0,180.0,0.0};
int bpart;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;

double size = 1.0;

void body(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(t,BODY_RADIUS,BODY_RADIUS,BODY_HEIGHT,10,10);
	glPopMatrix();
}

void left_gun(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(lua,UPPER_GUN_RADIUS,UPPER_GUN_RADIUS,UPPER_GUN_HEIGHT,10,10);
	glPopMatrix();
}

void right_gun(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(rua,UPPER_GUN_RADIUS,UPPER_GUN_RADIUS,UPPER_GUN_HEIGHT,10,10);
	glPopMatrix();
}

void left_upper_leg(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(lul,UPPER_LEG_RADIUS,UPPER_LEG_RADIUS,UPPER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void left_lower_leg(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(lll,LOWER_LEG_RADIUS,LOWER_LEG_RADIUS,LOWER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void right_upper_leg(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(rul,UPPER_LEG_RADIUS,UPPER_LEG_RADIUS,UPPER_LEG_HEIGHT,10,10);
	glPopMatrix();
}

void right_lower_leg(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	gluCylinder(rll,LOWER_LEG_RADIUS,LOWER_LEG_RADIUS,LOWER_LEG_HEIGHT,10,10);
	glPopMatrix();
}


void init() {
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
}

void drawAxis (){
	glLineWidth(3.0f);
	glBegin(GL_LINES);{
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,1,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,1);
		glVertex3f(0,0,1);
	}
	glEnd();
	glFlush();
}

void display()							// Called for each frame (about 60 times per second).
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0.0, 0.0, 10.0,										// Where the camera is.
		      0.0, 0.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);
	drawAxis();
	/* Draw Torso */
	glColor3f(0,0,0);
	glRotatef(theta[0],0,1,0);
	body();
	/* Connect left arm to the body */
	glPushMatrix();
	glTranslatef(-(BODY_RADIUS+UPPER_GUN_RADIUS), 0.9*BODY_HEIGHT,0);
	glRotatef(theta[3],1,0,0);
	left_gun();
	glPopMatrix();
	
	/* Connect right arm to the body */
	glPushMatrix();
	glTranslatef(BODY_RADIUS+UPPER_GUN_RADIUS, 0.9*BODY_HEIGHT,0);
	glRotatef(theta[5],1,0,0);
	right_gun();
	glPopMatrix();

	/* Connect the left leg */
	glPushMatrix();
	glTranslatef(-(BODY_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0);
	glRotatef(theta[7],1,0,0);
	left_upper_leg();

	glTranslatef(0,UPPER_LEG_HEIGHT,0);
	glRotatef(theta[8],1,0,0);
	left_lower_leg();
	glPopMatrix();

	/* Connect the right leg */
	glPushMatrix();
	glTranslatef(BODY_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0);
    glRotatef(theta[9], 1, 0, 0);
    right_upper_leg();

    glTranslatef(0, UPPER_LEG_HEIGHT, 0);
    glRotatef(theta[10], 1, 0, 0);
    right_lower_leg();
    glPopMatrix();

	glFlush();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle()															// Called when drawing is finished.
{
	
    glutPostRedisplay();										// Display again.
}

void reshape(int x, int y)											// Called when the window geometry changes.
{
	glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (x <= y)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) y / (GLfloat) x,
            10.0 * (GLfloat) y / (GLfloat) x, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) x / (GLfloat) y,
            10.0 * (GLfloat) x / (GLfloat) y, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
	This can help on having an interactive keyboard
*/
void littleKey(unsigned char key, int x, int y){
	switch(key){
		case 'A': case 'a': case '1': case 1:
			bpart = 0;
		break;
		case 'B': case 'b': case '2': case 2:
			bpart = 1;
		break;
		case 'C': case 'c': case '3': case 3:
			bpart = 2;
		break;
		case 'D': case 'd': case '4': case 4:
			bpart = 3;
		break;
		case 'E': case 'e': case '5': case 5:
			bpart = 4;
		break;
		case 'F': case 'f': case '6': case 6:
			bpart = 5;
		break;
		case 'G': case 'g': case '7': case 7:
			bpart = 6;
		break;
		case 'H': case 'h': case '8': case 8:
			bpart = 7;
		break;
		case 'I': case 'i': case '9': case 9:
			bpart = 8;
		break;
		case 'J': case 'j': case 10:
			bpart = 9;
		break;
		case 'K': case 'k': case 11:
			bpart = 10;
		break;
	}
	//Goes back to the display function
	// std::cout << bpart;
	glutPostRedisplay();
}

void specialKey(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:
			theta[bpart] +=0.5;
			printf("here\n");
		break;
		case GLUT_KEY_DOWN:
			theta[bpart] -=0.5;
		break;
	}
}

void myinit()
{
        GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess={100.0};
        GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
        GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING); 
        glEnable(GL_LIGHT0);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST); 

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 0.0);

/* allocate quadrics with filled drawing style */

        h=gluNewQuadric();
        gluQuadricDrawStyle(h, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        lua=gluNewQuadric();
        gluQuadricDrawStyle(lua, GLU_FILL);
        lla=gluNewQuadric();
        gluQuadricDrawStyle(lla, GLU_FILL);
        rua=gluNewQuadric();
        gluQuadricDrawStyle(rua, GLU_FILL);
        rla=gluNewQuadric();
        gluQuadricDrawStyle(rla, GLU_FILL);
        lul=gluNewQuadric();
        gluQuadricDrawStyle(lul, GLU_FILL);
        lll=gluNewQuadric();
        gluQuadricDrawStyle(lll, GLU_FILL);
        rul=gluNewQuadric();
        gluQuadricDrawStyle(rul, GLU_FILL);
        rll=gluNewQuadric();
        gluQuadricDrawStyle(rll, GLU_FILL);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(500, 500);
	glutCreateWindow("AT-ST");
	glutKeyboardFunc(littleKey);
	glutSpecialFunc(specialKey);
	
	myinit();
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}