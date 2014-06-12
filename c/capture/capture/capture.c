#include <windows.h>
#include "resource.h"

POINT start_pt = {0};
POINT old_pt = {0};
BOOL is_start = FALSE;
int g_screen_width = 0;
int g_screen_height = 0;

void copy_rect_to_clipboard(HWND hwnd, RECT *rt)
{
    int width = rt->right - rt->left;
    int height = rt->bottom - rt->top;
    HDC hdc = GetDC(hwnd);
    HDC mem_dc = CreateCompatibleDC(hdc);
    HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
    
    SelectObject(mem_dc, bitmap);
    BitBlt(mem_dc, 0, 0, width, height, hdc, rt->left, rt->top, SRCCOPY);
    
    OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, bitmap);
    
    DeleteObject(bitmap);
    DeleteDC(mem_dc);
    ReleaseDC(hwnd, hdc);
}

HBRUSH get_desktop_brush(void)
{
    HBRUSH brush;
    HBITMAP bitmap;
    HDC mem_dc, desptop_dc;
    desptop_dc = GetDC(NULL);
    mem_dc = CreateCompatibleDC(desptop_dc);
    bitmap = CreateCompatibleBitmap(desptop_dc, g_screen_width, g_screen_height);
    SelectObject(mem_dc, bitmap);
    BitBlt(mem_dc, 0, 0, g_screen_width, g_screen_height, desptop_dc, 0, 0, SRCCOPY);
    brush = CreatePatternBrush(bitmap); //通过位图创建画刷
    DeleteObject(bitmap);
    DeleteDC(mem_dc);
    ReleaseDC(NULL, desptop_dc);

    return brush;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{    
    switch (message) 
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                DestroyWindow(hwnd);
            break;

        case WM_RBUTTONUP:
            DestroyWindow(hwnd);
            break;
        
        case WM_LBUTTONUP:
        {                
            POINT end_pt = {LOWORD(lParam), HIWORD(lParam)};
            RECT rt = {
				min(start_pt.x, end_pt.x) + 1, 
				min(start_pt.y, end_pt.y) + 1, 
				max(start_pt.x, end_pt.x) - 1, 
				max(start_pt.y, end_pt.y) - 1};

            if (!is_start)
                break;

            copy_rect_to_clipboard(hwnd, &rt);
            MessageBox(hwnd, "截图已保存到剪切板", "提示", MB_OK | MB_ICONINFORMATION);
            DestroyWindow(hwnd);
            break;
        }

        case WM_MOUSEMOVE:
        {            
            POINT end_pt = {LOWORD(lParam), HIWORD(lParam)};
            HDC hdc;
        
            if (!is_start)
                break;

            hdc = GetDC(hwnd);
            SetROP2(hdc, R2_NOT);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            Rectangle(hdc, start_pt.x, start_pt.y, old_pt.x, old_pt.y);
            Rectangle(hdc, start_pt.x, start_pt.y, end_pt.x, end_pt.y);            
            ReleaseDC(hwnd, hdc);

            old_pt = end_pt;
            break;
        }

        case WM_LBUTTONDOWN:
        {
            start_pt.x = LOWORD(lParam);
            start_pt.y = HIWORD(lParam);
            old_pt = start_pt;
            is_start = TRUE;
            break; 
        }       
            
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

int APIENTRY WinMain(
        HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASS wc;
    HWND hwnd;    
    HBRUSH brush;
    char class_name[] = "Capture";

    g_screen_width = GetSystemMetrics(SM_CXSCREEN);
    g_screen_height = GetSystemMetrics(SM_CYSCREEN);
    brush = get_desktop_brush();

    ZeroMemory(&wc, sizeof wc);
    wc.hInstance     = hInstance;
    wc.lpszClassName = class_name;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.hbrBackground = brush;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PEN));
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);

    if (RegisterClass(&wc) == FALSE)
        return 0;

    hwnd = CreateWindowEx(
        WS_EX_TOOLWINDOW, 
        class_name,
        class_name,
        WS_POPUP | WS_VISIBLE,
        0, 0,
        g_screen_width, g_screen_height,
        0, 0,
        hInstance, 0);

    if (hwnd == NULL)
        return 0;

    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(brush);

    return (int)msg.wParam;
}

