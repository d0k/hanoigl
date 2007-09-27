#ifndef _HANOIGL_H
#define _HANOIGL_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef __BORLANDC__
#include <float.h>
#endif /* __BORLANDC__ */
#endif

#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else /* __APPLE__ */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif /* __APPLE */

#endif /* _HANOIGL_H */
