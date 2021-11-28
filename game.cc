/*
	Sinenomine (puzzle game)
	Copyright (C) 2008 Julius Schmidt
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but without any warranty; without even the implied warranty of
	merchantability or fitness for a particular purpose. See the
	GNU General Public License for more details.

	You are able to access a copy of the GNU General Public License at
	 http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
	or write to the Free Software Foundation, Inc., 51 Franklin Street,
	Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_gfxPrimitives_font.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <sstream>

/*
Obstacles
0 - energy drain (par: range)
1 - energy dispenser (par: speed, par2: max)
2 - wall (p: start, q: end)
3 - teleporter (par: min energy, q: target)
4 - switch (par: obstacle id, par2: value)
5 - force field generator (par: range)
6 - "clic-clac" timer (par: obstacle id, p: times, q: states)
7 - barrier (p: start, q: end, par: destructible?)
8 - wall switch (p: start, q: end, par: obstacle id, par2: value)
9 - cannon (par: power, par2: energy)
10 - cannon control pad (par: obstacle id)
11 - simple enemy (p: start, q: end, par: offset)
12 - follow enemy (varparam: position, par: range)
13 - "on-off" timer (par: obstacle id, q: (on, off), varparam: time)
14 - hub (par, par2, p, q: obstacle ids)
*/
const int nobst = 13;

const int resx = 1024, resy = 768;
const float pw = 1;
SDL_Surface* display;
float grad = -45;
int mx, my;
float mX, mY;
bool showtime;

class Point {
public:
	float x, y;
	Point(float X=0, float Y=0) {x=X; y=Y;}
	Point operator +(Point a) const {return Point(x+a.x, y+a.y);}
	Point operator -(Point a) const {return Point(x-a.x, y-a.y);}
	Point operator *(float k) const {return Point(x*k, y*k);}
	Point operator /(float k) const {return Point(x/k, y/k);}
	float len() const {return sqrt(x*x + y*y);}
	Point norm() const {if (len() != 0) return Point(x/len(), y/len()); return Point(0, 0);}
};

float del(Point a, Point b) {float A = a.x - b.x; float B = a.y - b.y; return sqrt(A*A + B*B);}
int sgn(float a) {if (a < 0) return -1; if (a > 0) return 1; return 0;}
template <class T> T min(T a, T b) {if (a < b) return a; return b;}
template <class T> T max(T a, T b) {if (a < b) return b; return a;}

inline std::string toString(float f) {
	std::ostringstream o;
	o << f;
	return o.str();
}

class Obstacle {
public:
	Point p;
	Point q;
	int t;
	float par, par2, par3;
	Obstacle(Point P, int T, float Par=0, Point Q=Point(0,0), float Par2=0, float Par3=0) {p=P; t=T; par=Par; q=Q; par2=Par2; par3=Par3;}
	Obstacle(Point P, int T, float Par, float Par2, float Par3=0) {p=P; t=T; par=Par; par2=Par2; par3=Par3;}
};

class Shot {
public:
	float t;
	Point p;
	Point d;
	float v;
	Shot(float T, Point P, Point D, float V) {t=T; p=P; d=D; v=V;};
};

class State {
public:
	float t, T;
	Point p;
	bool success;
	float energy, sumEnergy;
	int canon;
	bool canon_bool;
	std::vector<Shot> shots;
	std::map<int, Point> varparam;
	State() {canon = -1; t = 0;}
	float par(int i) {return varparam[i].x;}
	Point ppar(int i) {return varparam[i];}
	void spar(int i, float v) {spar(i, Point(v,0));}
	void spar(int i, Point v) {if (i >= 0) varparam[i] = v;}
	std::map<int, bool> removed;
	bool exists(int i) {return !removed[i];}
	bool nexists(int i) {return removed[i];}
	void setthere(int i, bool b) {removed[i] = !b;}
	void show(int i) {removed[i] = false;}
	void hide(int i) {removed[i] = true;}
} state;

class Map {
public:
	float u, d, r, l;
	Point target;
	State begin;
	float portalmin;
	std::vector<Obstacle> obstacles;
} map;

const int nmap = 8;
Map maps[nmap];
int cmap = -1;

void
nextmap()
{
	if (state.T > 0 && showtime)
		printf("Level %d: Time %g, Energy %g\n", cmap+1, int(10*state.T)/10., state.sumEnergy);
	cmap++;
	if (cmap >= nmap) cmap = 0;
	map = maps[cmap];
	state = map.begin;
}

