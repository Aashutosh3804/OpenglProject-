#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
using namespace std;
#include <Gl/glut.h>
float _angle = 30.0f;
float _cameraAngle = 0.0f;
#include "./stb_image.h"
#include <bits/stdc++.h>
#include <boost/algorithm/clamp.hpp>
#include <GL/freeglut.h>
typedef GLfloat point[3];

point v[] = {{-0.5, 0.3, -0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.3, -0.5}, {-0.5, 0.3, 0.5}, {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, 0.3, 0.5}};
point hfrt[] = {{-0.5, 0.3, 0.5}, {0.5, 0.3, 0.5}, {0.5, 0.25, 0.65}, {-0.5, 0.25, 0.65}};
GLfloat theta[] = {10.0, 0.0, 0.0};
point grass[] = {{-2.0, -0.5, -2.0}, {-2.0, -0.5, 2.0}, {2.0, -0.5, 2.0}, {2.0, -0.5, -2.0}};
point road[] = {{-2.0, -0.492, 1.5}, {-2.0, -0.492, 0.9}, {2.0, -0.492, 0.9}, {2.0, -0.492, 1.5}};
point boundry[] = {{-2.0, -0.5, 0.9}, {-2.0, 0.1, 0.9}, {-2, 0.1, -2}, {-2, -0.5, -2}, {2, 0.1, -2}, {2, -0.5, -2}, {2.0, 0.1, 0.9}, {2.0, -0.5, 0.9}, {-1, -0.5, 0.9}, {-1, 0.1, 0.9}, {1, -0.5, 0.9}, {1, 0.1, 0.9}};
GLint axis = 1;
point rackFaces[] = {{-0.2, 0.2, -0.08}, {-0.2, 0.2, 0.08}, {-0.2, -0.2, 0.08}, {-0.2, -0.2, -0.08}, {0.2, 0.2, -0.08}, {0.2, 0.2, 0.08}, {0.2, -0.2, 0.08}, {0.2, -0.2, -0.08}};
point rack[] = {{-0.2, 0.15, -0.08}, {-0.2, 0.15, 0.08}, {0.2, 0.15, -0.08}, {0.2, 0.15, 0.08}};
point mall_boundry[] = {{-1.8, -0.49, 0.7}, {-1.8, 2, 0.7}, {-1.8, 2, -1.8}, {-1.8, -0.49, -1.8}, {1.8, 2, -1.8}, {1.8, -0.49, -1.8}, {1.8, 2, 0.7}, {1.8, -0.49, 0.7}, {-0.5, -0.49, 0.7}, {-0.5, 0.2, 0.7}, {0.5, 0.2, 0.7}, {0.5, -0.49, 0.7}};
point mall_door[] = {{-0.5, -0.49, 0.7}, {-0.5, 0.2, 0.7}, {-0.0028, 0.2, 0.7}, {-0.0028, -0.49, 0.7}, {0.0028, -0.49, 0.7}, {0.0028, 0.2, 0.7}, {0.5, 0.2, 0.7}, {0.5, -0.49, 0.7}};
point mall_door_inner[] = {{-0.49, -0.47, 0.709}, {-0.49, 0.18, 0.709}, {-0.003, 0.18, 0.709}, {-0.003, -0.47, 0.709}, {0.003, -0.47, 0.709}, {0.003, 0.18, 0.709}, {0.49, 0.18, 0.709}, {0.49, -0.47, 0.709}};
point transparent_glass[] = {{-1.8, 0.3, -0.5}, {-1.8, -0.49, -0.5}, {-0.6, -0.49, -0.5}, {-0.6, 0.3, -0.5}, {-0.6, 0.3, -1.69}, {-0.6, -0.49, -1.69}};
point sphere_particles[] = {{-0.8, 2.2, 1}, {-0.6, 0.15 + 2.0, 1}, {-0.7, 0.2 + 2.0, 1}, {-0.75, 0.18 + 2.0, 1}, {-0.69, 0.21 + 2.0, 1}, {-0.66, 0.15 + 2.0, 1}, {-0.8, 0.18 + 2.0, 1}, {-0.65, 0.18 + 2.0, 1}, {-0.69, 0.25 + 2.0, 1}};
point sphere_particles1[] = {{-0.75, 2.1, 1}, {-0.62, 0.11 + 2.0, 1}, {-0.8, 0.2 + 1.5, 1}, {-0.71, 0.2 + 2.0, 1}, {-0.69, 0.18 + 1.9, 1}, {-0.60, 0.17 + 1.9, 1}, {-0.64, 0.13 + 1.9, 1}, {-0.75, 0.20 + 1.9, 1}, {-0.8, 0.26 + 1.9, 1}};
bool sanitization[] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sanitize = 0;
int sanitize_idx = 0;

