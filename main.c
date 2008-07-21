#include "hanoigl.h"
#include "main.h"
#include "stack.h"
#include "objects.h"
#include "hanoi.h"

#define DEFAULTSPEED 1

int disks;
GLfloat rotX, rotY, zoom, offsetY = 1.5, speed;
GLUquadricObj *quadric;
GLfloat pos;

stack pin[3];
float pinheight[3];
struct config config;
action *curaction;
disk *curdisk;
int last = 0;

unsigned int draw;
GLfloat duration;

static void populatePin(void)
{
	int i;
	disk *cur;
	GLfloat radius = 0.1f * disks;

	for (i = 0; i < disks; i++) {
		cur = (disk *) malloc(sizeof(disk));
		cur->color = (char)i % 6;
		cur->radius = radius;

		push(&pin[0], cur);

		radius -= 0.1;
	}
	draw = 0;
}

static void clearPins(void)
{
	int i;
	disk *cur, *tmp;

	free(curdisk);
	curdisk = NULL;

	for (i = 0; i < 3; i++) {
		cur = pin[i].top;
		while (cur != NULL) {
			tmp = cur->prev;
			free(cur);
			cur = tmp;
		}
		pin[i].top = NULL;
		pin[i].bottom = NULL;
	}
}

static void hanoiinit(void)
{
	FILE *datei;
	char buf[3];		/* two digits */
	GLfloat radius;

	if ((datei = fopen("disks.txt", "r")) != NULL) {
		fgets(buf, 3, datei);
		disks = atoi(buf);
		fclose(datei);
	}

	if (disks <= 0)
		disks = 3;

	speed = DEFAULTSPEED;

	radius = 0.1f * disks;
	config.pinradius = radius + 0.1f;
	config.gap = radius * 2 + 0.5f;
	config.pinheight = disks * BREITE + 0.2f;

	populatePin();

	curaction = (action *) malloc(sizeof(action));
	hanoi_next(draw, disks, &last, curaction, pin);
	curdisk = pop(&pin[curaction->fromstack]);
	pos = 0.001;
}

static void reset(void)
{
	clearPins();
	populatePin();
	glfwSetTime(0);
	duration = 0;

	/* reset actions */
	last = 0;
	hanoi_next(draw, disks, &last, curaction, pin);
	curdisk = pop(&pin[curaction->fromstack]);
	pos = 0.001;
}

static void setColor(const int color)
{
	switch (color) {
	case 0:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case 1:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case 2:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case 3:
		glColor3f(0.0, 1.0, 1.0);
		break;
	case 4:
		glColor3f(1.0, 0.0, 1.0);
		break;
	case 5:
		glColor3f(0.0, 0.0, 0.0);
		break;
	}
}

static void fillPins(void)
{
	int i;
	disk *cur;

	glPushMatrix();
	for (i = 0; i < 3; i++) {	/* fill pins with disks */
		glPushMatrix();
		pinheight[i] = 0;
		if ((cur = pin[i].bottom) != NULL) {
			do {
				setColor(cur->color);
				drawDisk(&quadric, cur->radius, STANGENBREITE);
				glTranslatef(0.0, BREITE, 0.0);
				pinheight[i] += BREITE;
				cur = cur->next;
			} while (cur != NULL);
		}
		glPopMatrix();
		glTranslatef(config.gap, 0.0, 0.0);
	}
	glPopMatrix();
}

void Init(void)
{
	const GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	const GLfloat mat_shininess[] = { 50.0 };
	const GLfloat light_position[] = { 0.0, 1.0, 1.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	/* draw polygons filled */
	glClearColor(1.0, 1.0, 1.0, 1.0);	/* set screen clear color */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	/* blending settings */
	glCullFace(GL_BACK);	/* don't draw backsides */

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	/* glColor should be used although lightning is used */

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);	/* nicer lightning :) */

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
}

/** Is called if the window size is changed */
void GLFWCALL reshape(void)
{
	int width, height;
	glfwGetWindowSize(&width, &height);
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 75.0);
	glMatrixMode(GL_MODELVIEW);
}

/** react to key presses */
void GLFWCALL keycb(int key, int action)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case ' ':
			rotX = 0.0;
			rotY = 0.0;
			zoom = 0.0;
			offsetY = 1.5;
			speed = DEFAULTSPEED;
			break;
		case '+':
			zoom -= 0.1;
			break;
		case '-':
			zoom += 0.1;
			break;
		case 'R':
			reset();
			break;
		case 'S':
			speed += 0.5;
			break;
		case 'X':
			speed -= 0.5;
			if (speed < 0.0)
				speed = 0.0;
			break;
		case GLFW_KEY_UP:
			rotX -= 5;
			break;
		case GLFW_KEY_DOWN:
			rotX += 5;
			break;
		case GLFW_KEY_LEFT:
			rotY -= 5;
			break;
		case GLFW_KEY_RIGHT:
			rotY += 5;
			break;
		case GLFW_KEY_PAGEUP:
			offsetY -= 0.1;
			break;
		case GLFW_KEY_PAGEDOWN:
			offsetY += 0.1;
			break;
		}
	}
}

