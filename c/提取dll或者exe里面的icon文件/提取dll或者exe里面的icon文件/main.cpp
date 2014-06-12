#include <windows.h>

char szAppName[] = "HELLO_WIN"; 
char szTitle[]   = "HELLO_WIN"; 
HINSTANCE g_hInst = NULL;         

void CenterWindow(HWND hWnd);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
                         WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;
    WNDCLASS wc;
    HWND hwnd;

    g_hInst = hInstance;

    ZeroMemory(&wc, sizeof(WNDCLASS));
    wc.hInstance     = hInstance;
    wc.lpszClassName = szAppName;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.style         = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) 
        return 0;

    hwnd = CreateWindow(
        szAppName,
        szTitle,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        900, 600,
        0, 0,
        g_hInst,
        0);

    if (hwnd == NULL) 
        return 0;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
                         WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CenterWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_LBUTTONUP:
        // MessageBox(hwnd, "hello world!", szTitle, MB_OK);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hwnd);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc;
            RECT rc;
            hdc = BeginPaint(hwnd, &ps);

            GetClientRect(hwnd, &rc);
            SetTextColor(hdc, RGB(240, 240, 96));
            SetBkMode(hdc, TRANSPARENT);
            /*DrawText(hdc, "hello world!", -1, &rc, 
                DT_CENTER | DT_SINGLELINE | DT_VCENTER);*/
            
            for (int i = 0; ; i++)
            {
                int size = 40;
                int row = 20;
                char file[] = "D:\\Program Files (x86)\\常用工具\\美化系统\\imageres.dll.blue";
                HICON icon = ExtractIcon(g_hInst, file, i);
                if (icon == NULL)
                    break;
                DrawIcon(hdc, i % row * size, i / row * size, icon);
                DestroyIcon(icon);
            }

            EndPaint(hwnd, &ps);
            break;
        }

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void CenterWindow(HWND hwnd)
{
    RECT rw_self; 
    RECT rc_parent;
    RECT rw_parent; 
    HWND hwnd_parent;

    hwnd_parent = GetParent(hwnd);
    if (hwnd_parent == NULL) 
        hwnd_parent = GetDesktopWindow();

    GetWindowRect(hwnd_parent, &rw_parent);
    GetClientRect(hwnd_parent, &rc_parent);
    GetWindowRect(hwnd, &rw_self);

    SetWindowPos(hwnd, NULL,
        rw_parent.left + (rc_parent.right + rw_self.left - rw_self.right) / 2,
        rw_parent.top  + (rc_parent.bottom + rw_self.top - rw_self.bottom) / 2,
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