GLfloat view_translate[] = {0, 0, 0};
int val = 2;
GLfloat thumanx = -1.1;
GLfloat thumany = -0.2;
GLfloat thumanz = 1.55;
GLfloat mall_door_left_t = 0;
GLfloat moving_humanz = 0;
GLfloat moving_human_angle = 0;
GLfloat angleLeft_auto = 30;
GLfloat angleright_auto = -30;

GLfloat human1_color[] = {0.3, 0.64, 0.1};
GLfloat human2_color[] = {0.3, 0.64, 0.1};
GLfloat human3_color[] = {0.3, 0.64, 0.1};
GLfloat human4_color[] = {0.3, 0.64, 0.1};

GLint time_s = 0;
int lightning = 0;
int corona_particles = 9;
int soap_particles = 9;
static GLuint textureNames[9];

float angleleftleg = 30;
float anglerightleg = -30;
int leftvar = 1, leftvar_auto = 1;
int rightvar = 1, rightvar_auto = 1;
int orthoview = 0;
int houseline = 0;
GLfloat humanangle = 180;
GLdouble viewer[] = {0.0, 0.0, 9.0};
void openDoor();
void timers(int);
void drawPolygon(point a, point b, point c, point d, int texture = 0, bool is_texture = false)
{
    if (is_texture)
    {
        glDisable(GL_COLOR_MATERIAL);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, textureNames[texture]);
    }
    glBegin(GL_POLYGON);
    if (is_texture)
        glTexCoord2f(0.0, 1.0);
    glVertex3fv(a);
    if (is_texture)
        glTexCoord2f(0.0, 0.0);
    glVertex3fv(b);
    if (is_texture)
        glTexCoord2f(1.0, 0.0);
    glVertex3fv(c); //left
    if (is_texture)
        glTexCoord2f(1.0, 1.0);
    glVertex3fv(d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
}