void
initMaps()
{
	maps[0].u = maps[0].r = 10;
	maps[0].d = maps[0].l = -10;
	maps[0].target = Point(-2, -2);
	maps[0].begin.p = Point(2, 3);
	//------------------
	maps[1].u = maps[1].r = 10;
	maps[1].d = maps[1].l = -10;
	maps[1].target = Point(5, -5);
	maps[1].begin.p = Point(-5, -5);
	maps[1].portalmin = 10;
	maps[1].obstacles.push_back(Obstacle(Point(0, 5), 1, 1, 10));
	maps[1].obstacles.push_back(Obstacle(Point(-7, 0), 2, 0, Point(7, 0)));
	//------------------
	maps[2].u = maps[2].r = 10;
	maps[2].d = maps[2].l = -10;
	maps[2].target = Point(-5, -5);
	maps[2].begin.p = Point(7, 7);
	maps[2].portalmin = 10;
	maps[2].obstacles.push_back(Obstacle(Point(5, 5), 1, 1, 10));
	maps[2].obstacles.push_back(Obstacle(Point(-5, 5), 0, 8));
	maps[2].obstacles.push_back(Obstacle(Point(5, -5), 5, 8));
	//------------------
	maps[3].u = maps[3].r = 10;
	maps[3].d = maps[3].l = -10;
	maps[3].target = Point(-7, 7);
	maps[3].begin.p = Point(5, 0);
	maps[3].portalmin = 10;
	maps[3].obstacles.push_back(Obstacle(Point(0, -10), 2, 0, Point(0, 10)));
	maps[3].obstacles.push_back(Obstacle(Point(7, 0), 1, 1, 5));
	maps[3].obstacles.push_back(Obstacle(Point(7, -7), 3, 5, Point(-7, -7)));
	maps[3].obstacles.push_back(Obstacle(Point(0, 0), 2, 0, Point(-10, 0)));
	maps[3].obstacles.push_back(Obstacle(Point(-7, -7), 1, 1, 10));
	maps[3].obstacles.push_back(Obstacle(Point(7, 7), 4, 3, 1));
	//------------------
	maps[4].u = 20;
	maps[4].r = 10;
	maps[4].d = maps[4].l = -10;
	maps[4].target = Point(5, -5);
	maps[4].begin.p = Point(-5, -5);
	maps[4].portalmin = 10;
	maps[4].obstacles.push_back(Obstacle(Point(0, -5), 1, 1, 5));
	maps[4].obstacles.push_back(Obstacle(Point(-10, 0), 2, 0, Point(10, 0)));
	maps[4].obstacles.push_back(Obstacle(Point(-5, 15), 3, 5, Point(5, 15)));
	maps[4].obstacles.push_back(Obstacle(Point(-10, 10), 2, 0, Point(0, 10)));
	maps[4].obstacles.push_back(Obstacle(Point(1, 1), 6, 3, Point(0, 1)));
	maps[4].obstacles.push_back(Obstacle(Point(0, 5), 0, 5));
	maps[4].obstacles.push_back(Obstacle(Point(5, 15), 1, 1, 10));
	maps[4].obstacles.push_back(Obstacle(Point(0, 10), 7, 0, Point(10, 10)));
	maps[4].obstacles.push_back(Obstacle(Point(0, 10), 7, 0, Point(0, 20)));
	maps[4].obstacles.push_back(Obstacle(Point(0, 11), 8, 7, Point(11, 10), 1));
	maps[4].obstacles.push_back(Obstacle(Point(1, 1), 6, 1, Point(1, 0)));
	//------------------
	maps[5].l = maps[5].d = 0;
	maps[5].u = 30;
	maps[5].r = 30;
	maps[5].begin.p = Point(3, 3);
	maps[5].target = Point(27, 27);
	maps[5].portalmin = 10;
	maps[5].obstacles.push_back(Obstacle(Point(7, 7), 1, 10, 10));
	#define tele(X, Y, Z) \
	maps[5].obstacles.push_back(Obstacle(Point((X-1)%3*10+3, (X-1)/3*10+7), 3, 10, Point((Y-1)%3*10+3, (Y-1)/3*10+3)));\
	maps[5].obstacles.push_back(Obstacle(Point((X-1)%3*10+7, (X-1)/3*10+3), 3, 10, Point((Z-1)%3*10+3, (Z-1)/3*10+3)))
	tele(1,2,4);
	tele(2,8,5);
	tele(3,9,1);
	tele(4,5,7);
	tele(5,1,3);
	tele(6,7,2);
	tele(7,8,6);
	tele(8,3,6);
	#undef tele

	maps[5].obstacles.push_back(Obstacle(Point(0, 10), 2, 0, Point(30, 10)));
	maps[5].obstacles.push_back(Obstacle(Point(0, 20), 2, 0, Point(30, 20)));
	maps[5].obstacles.push_back(Obstacle(Point(10, 0), 2, 0, Point(10, 30)));
	maps[5].obstacles.push_back(Obstacle(Point(20, 0), 2, 0, Point(20, 30)));
	//------------------
	maps[6].u = 10;
	maps[6].d = maps[6].l = -10;
	maps[6].r = 20;
	maps[6].begin.p = Point(0, 0);
	maps[6].target = Point(5, 5);
	maps[6].portalmin = 10;
	maps[6].obstacles.push_back(Obstacle(Point(7, 10), 7, 0, Point(7, -10)));
	maps[6].obstacles.push_back(Obstacle(Point(-3, 10), 7, 0, Point(-3, -10)));
	maps[6].obstacles.push_back(Obstacle(Point(-7, 0), 1, 1, 10));
	maps[6].obstacles.push_back(Obstacle(Point(17, 0), 4, 1, 1));
	maps[6].obstacles.push_back(Obstacle(Point(5, 0), 9, 5, 0));
	maps[6].obstacles.push_back(Obstacle(Point(5, -5), 10, 4));
	//------------------
	{
	maps[7].u = maps[7].r = 30;
	maps[7].d = maps[7].l = -30;
	maps[7].begin.p = Point(-27, 3);
	maps[7].target = Point(27, 0);
	maps[7].portalmin = 10;
	maps[7].obstacles.push_back(Obstacle(Point(2, 2), 7, 0, Point(-2, 2)));
	maps[7].obstacles.push_back(Obstacle(Point(0, 0), 9, 10, .5)); int canonid = maps[7].obstacles.size() - 1;
	maps[7].obstacles.push_back(Obstacle(Point(-27, -3), 10, canonid));
	for (int i=0; i<7; i++)
		maps[7].obstacles.push_back(Obstacle(Point(-24+3*i, -4), 11, 2*i, Point(-24+3*i, 4)));
	maps[7].obstacles.push_back(Obstacle(Point(0, -27), 1, 1, 10));
	maps[7].obstacles.push_back(Obstacle(Point(0, 0), 12, 10)); maps[7].begin.spar(maps[7].obstacles.size() - 1, Point(0, -20));
	int xid = maps[7].obstacles.size();
	for (int i=0; i<5; i++)
		maps[7].obstacles.push_back(Obstacle(Point((i%2)?-4:4, 9+4*i), 0, 5));
	maps[7].obstacles.push_back(Obstacle(Point(xid,xid+1), 14, xid+2, Point(xid+3, xid+4), -1));
	maps[7].obstacles.push_back(Obstacle(Point(0, 0), 13, xid+5, Point(1, 0)));
	maps[7].obstacles.push_back(Obstacle(Point(-5, 5), 8, xid+6, Point(5, 5), 1));
	maps[7].obstacles.push_back(Obstacle(Point(20, -5), 2, 0, Point(20, 5)));
	maps[7].obstacles.push_back(Obstacle(Point(-4, 29), 4, xid+8, 1, 7));

	maps[7].obstacles.push_back(Obstacle(Point(-30, 5), 7, 0, Point(-5, 5)));
	maps[7].obstacles.push_back(Obstacle(Point(-30, -5), 7, 0, Point(-5, -5)));
	maps[7].obstacles.push_back(Obstacle(Point(30, 5), 7, 0, Point(5, 5)));
	maps[7].obstacles.push_back(Obstacle(Point(30, -5), 7, 0, Point(5, -5)));
	maps[7].obstacles.push_back(Obstacle(Point(5, 30), 7, 0, Point(5, 5)));
	maps[7].obstacles.push_back(Obstacle(Point(-5, 30), 7, 0, Point(-5, 5)));
	maps[7].obstacles.push_back(Obstacle(Point(5, -30), 7, 0, Point(5, -5)));
	maps[7].obstacles.push_back(Obstacle(Point(-5, -30), 7, 0, Point(-5, -5)));

	maps[7].obstacles.push_back(Obstacle(Point(-2, -2), 7, 0, Point(-2, 2)));
	maps[7].obstacles.push_back(Obstacle(Point(2, -2), 7, 0, Point(2, 2)));
	maps[7].obstacles.push_back(Obstacle(Point(2, -2), 7, 0, Point(-2, -2)));
	maps[7].obstacles.push_back(Obstacle(Point(-5, -5), 7, 0, Point(5, -5))); maps[7].begin.spar(maps[7].obstacles.size() - 1, Point(1,1));
	maps[7].obstacles.push_back(Obstacle(Point(17, -5), 7, 1, Point(17, 5)));
	}
	nextmap();
};

