#ifndef _OBJECTS_H
#define _OBJECTS_H

#define BREITE 0.1f
#define STANGENBREITE 0.025f

void drawDisk(GLUquadricObj **quadric, GLfloat outer, GLfloat inner);
void drawPin(GLUquadricObj **quadric, GLfloat radius, GLfloat height);
void drawAllPins(GLUquadricObj **quadric, GLfloat radius, GLfloat height, GLfloat gap);
void drawBitmapString(GLfloat x, GLfloat y, GLfloat z, void *font, char *string);
void drawBitmapInt(GLfloat x, GLfloat y, GLfloat z, void *font, int number);

#endif /* _OBJECTS_H */
