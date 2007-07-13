#ifndef _OBJECTS_H
#define _OBJECTS_H

#define BREITE 0.1f
#define STANGENBREITE 0.025f

void drawDisk(GLUquadricObj **quadric, const GLfloat outer, const GLfloat inner);
void drawPin(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height);
void drawAllPins(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height, const GLfloat gap);
void drawBitmapString(const GLfloat x, const GLfloat y, const GLfloat z, void *font, char *string);
void drawBitmapInt(const GLfloat x, const GLfloat y, const GLfloat z, void *font, const int number);

#endif /* _OBJECTS_H */
