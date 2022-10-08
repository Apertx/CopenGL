#ifndef _OPENGL_H_
#define _OPENGL_H_

#include <windows.h>


void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

#endif