Point
senemypos(Point p, Point q, float off)
{
	float z = sin(2*state.t + off)/2+0.5;
	return p*z + q*(1-z);
}

bool
linecircle(Point p, Point q, Point r, float rad = pw)
{
	if (p.y == q.y) {
		if (r.y > p.y - rad && r.y < p.y + rad)
			if (r.x > min(p.x, q.x) - rad && r.x < max(p.x, q.x) + rad)
				return true;
		return false;
	}
	if (p.x == q.x) {
		if (r.x > p.x - rad && r.x < p.x + rad)
			if (r.y > min(p.y, q.y) - rad && r.y < max(p.y, q.y) + rad)
				return true;
		return false;
	}
	Point A = Point((p.x - r.x), (p.y - r.y));
	Point B = Point((q.x - r.x), (q.y - r.y));
	float dx = B.x - A.x;
	float dy = B.y - A.y;
	float dr = sqrt(dx*dx + dy*dy);
	float D = A.x*B.y - A.y*B.x;
	float Del = rad*dr*dr - D*D;
	Point X = Point((D*dy + ((dy>=0)?1:-1)*dx*sqrt(rad*dr*dr - D*D))/dr/dr, (-D*dy + fabs(dy)*sqrt(rad*dr*dr - D*D))/dr/dr);
	Point Y = Point((D*dy - ((dy>=0)?1:-1)*dx*sqrt(rad*dr*dr - D*D))/dr/dr, (-D*dy - fabs(dy)*sqrt(rad*dr*dr - D*D))/dr/dr);
	if (Del > 0) {
		float t1 = -1, t2 = -1;
		if (A.x != B.x)
			t1 = (X.x - A.x)/(B.x - A.x);
		else
			t1 = (X.y - A.y)/(B.y - A.y);
		if (A.x != B.x)
			t2 = (Y.x - A.x)/(B.x - A.x);
		else
			t2 = (Y.y - A.y)/(B.y - A.y);
		if ((t1 > 0 && t1 < 1) || (t2 > 0 && t2 < 1))
			return true;
	}
	return false;
}


