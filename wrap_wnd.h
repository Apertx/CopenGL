#ifndef __WRAP_WND_H__
#define __WRAP_WND_H__

#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void setFullscreen(unsigned char is_fullscreen);

#endif