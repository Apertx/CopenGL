#ifndef __MAIN_H__
#define __MAIN_H__

#define APP_TITLE "Game of Russia"
#define APP_WIDTH 640
#define APP_HEIGHT 480

void myInit(void);
void myResize(int w, int h);
void myDraw(void);
void myKeyDown(int key);
void myKeyUp(int key);

#endif