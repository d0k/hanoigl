#ifndef _OBJECTS_H
#define _OBJECTS_H

#define BREITE 0.1f
#define STANGENBREITE 0.025f

void drawDisk(GLUquadricObj **quadric, const GLfloat outer, const GLfloat inner);
void drawPin(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height);
void drawAllPins(GLUquadricObj **quadric, const GLfloat radius, const GLfloat height, const GLfloat gap);

#endif /* _OBJECTS_H */
