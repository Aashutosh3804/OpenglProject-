#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1416
int size, submenu;
GLint nCtrlPts = 4, nBezCurvePts = 20;
static float theta = 0;
int flag1 = 1;
GLfloat ya = 10;

struct wcPt
{
    GLfloat x;
    GLfloat y;
};
struct wcPt ctrlPts[4] = {{20, 100}, {30, 110}, {50, 90}, {60, 100}};
typedef struct wcPt cp;

void drawtext(float x, float y, char *s)
{
    int i;
    glRasterPos2f(x, y);
    for (i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void animate()
{
    ctrlPts[1].y = 100 + ya;
    ctrlPts[2].y = 100 - ya;
    theta += 5;
    if (ya < 10 && flag1 == 1)
        ya += 0.2;
    if (ya > -10 && flag1 == 0)
        ya -= 0.2;
    if (ya >= 10 && flag1 == 1)
        flag1 = 0;
    if (ya <= -10 && flag1 == 0)
        flag1 = 1;
    glutPostRedisplay();
}

void bino(GLint n, GLint *C)
{
    GLint k, j;
    for (k = 0; k <= n; k++)
    {
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void computeBezPt(GLfloat u, cp *bezPt, GLint nCtrlPts, cp *CtrlPts, GLint *C)
{
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;
    bezPt->x = bezPt->y = 0.0;
    for (k = 0; k < nCtrlPts; k++)
    {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += CtrlPts[k].x * bezBlendFcn;
        bezPt->y += CtrlPts[k].y * bezBlendFcn;
    }
}

void bezier(cp *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
    cp bezCurvePt;
    GLfloat u;
    GLint C[nCtrlPts], k;
    bino(nCtrlPts - 1, C);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k <= nBezCurvePts; k++)
    {
        u = (GLfloat)(k) / (GLfloat)(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        glVertex2f(bezCurvePt.x, bezCurvePt.y);
    }
    glEnd();
}

void displayFcn()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glPushMatrix();
    glLineWidth(5);
    glColor3f(255 / 255, 153 / 255.0, 51 / 255.0); //Indian flag: Orange color code
    for (i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    }

    glColor3f(1, 1, 1); //Indian flag: white color code
    for (i = 0; i < 8; i++)
    {
        glTranslatef(0, -1.0, 0);
        bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    }
    glColor3f(0.0, 1.0, 0.0); //Indian flag: green color code
    for (i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    }
    glPopMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glLineWidth(10);
    glBegin(GL_LINES); //to define pole of the flag
    glVertex2f(20, 100);
    glVertex2f(20, 40);
    glEnd();
    // drawtext(85.0, 20.0, "");
    // drawtext(85.0, 10.0, "1BI18CS069");
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void menufunc(int n)
{
    int i;
    switch (n)
    {
    case 1:
        ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
        ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
        ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[3].x -= 4 * sin((theta)*PI / 180.0);
        ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
        theta += 0.1;
        break;
    case 2:
        ctrlPts[1].x -= 10 * sin(theta * PI / 180.0);
        ctrlPts[1].y -= 5 * sin(theta * PI / 180.0);
        ctrlPts[2].x += 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[2].y += 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[3].x += 4 * sin((theta)*PI / 180.0);
        ctrlPts[3].y -= sin((theta - 30) * PI / 180.0);
        theta -= 0.1;
        break;
    case 3:
        glutIdleFunc(animate);
        break;
    case 4:
        exit(0);
    }
}

void winReshapeFun(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 130.0, 0.0, 130.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bezier Curve");
    submenu = glutCreateMenu(menufunc);
    glutReshapeFunc(winReshapeFun);
    glutCreateMenu(menufunc);
    glutAddMenuEntry("Dwn-mov", 1);
    glutAddMenuEntry("Up-mov", 2);
    glutAddMenuEntry("wave", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(displayFcn);
    glutMainLoop();
}
