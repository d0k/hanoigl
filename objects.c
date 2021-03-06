#include "hanoigl.h"
#include "objects.h"

#define SLICES 32
#define INNERSLICES 16
#define LOOPS 1

void drawDisk(GLUquadricObj **quadric, const GLfloat outer, const GLfloat inner) {
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(*quadric, outer, outer, BREITE, SLICES, LOOPS);
		gluQuadricOrientation(*quadric, GLU_INSIDE);
		if(inner > 0)
			gluCylinder(*quadric, inner, inner, BREITE, INNERSLICES, LOOPS);
		gluDisk(*quadric, inner, outer, SLICES, LOOPS);
		gluQuadricOrientation(*quadric, GLU_OUTSIDE);
		glTranslatef(0.0, 0.0, BREITE);
		gluDisk(*quadric, inner, outer, SLICES, LOOPS);
		gluQuadricOrientation(*quadric, GLU_OUTSIDE);
	glPopMatrix();
}

void drawPin(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height) {
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(*quadric, radius, radius, BREITE/2, SLICES, LOOPS);
		gluQuadricOrientation(*quadric, GLU_INSIDE);
		gluDisk(*quadric, 0.0, radius, SLICES, LOOPS);
		gluQuadricOrientation(*quadric, GLU_OUTSIDE);
		glTranslatef(0.0, 0.0, BREITE/2);
		gluDisk(*quadric, 0.0, radius, SLICES, LOOPS);
		gluCylinder(*quadric, STANGENBREITE, STANGENBREITE, height, INNERSLICES, LOOPS);
		glTranslatef(0.0, 0.0, height);
		gluDisk(*quadric, 0.0, STANGENBREITE, INNERSLICES, LOOPS);
	glPopMatrix();
}

void drawAllPins(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height, const GLfloat gap) {
	glPushMatrix();
		drawPin(quadric, radius, height);
		glTranslatef(-gap, 0.0, 0.0);
		drawPin(quadric, radius, height);
		glTranslatef(gap*2, 0.0, 0.0);
		drawPin(quadric, radius, height);
	glPopMatrix();
}

/* from lighthouse3d */
void drawBitmapString(const GLfloat x, const GLfloat y, const GLfloat z, void *font, char *string) {
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void drawBitmapInt(const GLfloat x, const GLfloat y, const GLfloat z, void *font, const int number) {
	char string[17];

	sprintf(string, "%d", number);
	drawBitmapString(x, y, z, font, string);
}