void drawhouse(point a, point b, point c, point d, point e, point f, point g, point h)
{
    if (houseline)
    {

        glBegin(GL_LINE_LOOP);
        glVertex3fv(b);
        glVertex3fv(f);
        glVertex3fv(g);
        glVertex3fv(c);
        glEnd();
        glBegin(GL_LINES);
        glVertex3fv(e);
        glVertex3fv(f);
        glVertex3fv(h);
        glVertex3fv(g);
        glVertex3fv(d);
        glVertex3fv(c);
        glVertex3fv(a);
        glVertex3fv(b);
        glEnd();
        glColor3f(1, 0.5, 0.31);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-0.15, -0.1, 0.5);
        glVertex3f(-0.15, -0.5, 0.5);
        glVertex3f(0.15, -0.5, 0.5);
        glVertex3f(0.15, -0.1, 0.5);
        glEnd();
    }
    else
    {
        glColor3f(1, 0.98, 0.8);
        glNormal3f(0.0, +1.0, 0.0);

        drawPolygon(b, a, e, f, 3, true);
        glNormal3f(0.0, -1.0, 0.0);

        drawPolygon(d, h, g, c, 3, true);
        glNormal3f(0.0, 0.0, -1.0);

        drawPolygon(a, b, c, d, 3, true);
        glNormal3f(0.0, 0.0, +1.0);

        drawPolygon(e, h, g, f, 3, true);
        glColor3f(0.7, 0.2, 0.8);

        //        glColor3f(1, 0.5, 0.31);
        //        glBegin(GL_POLYGON);
        //        glVertex3f(-0.15, -0.1, 0.51);
        //        glVertex3f(-0.15, -0.5, 0.51);
        //        glVertex3f(0.15, -0.5, 0.51);
        //        glVertex3f(0.15, -0.1, 0.51);
        //        glEnd();
    }
}
void drawRack()
{
    GLfloat y = rack[0][1];
    for (int i = 1; i < 5; i++)
    {
        glBegin(GL_POLYGON);

        glVertex3f(rack[0][0], y, rack[0][2]);
        glVertex3f(rack[1][0], y, rack[1][2]);
        glVertex3f(rack[3][0], y, rack[3][2]);
        glVertex3f(rack[2][0], y, rack[2][2]);
        glEnd();
        y -= 0.05;
    }
}
void drawBoundry()
{
    glNormal3f(1, 0, 0);
    drawPolygon(boundry[0], boundry[1], boundry[2], boundry[3], 1, true);
    glNormal3f(0, 0, 1);

    drawPolygon(boundry[3], boundry[2], boundry[4], boundry[5], 1, true);
    glNormal3f(-1, 0, 0);

    drawPolygon(boundry[5], boundry[4], boundry[6], boundry[7], 1, true);
    glNormal3f(0, 0, -1);

    drawPolygon(boundry[0], boundry[1], boundry[9], boundry[8], 1, true);
    glNormal3f(0, 0, -1);

    drawPolygon(boundry[7], boundry[6], boundry[11], boundry[10], 1, true);
}
void drawMallBoundry(int innerMall = 1)
{

    glColor3f(1, 1, 1);
    glNormal3f(1, 0, 0);
    drawPolygon(mall_boundry[0], mall_boundry[1], mall_boundry[2], mall_boundry[3], 4, true);
    glNormal3f(0, 0, 1);
    drawPolygon(mall_boundry[3], mall_boundry[2], mall_boundry[4], mall_boundry[5], 4, true);
    glNormal3f(-1, 0, 0);
    drawPolygon(mall_boundry[5], mall_boundry[4], mall_boundry[6], mall_boundry[7], 4, true);
    if (innerMall)
    {
        glBegin(GL_LINE_LOOP);

        glVertex3fv(mall_boundry[8]);
        glVertex3fv(mall_boundry[9]);
        glVertex3fv(mall_boundry[10]);
        glVertex3fv(mall_boundry[11]);
        glVertex3fv(mall_boundry[7]);
        glVertex3fv(mall_boundry[6]);
        glVertex3fv(mall_boundry[1]);
        glVertex3fv(mall_boundry[0]);
        glEnd();
    }
    else
    {
    }
}
void table()
{
    glColor3f(0.80, 0.72, 0.62);
    glPushMatrix();
    glTranslated(0.375, -0.325, -0.375);
    glScaled(2.5, 0.5, 2.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.475, -0.425, -0.475);
    glScaled(0.5, 1.5, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.475, -0.425, -0.275);
    glScaled(0.5, 1.5, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.275, -0.425, -0.275);
    glScaled(0.5, 1.5, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.275, -0.425, -0.475);
    glScaled(0.5, 1.5, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}

void drawMallDoor()
{

    glColor3f(0.7, 0.62, 0.5);
    glPushMatrix();
    glTranslatef(mall_door_left_t, 0, 0);
    drawPolygon(mall_door[0], mall_door[1], mall_door[2], mall_door[3]);
    glNormal3f(0, 0, 1);

    drawPolygon(mall_door_inner[0], mall_door_inner[1], mall_door_inner[2], mall_door_inner[3], 0, true);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.7, 0.62, 0.5);

    glTranslatef(-mall_door_left_t, 0, 0);

    drawPolygon(mall_door[4], mall_door[5], mall_door[6], mall_door[7]);

    glNormal3f(0, 0, 1);
    drawPolygon(mall_door_inner[4], mall_door_inner[5], mall_door_inner[6], mall_door_inner[7], 0, true);
    glPopMatrix();
}
void rotateHuman(int choice)
{
    switch (choice)
    {
    case 1:
        humanangle = 90;
        break;
    case 2:
        humanangle = 180;
        break;
    case 3:
        humanangle = -90;
        break;
    case 4:
        humanangle = 0;
        break;
    case 5:
        lightning = 1;
        break;
    case 6:
        lightning = 0;
        break;
    case 7:
        glutIdleFunc(openDoor);
        break;
    case 8:
        sanitize = 1;
        glutTimerFunc(1, timers, 0);
        break;

    case 9:
        sanitize = 0;
        break;

    default:
        exit(0);
    }
    glutPostRedisplay();
}
void Human(int leftleg, int rightleg, GLfloat body[])
{
    glColor3f(0.96, 0.64, 0.38);

    glPushMatrix();
    //    glTranslated(-0.4 , -0.3125, -0.25 );		//head
    //    glScaled(-2, -0.75, -1);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glColor3fv(body);

    glPushMatrix();
    glTranslated(-0.0, -0.2, 0); //neck
    glRotated(90, 1, 0, 0);
    glScaled(2, 1.5, 2);

    glutSolidCube(0.06);

    glTranslated(-0.0, -0.0, 0.14); //chest
                                    //    glRotated(90,1,0,0);
    glScaled(4, 2.5, 3.5);

    glutSolidCube(0.06);
    glPopMatrix();
    glColor3f(0.9, 0.2, 0.38);

    glPushMatrix();
    //    glRotated(180,1,0,0);

    glTranslated(-0.28, -0.45, 0); //left arm
    glRotated(-30, 0, 0, 1);

    glScaled(1.2, 4.9, 1);

    glutSolidCube(0.06);
    glPopMatrix();
    glPushMatrix();
    //    glRotated(180,1,0,0);

    glTranslated(0.28, -0.45, 0); //rigth arm
    glRotated(30, 0, 0, 1);

    glScaled(1.2, 4.9, 1);

    glutSolidCube(0.06);
    glPopMatrix();
    glPushMatrix();
    //    glRotated(180,1,0,0);

    glTranslated(-0.15, -0.8, 0); //left leg;
    glRotated(leftleg, 1, 0, 0);

    glScaled(1.2, 4.9, 1);

    glutSolidCube(0.06);
    glPopMatrix();
    glPushMatrix();
    //    glRotated(180,1,0,0);

    glTranslated(0.15, -0.8, 0); //eight leg
    glRotated(rightleg, 1, 0, 0);

    glScaled(1.2, 4.9, 1);

    glutSolidCube(0.06);
    glPopMatrix();
}

