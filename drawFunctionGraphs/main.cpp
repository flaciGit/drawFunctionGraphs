#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <stdlib.h>
#include <time.h>


GLfloat margin = 5;
GLfloat areaWidth = 190;

GLint glutTimerFuncValue = 5;

GLint windowWidth = 400;
GLint windowHeight = 400;

vec2 oldPn,oldPkob,oldPe,oldPep,oldPsin,oldPcos,oldPfive;

mat3 w2v;

void drawLine(float l, float m, float j, float i)
{

	glBegin(GL_LINES);
	glVertex2f(l, m);
	glVertex2f(j, i);
	glEnd();
	glFlush();
}
void drawDot(float l, float m)
{

	glBegin(GL_POINTS);
	glVertex2f(l, m);
	glEnd();
	glFlush();
}

void drawBorder(vec2 w,vec2 s) {
	drawLine(w.x, w.y, w.x, w.y+s.y);
	drawLine(w.x, w.y + s.y, w.x+s.x, w.y + s.y);
	drawLine(w.x + s.x, w.y + s.y, w.x + s.x, w.y);
	drawLine(w.x, w.y, w.x + s.x, w.y);
	drawLine(w.x, w.y+ s.x/2, w.x + s.x, w.y+s.y/2);
	drawLine(w.x+s.x/2 , w.y + s.y, w.x+ s.x/ 2, w.y);
}



// x^3
void cubicF() {

	vec2 vP = { margin,windowHeight - margin - areaWidth };
	vec2 vS = { areaWidth,areaWidth };

	vec2 wP = { -1,-1 };
	vec2 wS = {  2, 2 };

	w2v = windowToViewport2(wP, wS, vP, vS);
	
	float l = 0.01;
	int count = 0;
	bool first = true;
	//x  [-1, 1]
	for (float i = -1.0; i <= 1; i += l) {
		vec2 point = { i,i*i*i }; // y,x^3
		vec3 pointH = ihToH(point);
		vec3 resultH = w2v * pointH;

		if (resultH.z != 0) {
			vec2 result = hToIh(resultH);

			if (first) {
				first = false;
				oldPkob = {result.x, result.y};
			}
			else {

				//ne lógjon ki
				if (result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					)
					drawLine(oldPkob.x, oldPkob.y, result.x, result.y);
				oldPkob = { result.x, result.y };
			}

		}
	}

	glColor3f(0.0, 0.0, 0.0);
	drawBorder(vP,vS);

}


// 1/x
void reciprocal() {

	vec2 vP = { windowWidth-margin-areaWidth, windowHeight - margin - areaWidth };
	vec2 vS = { areaWidth,areaWidth };

	vec2 wP = { -5,-5 };
	vec2 wS = { 10, 10 };

	w2v = windowToViewport2(wP, wS, vP, vS);

	glColor3f(0.0, 1.0, 1.0);

	float l = 0.001;
	int count = 0;
	bool first = true;

	//x [-1, 1]
	for (float i = -5.0; i <= 5; i += l) {
		vec2 point = { i,1/i }; // y,1/x
		vec3 pointH = ihToH(point);
		vec3 resultH = w2v * pointH;

		if (resultH.z != 0) {
			vec2 result = hToIh(resultH);

			if (first && i < 0) {
				first = false;
				oldPe = { result.x, result.y };
			}
			else {

				if (i < 0 && result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					) {
					drawLine(oldPe.x, oldPe.y, result.x, result.y);
					oldPe = { result.x, result.y };
				}

			}

			if (!first && i > 0 &&
				result.y < vP.y + vS.y && result.y > vP.y
				&& result.x < vP.x + vS.x && result.x > vP.x
				) {
				first = true;
				oldPep = { result.x, result.y };
			}
			else {
			
				if (i > 0 && result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					) {

					drawLine(oldPep.x, oldPep.y, result.x, result.y);
					oldPep = { result.x, result.y };
				}
			}
		}
	}

	glColor3f(0.0, 0.0, 0.0);
	drawBorder(vP, vS);

}

