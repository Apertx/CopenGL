#include "wrap_wnd.h"
#include "main.h"


WINDOWPLACEMENT wpc;
BOOL is_fullscreen;

void enableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC(hWnd);
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
  WNDCLASS wc;
  HWND hWnd;
  HDC hDC;
  HGLRC hRC;        
  MSG msg;
  BOOL bQuit;

  bQuit = FALSE;

  wc.style = CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "GL_YOUTB";
  RegisterClass(&wc);

  hWnd = CreateWindow (
    "GL_YOUTB", APP_TITLE, 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    0, 0, APP_WIDTH, APP_HEIGHT,
    NULL, NULL, hInstance, NULL);

  enableOpenGL(hWnd, &hDC, &hRC);
  myInit();

  while (!bQuit) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        bQuit = TRUE;
      } else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    } else {
      myDraw();
      SwapBuffers(hDC);
      Sleep(1);
    }
  }

  wglMakeCurrent(0, 0);
  wglDeleteContext(hRC);
  ReleaseDC(hWnd, hDC);

  DestroyWindow(hWnd);
  return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_CREATE:
    return 0;
  case WM_CLOSE:
    PostQuitMessage(0);
    return 0;
  case WM_SIZE:
    myResize(LOWORD(lParam), HIWORD(lParam));
    return 0;
  case WM_DESTROY:
    return 0;
  case WM_KEYDOWN:
    myKeyDown(wParam);
    return 0;
  case WM_KEYUP:
    if (wParam == VK_F11) {
      if (!is_fullscreen) {
        GetWindowPlacement(hWnd, &wpc);
        SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
        SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);
        ShowWindow(hWnd, SW_SHOWMAXIMIZED);
        is_fullscreen = TRUE;
      } else {
        SetWindowLong(hWnd, GWL_STYLE,WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        SetWindowLong(hWnd, GWL_EXSTYLE, 0L);
        SetWindowPlacement(hWnd, &wpc);
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        is_fullscreen = FALSE;
      }
    } else
      myKeyUp(wParam);
    return 0;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
}