void drawgrass()
{
    glColor3f(0.13, 0.55, 0.13);
    drawPolygon(grass[0], grass[1], grass[2], grass[3], 5, true);
}
void drawRoad()
{
    // glColor3f(0.3085, 0.2862, 0.3137);
    glNormal3f(0, 1, 0);
    drawPolygon(road[1], road[0], road[3], road[2], 6, true);
}
void DrawTransaparentGlass()
{
    glNormal3f(0, 0, 1);
    drawPolygon(transparent_glass[0], transparent_glass[1], transparent_glass[2], transparent_glass[3]);

    drawPolygon(transparent_glass[2], transparent_glass[3], transparent_glass[4], transparent_glass[5]);
}
void DrawAllTransaparent()
{
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(88 / 255., 179 / 255., 214 / 255., 0.5);
    glTranslatef(0, 1., 0);
    DrawTransaparentGlass();

    glDisable(GL_BLEND);
    glPopMatrix();
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(88 / 255., 179 / 255., 214 / 255., 0.5);
    glTranslatef(0, 1., 1.1);
    DrawTransaparentGlass();

    glDisable(GL_BLEND);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(88 / 255., 179 / 255., 214 / 255., 0.5);
    glRotatef(-90, 0, 10, 0);
    glTranslatef(0.1, 1., 0);
    DrawTransaparentGlass();

    glDisable(GL_BLEND);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1, 1, 0.8);
    glScalef(1, 1, 2);

    table();
    glPopMatrix();
}
void drawParticle(GLfloat mat_ambient[])
{

    GLfloat mat_specula[] = {1, 1, 1};
    GLfloat mat_shininess[] = {100};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specula);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glPushMatrix();
    glScalef(1, 1, 1);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.2, 0.1, 0);
    glScalef(0.4, 0.4, 0.4);
    glRotatef(-90, 1, 0, 0);

    glutSolidCone(0.1, 1.2, 20, 20);
    glTranslatef(0.0, 0, -0.2);
    glutSolidCylinder(0.018, 0.2, 20, 20);
    glPopMatrix();
}
void drawCircleFilled(double centerX, double centerY, double radiusX, double radiusY)
{

    glBindTexture(GL_TEXTURE_2D, textureNames[7]);
    const float DEG2RAD = 3.14159 / 180;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(centerX, centerY);
    for (int i = -1; i < 360; i++)
    {
        float degInRad = i * DEG2RAD;
        glVertex2d(centerX + cos(degInRad) * radiusX,
                   centerY + sin(degInRad) * radiusY);
    }

    glEnd();
}
void drawCloud(GLfloat x, GLfloat y)
{

    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x, y, 80, 45);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x + 25, y + 15, 35, 35);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x + 25, y - 15, 35, 35);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x - 25, y - 15, 35, 35);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x - 25, y + 15, 35, 35);
}
void RenderString(float x, float y, void *font, const unsigned char *string, float const &r, float const &g, float const &b)
{
    char *c;

    glColor3f(r, g, b);
    glRasterPos2f(x, y);

    glutBitmapString(font, string);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1, 1, 1, 1.0};
    //    GLfloat mat_shininess[] = { 100.0 };
    GLfloat lightintensity[] = {1, 1, 1, 1.0};
    GLfloat lightposition[] = {0, 0.9, 0, 1};
    GLfloat lightposition2[] = {0.1, 0.25, 0.2, 1.0};
    if (orthoview)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-4, 4, -4, 4, -4, 60);
        glMatrixMode(GL_MODELVIEW);
    }
    else
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1, 1, -1, 1, 1.0, 60.0);
        glMatrixMode(GL_MODELVIEW);
    }
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);

    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightintensity);
    glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
    glEnable(GL_LIGHT0);
    glFrontFace(GL_CW);
    // glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 3, 0);

    glRotatef(theta[0], 1.0f, 0.0f, 0.0f);
    glRotatef(theta[1], 0.0f, 1.0f, 0.0f);
    glRotatef(theta[2], 0.0f, 0.0f, 1.0f);
    glTranslatef(view_translate[0], view_translate[1], view_translate[2]);
    // glEnable(GL_COLOR_MATERIAL); //Enable COLOR
    // GLfloat mat_ambient[] = {0.19225, 0.19225, 0.19225, 1.0};
    // GLfloat mat_diffuse[] = {0.50754, 0.50754, 0.50754, 1.0};
    // GLfloat mat_specula[] = {0.508273, 0.508273, 0.508273};
    // GLfloat mat_shininess[] = {0.4};

    // glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specula);
    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(0, 0.9, 0);

    glutSolidCube(0.1);
    glPopMatrix();
    if (lightning == 1)
        glEnable(GL_LIGHTING);
    int zi = 1;
    int k = 1;
    for (int i = 1; i < 13; i++)
    {
        glPushMatrix();

        glTranslated(-1.3 + ((k - 1) * 0.6), -0.23, -1.2 + ((zi - 1) * 0.55));
        glRotated(90, 0, 1, 0);

        drawhouse(rackFaces[0], rackFaces[1], rackFaces[2], rackFaces[3], rackFaces[4], rackFaces[5], rackFaces[6], rackFaces[7]);
        drawRack();
        zi++;
        if (i % 3 == 0)
        {
            zi = 1;
            k++;
        }
        glPopMatrix();
    }

    // // glEnable(GL_COLOR_MATERIAL); //Enable COLOR

    drawgrass();
    drawRoad();
    drawBoundry();
    glPushMatrix();
    glTranslated(thumanx, thumany, thumanz);

    glRotated(humanangle, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    GLfloat gr[] = {0.3, 0.64, 0.1};
    Human(angleleftleg, anglerightleg, gr);
    glPopMatrix();

    drawMallBoundry();

    drawMallDoor();

    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(1, 1, 2);

    table();
    glPopMatrix();
    drawPolygon(mall_boundry[0], mall_boundry[3], mall_boundry[5], mall_boundry[7], 2, true);
    glPushMatrix();
    glTranslatef(0, 1, 0);

    drawPolygon(mall_boundry[0], mall_boundry[3], mall_boundry[5], mall_boundry[7], 2, true);

    glPopMatrix();
    zi = 1;
    k = 1;
    for (int i = 1; i < 7; i++)
    {
        glPushMatrix();

        glTranslated(-1.1 + ((k - 1) * 0.2), 0.7, -1.25 + ((zi - 1) * 0.5));
        glRotated(90, 0, 1, 0);

        drawhouse(rackFaces[0], rackFaces[1], rackFaces[2], rackFaces[3], rackFaces[4], rackFaces[5], rackFaces[6], rackFaces[7]);
        drawRack();
        zi++;
        if (i % 3 == 0)
        {
            zi = 1;
            k++;
        }
        glPopMatrix();
    }
    DrawAllTransaparent();
    glPushMatrix();
    glTranslated(-1.65, -0.2, moving_humanz);

    glRotated(moving_human_angle, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    Human(angleLeft_auto, angleright_auto, human1_color);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-0.5, -0.2, moving_humanz);

    glRotated(moving_human_angle, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    Human(angleLeft_auto, angleright_auto, human2_color);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.55, -0.2, -0.7);

    glRotated(90, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    Human(angleLeft_auto, angleright_auto, human3_color);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-0, 0.8, moving_humanz);

    glRotated(moving_human_angle, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    Human(angleLeft_auto, angleright_auto, human4_color);
    glPopMatrix();
    GLfloat green[] = {0, 1, 0};
    GLfloat blue[] = {0, 0, 1};

    if (sanitize)
    {
        glEnable(GL_LIGHTING);
        glPushMatrix();
        if (sanitization[0])
        {

            glTranslatef(-0.8, -0.2, 0.9);
            drawCircleFilled(1.5, 0.2, 0.06, 0.04);
        }
        // glPopMatrix();
        if (sanitization[1])
        {
            glTranslatef(-0.1, 0.2, 0);
            drawCircleFilled(1.5, 0.2, 0.06, 0.04);
        }
        if (sanitization[2])
        {
            glTranslatef(-0.1, 0.2, 0);
            drawCircleFilled(1.5, 0.2, 0.08, 0.06);
        }
        if (sanitization[3])
        {
            glTranslatef(-0.1, 0.25, 0);
            drawCircleFilled(1.5, 0.2, 0.1, 0.08);
        }
        if (sanitization[4])
        {
            glTranslatef(-0.1, 0.28, 0);
            drawCircleFilled(1.5, 0.2, 0.12, 0.09);
        }
        if (sanitization[5])
        {
            glTranslatef(-0.1, 0.3, 0);
            drawCircleFilled(1.5, 0.2, 0.14, 0.11);
        }
        if (sanitization[6])
        {
            glTranslatef(-0.1, 0.22, 0);
            drawCircleFilled(1.5, 0.22, 0.19, 0.1);
        }
        glPopMatrix();
        if (sanitization[7])
        {
            glPushMatrix();
            glTranslatef(0, 2, 0.9);

            glScalef(0.009, 0.009, 0.009);
            glDisable(GL_COLOR_MATERIAL);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glEnable(GL_TEXTURE_2D);
            drawCloud(0.4, 1);
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_COLOR_MATERIAL);
            glPopMatrix();

            glDisable(GL_COLOR_MATERIAL);

            for (int i = 0; i < soap_particles; i++)
            {
                glPushMatrix();
                glTranslatef(sphere_particles[i][0], sphere_particles[i][1], sphere_particles[i][2]);
                glScalef(0.2, 0.2, 0.2);
                drawParticle(green);
                glPopMatrix();
            }
            for (int i = 0; i < corona_particles; i++)
            {
                glPushMatrix();
                glTranslatef(sphere_particles1[i][0], sphere_particles1[i][1], sphere_particles1[i][2]);
                glScalef(0.2, 0.2, 0.2);

                drawParticle(blue);

                glPopMatrix();
            }
            glEnable(GL_COLOR_MATERIAL); //Enable COLOR
            if (lightning == 0)
                glDisable(GL_LIGHTING);
        }
    }
    glColor3f(165 / 255., 42 / 255., 42 / 255.);
    glPushMatrix();
    glTranslatef(0.7, -0.49, 0.78);
    glutSolidCube(0.1);
    glTranslatef(0., 0.2, 00);

    glScalef(1, 15, 1);
    glutSolidCube(0.02);
    glScalef(1, 0.02, 1);
    glTranslatef(0.0, 0.5, 0.0);

    glutSolidCube(0.1);
    // glScalef(1, 5, 1);
    glTranslatef(0.0, 0.4, 0.0);
    glColor3f(100 / 255., 149 / 255., 237 / 255.);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(0.018, 0.3, 20, 20);
    glPopMatrix();
    const unsigned char *t = reinterpret_cast<const unsigned char *>("Aashutosh Kumar Jha");

    RenderString(-6.0f, 5.5f, GLUT_BITMAP_TIMES_ROMAN_24, t, 0.0f, 0.807f, 0.8196f);
    t = reinterpret_cast<const unsigned char *>("Akhil Singhal");

    RenderString(-6.0f, 5.0f, GLUT_BITMAP_TIMES_ROMAN_24, t, 0.0f, 0.807f, 0.8196f);

    t = reinterpret_cast<const unsigned char *>("BANGALORE INSTITUTE OF TECHNOLOGY");

    RenderString(-4.5f, 6.5f, GLUT_BITMAP_TIMES_ROMAN_24, t, 0.0f, 0.807f, 0.8196f);

    t = reinterpret_cast<const unsigned char *>("3D SHOPPING CENTER");

    RenderString(-2.0f, 4.0f, GLUT_BITMAP_TIMES_ROMAN_24, t, 0.0f, 0.807f, 0.0f);
    GLfloat bit[4][3] = {{3.8f, 1.5f + 3.6f, 1.5f}, {3.8f, 2.5f + 3.6f, 1.5f}, {5.8f, 2.5f + 3.6f, 1.5f}, {5.8f, 1.5f + 3.6f, 1.5f}};
    drawPolygon(bit[0], bit[1], bit[2], bit[3], 8, true);

    glutSwapBuffers();
}
void timerf(int x)
{
    if (moving_human_angle == 0)
    {
        moving_humanz -= 0.01;
        if (moving_humanz < -1.8)
        {
            moving_human_angle = 180;
        }
    }
    else
    {
        moving_humanz += 0.01;
        if (moving_humanz > 0.5)
        {
            moving_human_angle = 0;
        }
    }
    if (angleLeft_auto == 30)
    {
        leftvar_auto = -2;
    }
    if (angleLeft_auto == -30)
    {
        leftvar_auto = 2;
    }
    if (angleright_auto == -30)
    {
        rightvar_auto = 2;
    }
    if (angleright_auto == 30)
    {
        rightvar_auto = -2;
    }
    angleLeft_auto += leftvar_auto;
    angleright_auto += rightvar_auto;

    glutPostRedisplay();
    glutTimerFunc((1000 / 20), timerf, 0);
}