void
rect(float w, float h, float r, float g, float b, float a)
{
	glBegin(GL_QUADS);
	glColor4f(r,g,b,a);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w,  h, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( w,  h, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( w, -h, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-w, -h, 0);
	glEnd();
}

void
CreateSphere(double r, int n)
{
	int i, j;
	double theta1, theta2, theta3;
	struct {
		double x, y, z;
	} e, p;
	const float TWOPI = 2*M_PI;
	const float PID2 = M_PI/2;

	if (r < 0)
	  r = -r;
	if (n < 0)
	  n = -n;
	if (n < 4 || r <= 0) {
	  glBegin(GL_POINTS);
	  glVertex3f(0, 0, 0);
	  glEnd();
	  return;
	}

	for (j=0; j<n/2; j++) {
	  theta1 = j * TWOPI / n - PID2;
	  theta2 = (j + 1) * TWOPI / n - PID2;

	  glBegin(GL_QUAD_STRIP);
	  for (i=0; i<=n; i++) {
	     theta3 = i * TWOPI / n;

	     e.x = cos(theta2) * cos(theta3);
	     e.y = sin(theta2);
	     e.z = cos(theta2) * sin(theta3);
	     p.x = r * e.x;
	     p.y = r * e.y;
	     p.z = r * e.z;

	     glNormal3f(e.x,e.y,e.z);
	     glTexCoord2f(i/(double)n, 2*(j+1)/(double)n);
	     glVertex3f(p.x,p.y,p.z);

	     e.x = cos(theta1) * cos(theta3);
	     e.y = sin(theta1);
	     e.z = cos(theta1) * sin(theta3);
	     p.x = r * e.x;
	     p.y = r * e.y;
	     p.z = r * e.z;

	     glNormal3f(e.x,e.y,e.z);
	     glTexCoord2f(i/(double)n, 2*j/(double)n);
	     glVertex3f(p.x,p.y,p.z);
	  }
	  glEnd();
	}
}

GLuint lobst[nobst];
GLuint circle, sphere;
GLuint font[255];

void
initLists()
{
	{
		circle = glGenLists(1);
		glNewList(circle, GL_COMPILE);
		const int N = 100;
		glBegin(GL_LINE_LOOP);
		for (float T=2*M_PI/N;T<2*M_PI;T+=2*M_PI/N)
			glVertex2f(cos(T), sin(T));
		glEnd();
		glEndList();
	}
	{
		sphere = glGenLists(1);
		glNewList(sphere, GL_COMPILE);
		CreateSphere(1, 100);
		glEndList();
	}
	{
		lobst[0] = glGenLists(1);
		glNewList(lobst[0], GL_COMPILE);
		glBegin(GL_QUADS);
		const float N = 100;
		const float DU = 2*M_PI/N;
		const float DV = 4./N;
		for (float U=0;U<2*M_PI;U+=DU)
			for (float V=0;V<4;V+=DV) {
				glVertex3f(sin(U), cos(U), V);
				glVertex3f(sin(U+DU), cos(U+DU), V);
				glVertex3f(sin(U+DU), cos(U+DU), V+DV);
				glVertex3f(sin(U), cos(U), V+DV);
			}
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(0.5, 1, 1);
		for (float T=0;T<2*M_PI;T+=2*M_PI/N)
			glVertex3f(cos(T), sin(T), 4);
		glEnd();
		glEndList();
	}
	{
		lobst[1] = glGenLists(1);
		glNewList(lobst[1], GL_COMPILE);
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
		const int N = 100;
		for (float T=0;T<2*M_PI;T+=2*M_PI/N)
			glVertex2f(cos(T)*(fabs(sin(2*T))+0.5)*0.7*pw, sin(T)*(fabs(sin(2*T))+0.5)*0.7*pw);
		glEnd();
		glEndList();
	}
	{
		lobst[4] = glGenLists(1);
		glNewList(lobst[4], GL_COMPILE);
		glBegin(GL_POLYGON);
		const int N = 7;
		for (float T=0;T<2*M_PI;T+=2*M_PI/N)
			glVertex2f(cos(T)*1.15*pw, sin(T)*1.15*pw);
		glEnd();
		glEndList();
	}
	{
		lobst[9] = glGenLists(1);
		glNewList(lobst[9], GL_COMPILE);
		const float N = 100;
		const float DU = 2*M_PI/N;
		const float DV = 4./N;
		glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		for (float U=0;U<2*M_PI;U+=DU)
			for (float V=0;V<4;V+=DV) {
				glVertex3f(sin(U)*0.5, cos(U)*0.5, V);
				glVertex3f(sin(U+DU)*0.5, cos(U+DU)*0.5, V);
				glVertex3f(sin(U+DU)*0.5, cos(U+DU)*0.5, V+DV);
				glVertex3f(sin(U)*0.5, cos(U)*0.5, V+DV);
			}
		glEnd();
		glTranslatef(0, 0, 3.85);
		glBegin(GL_POLYGON);
		for (float T=0;T<2*M_PI;T+=2*M_PI/N)
			glVertex3f(cos(T)*0.5, sin(T)*0.5, 0);
		glEnd();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS);
		for (float U=0;U<2*M_PI;U+=DU)
			for (float V=0;V<2;V+=DV) {
				glVertex3f(sin(U)*0.5, cos(U)*0.5, V);
				glVertex3f(sin(U+DU)*0.5, cos(U+DU)*0.5, V);
				glVertex3f(sin(U+DU)*0.5, cos(U+DU)*0.5, V+DV);
				glVertex3f(sin(U)*0.5, cos(U)*0.5, V+DV);
			}
		glEnd();
		glEndList();
	}
	font[0] = glGenLists(256);
	for (int i=0; i<255; i++) {
		font[i] = font[0] + i;
		glNewList(font[i], GL_COMPILE);
		for (int j=0; j<8; j++) {
			unsigned char c = gfxPrimitivesFontdata[i*8+j];
			for (int k=0;k<8;k++)
				if (c & (1 << (7-k))) {
					glBegin(GL_QUADS);
					glVertex2f(.125*k, .125*j);
					glVertex2f(.125*k, .125*(j+1));
					glVertex2f(.125*(k+1), .125*(j+1));
					glVertex2f(.125*(k+1), .125*j);
					glEnd();
				}
		}
		glEndList();
	}
}