static void display(void)
{
	GLfloat movY;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* clear scren */

	glLoadIdentity();	/* reinitialize model view matrix */

	glColor3f(0.0, 0.0, 0.0);

	gluLookAt(0.0, 0.9, 3.6 + zoom, 0.0, offsetY, 0.0, 0.0, 1.0, 0.0);	/* calculate view point */

	glRotatef(rotY, 0.0, 1.0, 0.0);	/* rotate Y axis */
	glRotatef(rotX, 1.0, 0.0, 0.0);	/* rotate X axis */

	glColor3f(0.0, 0.0, 0.5);
	drawAllPins(&quadric, config.pinradius, config.pinheight, config.gap);	/* draw pins */

	glTranslatef(-config.gap, BREITE / 2, 0.0);
	fillPins();

	if (curaction->fromstack != -1 && curdisk != NULL) {
		if (pos <= 1.0) {	/* push disk up */
			movY = pos * (config.pinheight - pinheight[curaction->fromstack]);
			glTranslatef(config.gap * curaction->fromstack, pinheight[curaction->fromstack] + movY, 0.0);
		} else {
			if (pos < 2.0 && curaction->fromstack != curaction->tostack) {
				GLfloat backward = (pos - 2.0f) * 180 + 90;
				GLfloat forward = -(pos - 2.0f) * 180 - 90;
				if (curaction->fromstack != 1 && curaction->tostack != 1) {	/* jump 2 pins */
					glTranslatef(config.gap, config.pinheight + 0.1f, 0.0);
					if (curaction->fromstack == 0)
						glRotatef(forward, 0.0, 0.0, 1.0);
					else
						glRotatef(backward, 0.0, 0.0, 1.0);
					glTranslatef(0.0, config.gap, 0.0);
				} else {	/* jump 1 pin */
					if (curaction->fromstack == 2 || curaction->tostack == 2)
						glTranslatef(config.gap / 2 * 3, config.pinheight + 0.1f, 0.0);
					else
						glTranslatef(config.gap / 2, config.pinheight + 0.1f, 0.0);

					if (curaction->fromstack < curaction->tostack)
						glRotatef(forward, 0.0, 0.0, 1.0);
					else
						glRotatef(backward, 0.0, 0.0, 1.0);

					glTranslatef(0.0, config.gap / 2, 0.0);
				}
				glRotatef(-90, 0.0, 0.0, 1.0);
			} else if (pos >= 2.0) {	/* drop disk down */
				movY = config.pinheight - (pos - 2.0f) * (config.pinheight - pinheight[curaction->tostack]);
				glTranslatef(config.gap * curaction->tostack, movY, 0.0);
			}
		}
		setColor(curdisk->color);
		drawDisk(&quadric, curdisk->radius, STANGENBREITE);
	}

	glfwSwapInterval(1);
	glfwSwapBuffers();	/* swap buffers (double buffering) */
}

void moveDisk(void)
{
	if (curaction->tostack != -1) {
		if (pos == 0.0 || pos >= 3.0) {	/* 0--1 -> disk goes upwards, 1--2 "disk in air", 2--3 disk goes downwards */
			pos = 0.0;
			draw++;
			push(&pin[curaction->tostack], curdisk);
			hanoi_next(draw, disks, &last, curaction, pin);
			if (curaction->fromstack != curaction->tostack)
				curdisk = pop(&pin[curaction->fromstack]);
		}

		pos += glfwGetTime() * speed;
		duration += glfwGetTime() * speed;
		glfwSetTime(0);

		if (pos > 3.0)
			pos = 3.0;

	} else {
		curdisk = NULL;
	}
}

int main(void)
{
	GLboolean running = GL_TRUE;

	hanoiinit();
	glfwInit();

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if (!glfwOpenWindow(800, 600, 8, 8, 8, 8, 24, 0, GLFW_WINDOW)) {
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwSetWindowTitle("Towers of Hanoi");

	Init();

	reshape();
	glfwSetKeyCallback(keycb);
	glfwSetWindowRefreshCallback(reshape);
	while (running) {
		if (curdisk != NULL || (int)glfwGetTime() < 5) {
			char buf[35 + 3 * 10];
			moveDisk();
			sprintf(buf, "Towers of Hanoi : Time: %ds : %d/%d draws", (int)duration, draw, (1 << disks) - 1);
			glfwSetWindowTitle(buf);
		} else {
			reset();
		}
		display();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	clearPins();
	gluDeleteQuadric(quadric);
	glfwTerminate();
	return EXIT_SUCCESS;
}