void timers(int x)
{

    if (sanitize)
    {
        if (sanitize_idx < 8)
        {
            sanitization[sanitize_idx] = 1;
            sanitize_idx++;
            glutTimerFunc((300), timers, 0);
            viewer[1] = 2;
            viewer[2] = 5;
        }
        if (sanitize_idx >= 7)
        {
            for (int i = 0; i < 9; i++)
            {

                sphere_particles[i][0] = boost::algorithm::clamp(sphere_particles[i][0] + ((double)rand() / RAND_MAX) * (0.1 - (-0.1)) - 0.1, -0.5, 0.5);
                sphere_particles[i][1] = boost::algorithm::clamp(sphere_particles[i][1] + ((double)rand() / RAND_MAX) * (0.1 - (-0.1)) - 0.1, 1.8, 2.2);
                ;
                sphere_particles1[i][0] = boost::algorithm::clamp(sphere_particles1[i][0] + ((double)rand() / RAND_MAX) * (0.1 - (-0.1)) - 0.1, -0.5, 0.5);
                sphere_particles1[i][1] = boost::algorithm::clamp(sphere_particles1[i][1] + ((double)rand() / RAND_MAX) * (0.1 - (-0.1)) - 0.1, 1.8, 2.2);
                ;
            }
            glutTimerFunc((100), timers, 0);
            time_s++;
            if (time_s % 50 == 0)
            {
                if (corona_particles > 0)
                    corona_particles -= 2;
                if (soap_particles > 4)
                    soap_particles--;
            }
        }
    }
    else
    {

        return;
    }
    glutPostRedisplay();
}
void initfirst()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(0, 1000, 0, 1000, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
void handleresize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
        if (orthoview)
            glOrtho(-1.0, 1.0, -1.0 * ((GLfloat)h / (GLfloat)w), 1.0 * ((GLfloat)h / (GLfloat)w), -20.0, 20.0);
        else
            glFrustum(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, 1.0, 10.0);
    }
    else
    {
        if (orthoview)
            glOrtho(-1.0 * ((GLfloat)w / (GLfloat)h), 1.0 * ((GLfloat)w / (GLfloat)h), -1.0, 1.0, -20.0, 20.0);
        else
            glFrustum(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, 1.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void openDoor()
{
    if (mall_door_left_t > -0.3)
    {
        mall_door_left_t -= 0.0005;
        glutPostRedisplay();
    }

    else
    {
        glutIdleFunc(NULL);
    }
}

void keys(unsigned char key, int x, int y)
{
    if (key == 'x')
        viewer[0] -= 0.25;
    if (key == 'X')
        viewer[0] += 0.25;
    if (key == 'y')
        viewer[1] -= 0.25;
    if (key == 'Y')
        viewer[1] += 0.25;
    if (key == 'z')
        viewer[2] -= 0.25;
    if (key == 'Z')
        viewer[2] += 0.25;
    if (key == 'q')
        axis = 0;
    if (key == 'w')
        axis = 1;
    if (key == 'e')
        axis = 2;
    if (key == 'o')
        val = -2;
    if (key == 's')
        val = 2;
    if (key == 'q' || key == 'w' || key == 'e')
    {

        if (val > 0)
        {
            theta[axis] += val;
            if (theta[axis] > 360.0)
                theta[axis] -= 360.0;
        }
        else
        {
            theta[axis] += val;
            if (theta[axis] < -360.0)
                theta[axis] += 360.0;
        }
    }
    if (key == 'p')
    {
        if (angleleftleg == 30)
        {
            leftvar = -2;
        }
        if (angleleftleg == -30)
        {
            leftvar = 2;
        }
        if (anglerightleg == -30)
        {
            rightvar = 2;
        }
        if (anglerightleg == 30)
        {
            rightvar = -2;
        }
        angleleftleg += leftvar;
        anglerightleg += rightvar;
        if (humanangle == 90)
        {
            thumanx += 0.009;
        }
        else if (humanangle == 180)
        {
            thumanz -= 0.009;
        }
        else if (humanangle == 0)
        {
            thumanz += 0.009;
        }
        else if (humanangle == -90)
        {
            thumanx -= 0.009;
        }

        if (thumanx < -1.5 && thumanz < -0.15 && !sanitization[0])
        {
            human1_color[0] = 254 / 255.;
            human1_color[1] = 202 / 255.;
            human1_color[2] = 38 / 255.;
        }
        if (thumanx < -0.4 && thumanz < -0.15 && !sanitization[0])
        {
            human2_color[0] = 254 / 255.;
            human2_color[1] = 202 / 255.;
            human2_color[2] = 38 / 255.;
        }
        if (thumanx > 1.1 && thumanz < -0.6 && !sanitization[0])
        {
            human3_color[0] = 254 / 255.;
            human3_color[1] = 202 / 255.;
            human3_color[2] = 38 / 255.;
        }
    }

    glutPostRedisplay();
}
void initTexture()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    // Read the images
    int width, height, nrChannels;
    unsigned char *image_data;
    char *x[] = {
        "./glass.jpg",
        "./brick1.jpg",
        "./marble.jpg",
        "./rack.jpg",
        "./boundrymall.jpg",
        "./grass.jpg",
        "./road.jpg", "./fight.jpg", "./bit.png"};

    glGenTextures(9, textureNames);

    for (int i = 0; i < 9; i++)
    {
        // Select the texture object
        image_data = stbi_load(x[i], &width, &height, &nrChannels, 0);

        glBindTexture(GL_TEXTURE_2D, textureNames[i]);

        // Set the parameters
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Create the texture object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
    }

    // Enable textures
}

void catchKey(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
        humanangle = -90;
    else if (key == GLUT_KEY_RIGHT)
        humanangle = 90;
    else if (key == GLUT_KEY_DOWN)
        humanangle = 0;
    else if (key == GLUT_KEY_UP)
        humanangle = 180;
    ;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    int rotatehuman;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("3D Shopping Conter");
    initfirst();
    initTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(handleresize);
    //    glutTimerFunc(1000,timerf,0);
    rotatehuman = glutCreateMenu(rotateHuman);
    glutAddMenuEntry("lighton", 5);
    glutAddMenuEntry("lightoff", 6);
    glutAddMenuEntry("openDoor", 7);
    glutAddMenuEntry("Sanitize", 8);
    glutAddMenuEntry("Sanitize_done", 9);

    glutTimerFunc((1000 / 10), timerf, 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keys);
    glutSpecialFunc(catchKey);

    glutMainLoop();

    return 0;
}
