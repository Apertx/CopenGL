#include "opengl.h"
#include "draw.h"

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>


const int width = 800;
const int height = 600;

WINDOWPLACEMENT wpc;
BOOL FullScreen = FALSE;
float f = 0.4f;

void
changeSize (int w, int h)
{
    if (h == 0)
    {
        h = 1;
    }
    float ratio = (float)w / (float)h;
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glViewport (0, 0, w, h);
    gluPerspective (45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode (GL_MODELVIEW);
}

LRESULT CALLBACK
WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        return 0;
        case WM_CLOSE:
        PostQuitMessage (0);
        return 0;
        case WM_SIZE:
        {
            UINT width = LOWORD (lParam);
            UINT height = HIWORD (lParam);
            changeSize (width, height);
        }
        return 0;
        case WM_DESTROY:
        return 0;

        case WM_KEYDOWN:
        switch (wParam)
        {
            case VK_ESCAPE:
            PostQuitMessage (0);
            return 0;
            case VK_UP:
            f += 0.1f;
            return 0;
            case VK_DOWN:
            f -= 0.1f;
            return 0;
            case VK_SPACE:
            {
                if (!FullScreen)
                {
                    GetWindowPlacement (hWnd, &wpc);
                    SetWindowLong (hWnd, GWL_STYLE, WS_POPUP);
                    SetWindowLong (hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);
                    ShowWindow (hWnd, SW_SHOWMAXIMIZED);
                    FullScreen = TRUE;
                }
                else
                {
                    SetWindowLong (hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                    SetWindowLong (hWnd, GWL_EXSTYLE, 0L);
                    SetWindowPlacement (hWnd, &wpc);
                    ShowWindow (hWnd, SW_SHOWDEFAULT);
                    FullScreen = FALSE;
                }
            }
            return 0;
        }
        return 0;

        default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

void
Init (void)
{
    glClearColor (0, 0, 0, 1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
    changeSize (width, height);
    glTranslatef (0.0f, 0.0f,-6.0f);
    glRotatef (30.0f, 1.0f, 1.0f, 1.0f); 
}

int
WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      0, 0, width, height,
      NULL, NULL, hInstance, NULL);

    EnableOpenGL (hWnd, &hDC, &hRC);
    Init();

    while (!bQuit)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawAxes();
            drawCube();
            glRotatef(f, 1.0f, 1.0f, 1.0f);
            SwapBuffers (hDC);
        }
    }

    DisableOpenGL (hWnd, hDC, hRC);
    DestroyWindow (hWnd);

    return msg.wParam;
}