//sin and cos
void sincos() {

	vec2 vP = { margin,margin };
	vec2 vS = { areaWidth, areaWidth };

	vec2 wP = { -2*pi(),-2*pi() };
	vec2 wS = { 4*pi(), 4*pi() };

	w2v = windowToViewport2(wP, wS, vP, vS);
	bool first = true;

	float l = 0.01;
	int count = 0;

	glColor3f(1.0, 0.0, 0.0);

	for (float i = -2*pi(); i <= 2*pi(); i += l) {
		vec2 point = { i,float(sin(i)) }; // y, sin(x)
		vec3 pointH = ihToH(point);
		vec3 resultH = w2v * pointH;

		if (resultH.z != 0) {
			vec2 result = hToIh(resultH);

			if (first) {
				first = false;
				oldPsin = { result.x, result.y };
			}
			else {

				if (result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					)
					drawLine(oldPsin.x, oldPsin.y, result.x, result.y);
				oldPsin = { result.x, result.y };
			}
		}
	}

	//cos
	glColor3f(0.0, 1.0, 0.0);

	for (float i = -2 * pi(); i <= 2 * pi(); i += l) {
		vec2 point = { i,float(cos(i)) }; // y, cos(x)
		vec3 pointH = ihToH(point);
		vec3 resultH = w2v * pointH;

		if (resultH.z != 0) {
			vec2 result = hToIh(resultH);

			if (first) {
				first = false;
				oldPcos = { result.x, result.y };
			}
			else {

				if (result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					)
					drawLine(oldPcos.x, oldPcos.y, result.x, result.y);
				oldPcos = { result.x, result.y };
			}

		}
	}

	glColor3f(0.0, 0.0, 0.0);
	drawBorder(vP, vS);

}

//5.
void fifthone() {

	vec2 vP = { windowWidth - margin - areaWidth, margin };
	vec2 vS = { areaWidth,areaWidth };

	vec2 wP = { float(-1.5*pi()-2.5*pi()),float(-1.5*pi() - 2.5*pi()) };
	vec2 wS = { float( 1.5*pi()+2.5*pi() )*2 , float(1.5*pi() + 2.5*pi())*2 };

	w2v = windowToViewport2(wP, wS, vP, vS);

	float l = 0.001;
	int count = 0;
	bool first = true;
	
	for (float i = -1.5*pi(); i <= 2.5*pi(); i += l) {
		vec2 point = {   float(i-1.6*cos(24 * i)) , float(i - 1.6*sin(25 * i)) };
		vec3 pointH = ihToH(point);
		vec3 resultH = w2v * pointH;


		if (resultH.z != 0) {
			vec2 result = hToIh(resultH);

			if (first) {
				first = false;
				oldPfive = { result.x, result.y };
			}
			else {

				if (result.y < vP.y + vS.y && result.y > vP.y
					&& result.x < vP.x + vS.x && result.x > vP.x
					)
					drawLine(oldPfive.x, oldPfive.y, result.x, result.y);
				oldPfive = { result.x, result.y };
				
			}
		}
	}
	
	glColor3f(0.0, 0.0, 0.0);
	drawBorder(vP, vS);

}


void init()
{
	srand(time(NULL));
	glEnable(GL_POINT_SMOOTH);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glShadeModel(GL_FLAT);

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	cubicF();
	reciprocal();
	sincos();
	fifthone();
	glutSwapBuffers();
}

void update(int n)
{
	glutPostRedisplay();
	glutTimerFunc(glutTimerFuncValue, update, 0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutIgnoreKeyRepeat(1);
	init();
	glutDisplayFunc(display);
	glutTimerFunc(glutTimerFuncValue, update, 0);
	glutMainLoop();
	return 0;
}
