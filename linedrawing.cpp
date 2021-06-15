#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "./stb_image.h"
/**
 * \file
 * An application that displays a rotating cube with a
 * texture mapped image.
 *
 * On Linux, compile with:
 *   g++ -o image -Wall image.c -lglut -lGL -lGLU
 *
 * @author  Prof. David Bernstein, James Madison University
 */

// Faces of the cube
GLint faces[][4] = {{4, 5, 6, 7},
                    {1, 2, 6, 5},
                    {0, 1, 5, 4},
                    {0, 3, 2, 1},
                    {0, 4, 7, 3},
                    {2, 3, 7, 6}};
unsigned char *data;

// Vertices
GLfloat vertices[][3] = {{-1.5, -1.0, -1.0},
                         {1.0, -1.0, -1.0},
                         {1.0, 1.0, -1.0},
                         {-1.0, 1.0, -1.0},
                         {-1.5, -1.0, 1.0},
                         {1.5, -1.0, 1.0},
                         {1.5, 1.0, 1.0},
                         {-1.5, 1.0, 1.0}};

static GLfloat angle[] = {0.0, 0.0, 0.0};
static GLint axis = 2;
static GLint delay = 20;

//[name
static GLuint textureName;

//]name

/**
 * Update the content
 */
void update()
{
    // Update the rotation angle (for the current axis
    // of rotation)
    angle[axis] += 2.0;

    if (angle[axis] > 360.0)
        angle[axis] -= 360.0;

    // Make the modelview matrix current
    glMatrixMode(GL_MODELVIEW);

    // Clear the modelview matrix
    glLoadIdentity();

    // Concatenate the three rotations
    glRotatef(angle[0], 1.0, 0.0, 0.0);
    glRotatef(angle[1], 0.0, 1.0, 0.0);
    glRotatef(angle[2], 0.0, 0.0, 1.0);
}

/**
 * The mouse callback (i.e., the function that is called
 * each time a mouse button is pressed or released).
 *
 * @param button The button (e.g., GLUT_LEFT_BUTTON)
 * @param state  The state (e.g., GLUT_UP or GLUT_DOWN)
 * @param x      The x-position of the mouse
 * @param y      The y-position of the mouse
 */
void mouseClicked(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            axis = 0;
        else if (button == GLUT_MIDDLE_BUTTON)
            axis = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            axis = 2;
    }
}

//[render
/**
 * The display callback
 */
void display()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Select the texture object
    glBindTexture(GL_TEXTURE_2D, textureName);

    // Draw the cube

    glBegin(GL_POLYGON);
    int v;

    v = faces[0][0];
    glTexCoord2f(0.0, 0.0); // Map to the bottom left texel
    glVertex3fv(vertices[v]);

    v = faces[0][1];
    glTexCoord2f(0.0, 1.0); // Map to the bottom right texel
    glVertex3fv(vertices[v]);

    v = faces[0][2];
    glTexCoord2f(1.0, 1.0); // Map to the top right texel
    glVertex3fv(vertices[v]);

    v = faces[0][3];
    glTexCoord2f(1.0, 0.0); // Map to the top left texel
    glVertex3fv(vertices[v]);

    glEnd();

    // Force the rendering (off-screen)
    glFlush();

    // Handle the double buffering
    glutSwapBuffers();
}
//]render

/**
 * The reshape callback (i.e., the function that is called
 * each time the window is re-sized).
 *
 * @param width   The new width
 * @param height  The new height
 */
void reshape(int width, int height)
{
    GLfloat aspect;

    // Set the viewport
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Make the projection matrix current
    glMatrixMode(GL_PROJECTION);

    // Clear the projection matrix
    glLoadIdentity();

    // Set the projection matrix (based on the aspect ratio)
    if (width <= height)
    {
        aspect = (GLfloat)height / (GLfloat)width;
        glOrtho(-2.0, 2.0, -2.0 * aspect, 2.0 * aspect, -10.0, 10.0);
    }
    else
    {
        aspect = (GLfloat)width / (GLfloat)height;
        glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, -10.0, 10.0);
    }
}

/**
 * The timer callback.
 */
void timer(int value)
{
    // Update the content
    update();

    // Request a callback to the DisplayFunc
    glutPostRedisplay();

    // Re-start the timer
    glutTimerFunc(delay, timer, 0);
}

//[image
/**
 * Fill the given matrix with a RAW image
 *
 * @param data          The matrix to fill
 */

//]image

/**
 * OpenGL Initialization.
 */
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    //[image

    // Read the "image"
    int width, height, nrChannels;

    data = stbi_load("C:\\Users\\ANKUR\\Desktop\\CGV project\\glass.jpg", &width, &height, &nrChannels, 0);

    //]image

    //[name
    // Get a name for the texture
    glGenTextures(1, &textureName);
    //]name

    //[bind
    // Bind the texture object to its name
    glBindTexture(GL_TEXTURE_2D, textureName);
    //]bind

    //[parameters
    // Specify the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //]parameters

    //[mode
    // Specify the application mode
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //]mode

    //[create
    // Create the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //]create

    //[enable
    // Enable textures
    glEnable(GL_TEXTURE_2D);
    //]enable
}

/**
 * The entry point of the application.
 *
 * @param argc  The number of command line arguments
 * @param argv  The array of command line arguments
 * @return      A status code
 */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // GLUT Initialization
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Images");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(delay, timer, 0);
    glutMouseFunc(mouseClicked);

    // OpenGL Initialization
    init();

    // Start the event loop
    glutMainLoop();
}