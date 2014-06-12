#include <windows.h>
#include <stdio.h>
#include <math.h>

//#define for if(0);else for only for vc6
#define ULONG_PTR unsigned long *
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

#define SELECT_COLOR 1
#define SELECT_ALPHA 2

using namespace Gdiplus;

typedef BOOL (WINAPI *FUNC)(HWND, COLORREF, BYTE, DWORD);

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void SetClientSize(HWND hwnd);
void DrawClock(Graphics *pGraphics);

const UINT ID_TIMER = 1;
const UINT ESCAPR_TIME = 30;
const TCHAR ClassName[] = TEXT("Clock");
const TCHAR WindowName[] = TEXT("Application");
int ClientWidth = 150;
int ClientHeight = 150;
const double PI = 3.1415926;
ULONG_PTR g_GdiToken = NULL;
HRGN g_hGgn = NULL;
FUNC SetLayeredWindowAttributes;
HMODULE hModule;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ClassName;
    wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, 
			TEXT("windows class register fail!"), 
			TEXT("error"), 
			MB_OK | MB_ICONERROR);
		return -1;
	} 
    
    HWND hwnd;
	hwnd = CreateWindowEx(WS_EX_TOPMOST, ClassName, WindowName, 
		WS_POPUP, 
        0, 0, 0, 0,
        NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, 
			TEXT("windows create fail!"), 
			TEXT("error"), 
			MB_OK | MB_ICONERROR);
		return -1;
	}

    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);

	MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
		TranslateMessage(&msg);
		DispatchMessage(&msg);       
    }
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
	{
	case WM_CREATE:
		{
			GdiplusStartupInput m_gdiplusStartupInput;
			GdiplusStartup(&g_GdiToken,&m_gdiplusStartupInput,NULL);			
			SetClientSize(hwnd);

            g_hGgn = CreateEllipticRgn(0, 0, ClientWidth + 1, ClientHeight + 1);
            SetWindowRgn(hwnd, g_hGgn, TRUE);

            hModule = LoadLibrary("user32.dll");
            SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | 0x80000);
            SetLayeredWindowAttributes = (FUNC)GetProcAddress(hModule, "SetLayeredWindowAttributes");
            
            SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 75, SELECT_ALPHA);

			SetTimer(hwnd, ID_TIMER, ESCAPR_TIME, NULL);
		}
		return 0;
    
    //左键按住可拖动窗口
    case WM_NCHITTEST:
        return HTCAPTION;
    //ESC关闭程序
    case WM_KEYUP:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hwnd);
        return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			Graphics g(hdc);
			DrawClock(&g);
			EndPaint(hwnd, &ps);
		}
		return 0;
	
	case WM_TIMER:
		{
			HDC hdc = GetDC(hwnd);
			Graphics g(hdc);
			DrawClock(&g);
			ReleaseDC(hwnd, hdc);
		}
		return 0;

	case WM_DESTROY:
		{
			GdiplusShutdown(g_GdiToken);
            DeleteObject(g_hGgn);
            FreeLibrary(hModule);
			PostQuitMessage(0);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}    
}

void SetClientSize(HWND hwnd)
{
	RECT rect = {0, 0, ClientWidth, ClientHeight};
	AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), NULL);
	int WindowWidth = rect.right - rect.left;
	int WindowHeight = rect.bottom - rect.top;
	int WindowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - WindowWidth / 2;
	int WindowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - WindowHeight / 2;
	MoveWindow(hwnd, WindowPosX, WindowPosY, WindowWidth, WindowHeight, TRUE);
}

void DrawClock(Graphics *pGraphics)
{
	Bitmap bmMem(ClientWidth, ClientHeight);
	Graphics gpMem(&bmMem);
	Pen pen(Color(0, 0, 0));
	SolidBrush brush(Color(255, 255, 255));
	Font font(L"Comic Sans MS", 10);
	SolidBrush fontbrush(Color(0, 0, 0));
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);
	PointF ptOrg(float(ClientWidth) / 2, float(ClientHeight) / 2);
	float R = min(ptOrg.X, ptOrg.Y);
	float rfont = 15; 

	gpMem.SetSmoothingMode(SmoothingModeAntiAlias);
	gpMem.FillRectangle(&brush, 0, 0, ClientWidth, ClientHeight);
	//gpMem.DrawEllipse(&pen, 1, 1, ClientWidth - 3, ClientHeight - 3);
	
	for (int i = 1; i <= 12; i++)
	{
		wchar_t str[30];
		swprintf_s(str, 10, L"%d", i);
		double t = i * PI / 6;
		PointF pt = ptOrg + PointF(0.85f * float(R * sin(t)), -0.85f * float(R * cos(t)));
		RectF rt(pt.X - rfont, pt.Y - rfont, 2 * rfont, 2 * rfont);
		gpMem.DrawString(str, wcslen(str), &font, rt, &format, &fontbrush);
	}
	
	SYSTEMTIME st;
	GetLocalTime(&st);

	double t = st.wSecond * PI / 30;
	float r = R * 0.75f;
	PointF pt = ptOrg + PointF(r * float(sin(t)), -r * float(cos(t)));
	gpMem.DrawLine(&pen, ptOrg, pt);

	t = (st.wMinute + st.wSecond / 60.0) * PI / 30;
	r = R * 0.63f;
	pt = ptOrg + PointF(r * float(sin(t)), -r * float(cos(t)));
	gpMem.DrawLine(&pen, ptOrg, pt);

	t = (st.wHour + st.wMinute / 60.0) * PI / 6;
	r = R * 0.5f;
	pt = ptOrg + PointF(r * float(sin(t)), -r * float(cos(t)));
	gpMem.DrawLine(&pen, ptOrg, pt);

	pGraphics->DrawImage(&bmMem, 0, 0, ClientWidth, ClientHeight);
}