void
orthogonal()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void
nonorthogonal()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0 * resx / resy, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void
write(float x, float y, std::string str)
{
	orthogonal();
	glTranslatef(x, y, 0);
	glScalef(1/80., 1/25., 1);
	for (int i=0; i<str.size(); i++) {
		glCallList(font[str[i]]);
		glTranslatef(1, 0, 0);
	}
	nonorthogonal();
}

void
drawscene()
{
	GLUquadric* quadratic;
	glLoadIdentity();
	glColor3f(1,1,1);
	if (showtime) {
		write(0, 0, "Time: " + toString(int(10*((state.success) ? state.T : state.t))/10.));
		write(0.5, 0, "Energy: " + toString(state.sumEnergy));
	}
	glTranslatef(0, 0, (state.canon < 0) ? -20 : (- 30 - map.obstacles[state.canon].par));
	if (state.canon < 0)
		glRotatef(grad, 1, 0, 0);
	if (state.canon >= 0) glTranslatef(-map.obstacles[state.canon].p.x, -map.obstacles[state.canon].p.y, 0);
	if (!state.success) {
		glPushMatrix();
		if (state.canon >= 0) glTranslatef(state.p.x, state.p.y, 0);
		glScalef(pw, pw, pw);
		if (map.portalmin > 0) {
			float p = state.energy/map.portalmin;
			glColor3f(1-p, 1-p, 1);
		} else {
			glColor3f(1, 1, 1);
		}
		glCallList(sphere);
		glPopMatrix();
	}
	if (state.canon < 0)
		glTranslatef(-state.p.x, -state.p.y, 0);
	glPushMatrix();
	glTranslatef((map.l+map.r)/2., (map.u+map.d)/2, 0);

	{
		const float x = (map.r-map.l)/2;
		const float y = (map.u-map.d)/2;
		const float z = 20;
		rect(x, y, 0, .39, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(0, .29, 0);
		glVertex3f(-x, -y, 0);
		glVertex3f(-x, -y, -z);
		glVertex3f(x, -y, -z);
		glVertex3f(x, -y, 0);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(map.target.x, map.target.y, 0.1);
	glScalef(1.15*pw, 1.15*pw, 1.15*pw);
	float x = 1, y = 0;

	for (int i=0; i<10; i++) {
		const int N = 100;
		if (state.success)
			glTranslatef(0, 0, (sin((1+pw)*M_PI/2*state.t)+1)/4);
		else
			glTranslatef(0, 0, 0.05*(sin(10*state.t)+1.5));
		if (state.energy >= map.portalmin)
			glColor3f(0,1,0);
		else
			glColor3f(1,0,0);
		glCallList(circle);
	}
	glPopMatrix();
	for (int i=0; i<map.obstacles.size(); i++) {
		if (state.nexists(i))
			continue;
		if (map.obstacles[i].t == 0) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			if (state.par(i) > 0.5)
				glColor3f(0, 1, 0);
			else
				glColor3f(0, 1, 1);
			glCallList(lobst[0]);
			glPopMatrix();
			if (del(state.p, map.obstacles[i].p) < map.obstacles[i].par && state.par(i) < 0.5) {
				glBegin(GL_LINE_STRIP);
				glColor3f(1,1,0);
				Point A = state.p;
				Point B = map.obstacles[i].p;
				const int n = 10;
				for (float T=0;T<=1;T+=1./n) {
					float z1 = 1.*rand()/RAND_MAX;
					float z2 = 1.*rand()/RAND_MAX;
					float z3 = 1.*rand()/RAND_MAX;
					glVertex3f(A.x + (B.x-A.x)*T + z1 - 0.5, A.y + (B.y-A.y)*T + z2 - 0.5, 4*T + z3 - 0.5);
				}
				glEnd();
			}
		}
		if (map.obstacles[i].t == 1) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			glCallList(lobst[1]);
			glPopMatrix();
		}
		if (map.obstacles[i].t == 2) {
			glPushMatrix();
			glBegin(GL_QUADS);
			if (state.par(i) > 0.5)
				glColor4f(0, 1, 0, 0.5);
			else
				glColor4f(1, 0, 0, 0.5);
			glVertex3f(map.obstacles[i].p.x, map.obstacles[i].p.y, 0);
			glVertex3f(map.obstacles[i].q.x, map.obstacles[i].q.y, 0);
			glVertex3f(map.obstacles[i].q.x, map.obstacles[i].q.y, 4);
			glVertex3f(map.obstacles[i].p.x, map.obstacles[i].p.y, 4);
			glEnd();
			glPopMatrix();
		}
		if (map.obstacles[i].t == 3) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			const int N = 100;
			float x = 1, y = 0;
			for (int j=0; j<10; j++) {
				glTranslatef(0, 0, 0.05*(sin(10*state.t)+1.5));
				glBegin(GL_LINE_LOOP);
				if (state.energy >= map.obstacles[i].par)
					glColor3f(0,1,0);
				else
					glColor3f(1,0,0);
				glVertex2f(1.15*pw, 1.15*pw);
				glVertex2f(-1.15*pw, 1.15*pw);
				glVertex2f(-1.15*pw, -1.15*pw);
				glVertex2f(1.15*pw, -1.15*pw);
				glEnd();
			}
			glPopMatrix();
		}
		if (map.obstacles[i].t == 4) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			if (state.energy >= map.obstacles[i].par3)
				glColor3f(1, 0, 1);
			else
				glColor3f(1, 0, 0);
			glCallList(lobst[4]);
			glPopMatrix();
		}
		if (map.obstacles[i].t == 5) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			glBegin(GL_POLYGON);
			glColor3f(0, 1, 1);
			glVertex3f(0, 0, 4);
			glVertex3f(1, 1, 0);
			glVertex3f(1, -1, 0);
			glVertex3f(-1, -1, 0);
			glVertex3f(-1, 1, 0);
			glEnd();
			float T = fmod(4*state.t, pw);
			for (float j=0; j<map.obstacles[i].par; j+=pw) {
				glPushMatrix();
				float R = T + pw*j;
				glScalef(R, R, R);
				if ((j + pw) >= map.obstacles[i].par)
					glColor4f(0, 1, 1, pw - fmod(4*state.t, pw));
				glCallList(circle);
				glPopMatrix();
			}
			glPopMatrix();
