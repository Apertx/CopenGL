#include "main.h"
#include "texture.h"
#include "wrap_wnd.h"
#include <windows.h>
#include "GL.h"
#include "GLU.h"

#define X0 0.0f
#define X1 1.0f / 3.0f
#define X2 2.0f / 3.0f
#define X3 1.0f
#define Y0 0.0f
#define Y1 0.5f
#define Y2 1.0f

float f = 0.4f;

GLfloat cube_vertices[72] = {
    -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
    -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
    -1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,
    -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1,
    -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
    1, -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1
};

GLfloat cube_texcoords[48] = {
    X0, Y0, X1, Y0, X1, Y1, X0, Y1,
    X1, Y0, X2, Y0, X2, Y1, X1, Y1,
    X2, Y0, X3, Y0, X3, Y1, X2, Y1,
    X0, Y1, X1, Y1, X1, Y2, X0, Y2,
    X1, Y1, X2, Y1, X2, Y2, X1, Y2,
    X2, Y1, X3, Y1, X3, Y2, X2, Y2
};

GLubyte cube_elements[36] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
};



void myInit(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);

    loadTexture("resources/tex01.bmp");
    loadTexture("resources/tex02.bmp");
    loadTexture("resources/tex03.bmp");
    loadTexture("resources/tex04.bmp");

    glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 1);
    myResize(APP_WIDTH, APP_HEIGHT);
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
}

void myResize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glScalef(0.3f, ratio * 0.3f, 0.3f);
    glMatrixMode(GL_MODELVIEW);
}

void myDraw(void) {
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube_elements);
    glDisable(GL_TEXTURE_2D);
    glRotatef(f, 1.0, 1.0, 1.0);
}

void myKeyDown(int key) {
    switch (key) {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case VK_UP:
        f += 0.1;
        break;
    case VK_DOWN:
        f -= 0.1;
        break;
    case '1':
        glBindTexture(GL_TEXTURE_2D, 1);
        break;
    case '2':
        glBindTexture(GL_TEXTURE_2D, 2);
        break;
    case '3':
        glBindTexture(GL_TEXTURE_2D, 3);
        break;
    case '4':
        glBindTexture(GL_TEXTURE_2D, 4);
        break;
    }
}

void myKeyUp(int key) {
    switch (key) {
    }
}