/*			if (del(state.p, map.obstacles[i].p) < map.obstacles[i].par) {
				glBegin(GL_LINE_STRIP);
				glColor3f(sin(4*t)/2+0.5, sin(4*t+2*M_PI/3)/2+0.5, sin(4*t+4*M_PI/3)/2+0.5);
				glVertex3f(map.obstacles[i].p.x, map.obstacles[i].p.y, 4);
				glVertex3f(state.p.x, state.p.y, 0);
				glEnd();
			}
*/
		}
		if (map.obstacles[i].t == 7) {
			glPushMatrix();
			glBegin(GL_QUADS);
			if (map.obstacles[i].par < 0.5) {
				if (state.par(i) > 0.5)
					glColor4f(1, 1, 1, 0.5);
				else
					glColor4f(0, 0, 0, 0.5);
			} else
				glColor4f(0.459, .231, 0, 0.7);
			glVertex3f(map.obstacles[i].p.x, map.obstacles[i].p.y, 0);
			glVertex3f(map.obstacles[i].q.x, map.obstacles[i].q.y, 0);
			glVertex3f(map.obstacles[i].q.x, map.obstacles[i].q.y, 4);
			glVertex3f(map.obstacles[i].p.x, map.obstacles[i].p.y, 4);
			glEnd();
			glPopMatrix();
		}
		if (map.obstacles[i].t == 9) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0);
			if (state.canon >= 0) {
				float angle = -atan2(mY, mX)/M_PI*180;
				glRotatef(angle, 0, 0, 1);
			}
			glCallList(lobst[9]);
			glPopMatrix();
		}
		if (map.obstacles[i].t == 10) {
			glPushMatrix();
			glTranslatef(map.obstacles[i].p.x, map.obstacles[i].p.y, 0.1);
			glBegin(GL_QUADS);
			if (state.energy >= map.obstacles[(int)map.obstacles[i].par].par2)
				glColor3f(1, 0, 1);
			else
				glColor3f(1, 0, 0);
			glVertex2f(-1.2, -1.2);
			glVertex2f(1.2, -1.2);
			glVertex2f(1.2, 1.2);
			glVertex2f(-1.2, 1.2);
			glEnd();
			glPopMatrix();
		}
		if (map.obstacles[i].t == 11) {
			glPushMatrix();
			Point p = senemypos(map.obstacles[i].p, map.obstacles[i].q, map.obstacles[i].par);
			glTranslatef(p.x, p.y, 0.1);
			glColor3f(0, 1, 1);
			glCallList(sphere);
			glPopMatrix();
		}
		if (map.obstacles[i].t == 12) {
			glPushMatrix();
			glTranslatef(state.ppar(i).x, state.ppar(i).y, 0.1);
			if (state.energy > 0) glRotatef(90-atan2(-state.ppar(i).y + state.p.y, state.ppar(i).x - state.p.x)/M_PI*180, 0, 0, 1);
			glBegin(GL_POLYGON);
			if (state.energy == 0)
				glColor3f(0, 1, 0);
			else
				glColor3f(0, 1, 1);
			glVertex3f(0, 2, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(-1, 0, 0);
			glEnd();
			glPopMatrix();
		}
	}
	for (int i=0; i<state.shots.size(); i++) {
		glPushMatrix();
		float X, Y, Z, T;
		const float k = 1;
		T = 10*(state.t - state.shots[i].t);
		X = state.shots[i].p.x + sqrt(2)/2*state.shots[i].v*T*state.shots[i].d.x;
		Y = state.shots[i].p.y - sqrt(2)/2*state.shots[i].v*T*state.shots[i].d.y;
		Z = -k*T*T/2 + sqrt(2)/2*state.shots[i].v*T + 4;
		glTranslatef(X, Y, Z);
		glScalef(0.3, 0.3, 0.3);
		glColor3f(1, 1, 0);
		glCallList(sphere);
		glPopMatrix();	
		bool F = false;
		for (int j=0; j<map.obstacles.size(); j++) {
			if (!(map.obstacles[j].t == 7 && map.obstacles[j].par > 0.5 && Z < 4 && linecircle(map.obstacles[j].p, map.obstacles[j].q, Point(X, Y), 0.5))) continue;
			state.hide(j);
			state.shots.erase(state.shots.begin()+i);
			F = true;
			break;
		}
		if (Z < -0.3 && !F) {
			state.shots.erase(state.shots.begin()+i);
			for (int j=0; j<map.obstacles.size(); j++) {
				if (state.nexists(j)) continue;
				if (map.obstacles[j].t == 4 && del(Point(X, Y), map.obstacles[j].p) < pw)
					state.spar((int)map.obstacles[j].par, map.obstacles[j].par2);
				if (map.obstacles[j].t == 11 && del(Point(X, Y), senemypos(map.obstacles[j].p, map.obstacles[j].q, map.obstacles[j].par)) < (pw+1))
					state.hide(j);
				if (map.obstacles[j].t == 12 && del(Point(X, Y), state.ppar(j)) < pw)
					state.hide(j);
			}
			i--;
		}
	}
	if (state.success) {
		glPushMatrix();
		glTranslatef(state.p.x, state.p.y, 4*state.t);
		glScalef(pw, pw, pw);
		glColor4f(1, 1, 1, 2+pw-4*state.t);
		glCallList(sphere);
		glPopMatrix();
	}
}

bool
validpos(Point p, int mode=0)
{
	if (p.x+pw > map.r || p.x-pw < map.l || p.y+pw > map.u || p.y-pw < map.d)
		return false;
	for (int i=0; i<map.obstacles.size(); i++)
		if (map.obstacles[i].t == 7 && linecircle(map.obstacles[i].p, map.obstacles[i].q, p, (mode == 1)?3.3:pw) && (state.par(i) < 0.5 || mode == 1) && state.exists(i))
			return false;
	return true;
}

int
main(int argc, char** argv)
{
	srand(time(0));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	display = SDL_SetVideoMode(resx, resy, 32, SDL_OPENGL);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_Hint, GL_NICEST);
	glViewport(0, 0, resx, resy);
	nonorthogonal();
	atexit(SDL_Quit);

	initLists();
	initMaps();

	bool running = true;
	bool mau = false;
	while (running) {
		SDL_Event event;
		unsigned long ticks = SDL_GetTicks();
		SDL_GetMouseState(&mx, &my);
		mX = 2.0*mx/resx-1;
		mY = 2.0*my/resy-1;
		while (SDL_PollEvent(&event))
			switch (event.type) {
				case SDL_QUIT: running = false; break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: running = false;
						case 'r': state = map.begin; break;
						case 't': showtime = !showtime; break;
						case SDLK_PAGEUP: if (grad > -90) grad-=1; break;
						case SDLK_PAGEDOWN: if (grad < 0) grad+=1; break;
					}
				break;	
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT && state.canon < 0)
						mau = true;
				break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (!mau && state.canon >= 0 && state.energy >= map.obstacles[state.canon].par2) {
							state.shots.push_back(Shot(state.t, map.obstacles[state.canon].p, Point(mX, mY).norm(), map.obstacles[state.canon].par*sqrt(mX*mX+mY*mY)));
							state.energy -= map.obstacles[state.canon].par2;
							if (state.energy < map.obstacles[state.canon].par2)
								event.button.button = SDL_BUTTON_RIGHT;
						}
						mau = false;
					}
					if (event.button.button == SDL_BUTTON_RIGHT) {
						state.canon = -1;
						state.canon_bool = true;
					}
				break;
			}
		
		if (mau && !state.success && state.canon < 0) {
			if (mX > 0.7) mX = 0.7;
			if (mY > 0.7) mY = 0.7;
			if (validpos(state.p + Point(mX,-mY))) {
				state.p.x += mX;
				state.p.y -= mY;
			}
			else if (validpos(state.p + Point(mX,0))) {
				state.p.x += mX;
				while (validpos(state.p + Point(0,-0.01*sgn(mY)))) {
					state.p.y -= 0.01 * sgn(mY);
				}
			}
			else if (validpos(state.p + Point(0,-mY))) {
				state.p.y-=mY;
				while (validpos(state.p + Point(0.01*sgn(mX), 0))) {
					state.p.x += 0.01 * sgn(mX);
				}
			}
			else while (validpos(state.p + Point(0.01 * sgn(mX), -0.01 * sgn(mY))))
				state.p = state.p + Point(0.01 * sgn(mX), -0.01 * sgn(mY));
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawscene();
		glLoadIdentity();
		SDL_GL_SwapBuffers();
		state.t += 0.01;
		if (!state.success && del(state.p, map.target) < pw && state.energy >= map.portalmin) {
			state.p = map.target;
			state.success = true;
			state.T = state.t;
			state.t = 0;
		}
		for (int i=0; i<map.obstacles.size(); i++) {
			if (state.nexists(i)) continue;
			if (map.obstacles[i].t == 0 && del(state.p, map.obstacles[i].p) < map.obstacles[i].par && state.par(i) < 0.5) {
				state.energy -= 1;
				if (state.energy < 0)
					state.energy = 0;
			}
			if (map.obstacles[i].t == 1 && del(state.p, map.obstacles[i].p) < 2*pw) {
				if (map.obstacles[i].par2 == 0 || state.energy < map.obstacles[i].par2) {
					state.energy += map.obstacles[i].par;
					state.sumEnergy += map.obstacles[i].par;
				}
			}
			if (map.obstacles[i].t == 2 && state.par(i) < 0.5) {
				if (linecircle(map.obstacles[i].p, map.obstacles[i].q, state.p)) {
					state.energy = 0;
					for (std::map<int, Point>::iterator i=state.varparam.begin(); i!=state.varparam.end(); i++) {
						int t = map.obstacles[i->first].t;
						if (t == 0 || t == 2 || t == 5 || (t == 7 && i->second.y == 0))
							i->second = Point(0,0);
					}
				}
			}
			if (map.obstacles[i].t == 3 && del(state.p, map.obstacles[i].p) < pw && state.energy >= map.obstacles[i].par) {
				state.p = map.obstacles[i].q;
			}
			if (map.obstacles[i].t == 4 && del(state.p, map.obstacles[i].p) < pw && state.energy >= map.obstacles[i].par3) {
				state.spar((int)map.obstacles[i].par, map.obstacles[i].par2);
			}
			if (map.obstacles[i].t == 5 && del(state.p, map.obstacles[i].p) < map.obstacles[i].par) {
				Point diff = (state.p - map.obstacles[i].p).norm() * 0.3;
				if (validpos(state.p + diff))
					state.p = state.p + diff;
				else if (validpos(state.p + Point(diff.x, 0)))
					state.p.x = state.p.x + diff.x;
				else if (validpos(state.p + Point(0, diff.y)))
					state.p.y = state.p.y + diff.y;
			}
			if (map.obstacles[i].t == 6) {
				float T = state.t;
				float p = map.obstacles[i].p.x + map.obstacles[i].p.y;
				while (T >= p) T -= p;
				if (T < map.obstacles[i].p.x)
					state.spar((int)map.obstacles[i].par, map.obstacles[i].q.x);
				else
					state.spar((int)map.obstacles[i].par, map.obstacles[i].q.y);
			}
			if (map.obstacles[i].t == 8 && linecircle(map.obstacles[i].p, map.obstacles[i].q, state.p)) {
				state.spar((int)map.obstacles[i].par, map.obstacles[i].par2);
			}
			if (map.obstacles[i].t == 10) {
				if (del(state.p, map.obstacles[i].p) < pw) {
					if (!state.canon_bool && state.energy >= map.obstacles[(int)map.obstacles[i].par].par2) {
						state.p = map.obstacles[i].p;
						state.canon = (int)map.obstacles[i].par;
					}
				} else 
					state.canon_bool = false;
			}
			if (map.obstacles[i].t == 11 && del(state.p, senemypos(map.obstacles[i].p, map.obstacles[i].q, map.obstacles[i].par)) < (pw+1)) {
				state.energy = 0;
			}
			if (map.obstacles[i].t == 12 && del(state.p, state.ppar(i)) < map.obstacles[i].par && state.energy > 0) {
				Point pos = state.ppar(i) + (state.p - state.ppar(i)).norm()*0.1;
				if (validpos(pos, 1))
					state.spar(i, state.ppar(i) + (state.p - state.ppar(i)).norm()*0.1);
			}
			if (map.obstacles[i].t == 12 && del(state.p, state.ppar(i)) < 2*pw) {
				state.energy = 0;
			}
			if (map.obstacles[i].t == 13) {
				if (state.par(i) > 0) {
					state.spar((int)map.obstacles[i].par, map.obstacles[i].q.x);
					state.spar(i, state.par(i) - 0.01);
				} else {
					state.spar((int)map.obstacles[i].par, map.obstacles[i].q.y);
				}
			}
			if (map.obstacles[i].t == 14) {
				state.spar((int)map.obstacles[i].par, state.ppar(i));
				state.spar((int)map.obstacles[i].par2, state.ppar(i));
				state.spar((int)map.obstacles[i].p.x, state.ppar(i));
				state.spar((int)map.obstacles[i].p.y, state.ppar(i));
				state.spar((int)map.obstacles[i].q.x, state.ppar(i));
				state.spar((int)map.obstacles[i].q.y, state.ppar(i));
				state.spar((int)map.obstacles[i].p.y, state.ppar(i));
			}
		}
		if (state.success && state.t >= (pw+1)/2)
			nextmap();
		while ((SDL_GetTicks() - ticks) < 20)
			SDL_Delay(20 - (SDL_GetTicks() - ticks));
	}
}
