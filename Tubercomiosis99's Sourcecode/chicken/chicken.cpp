#include <cmath>
#include <windows.h>
#include <math.h>

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;
DWORD WINAPI hue(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 60000)
            byte = rand()%0xff;
        for (int i = 0; w * h > i; i++) {
            if (i % h == 0 && rand() % 100 == 0)
                v = rand() % 2;
                    *((BYTE*)data + 4 * i + v) = *((BYTE*)(data + i + v));
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
} 

DWORD WINAPI invert(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(1)
	{
		hdc = GetDC(0);
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		Sleep(100);
	        ReleaseDC(0, hdc);
	}
}

DWORD WINAPI dupe(LPVOID lpParam)
{
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    RECT rekt;POINT wPt[3];
    while (1) {
        GetWindowRect(GetDesktopWindow(), &rekt);
        wPt[0].x = rand()%sw; wPt[0].y = rand() % sh;
        wPt[1].x = rand() % sw; wPt[1].y = rand() % sh;
        wPt[2].x = rand() % sw; wPt[2].y = rand() % sh;
        PlgBlt(desk, wPt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
    }
}
DWORD WINAPI transpire(LPVOID lpParam)
{
    int hSrc;
    int wSrc;
    HDC hdcDest;
    GetDC(0);
    wSrc = GetSystemMetrics(0);
    for (hSrc = GetSystemMetrics(1);
        ;
        StretchBlt(hdcDest, -10, -10, wSrc + 20, hSrc + 20, hdcDest, 0, 0, wSrc, hSrc, 0xCC0020u))
    {
        hdcDest = GetDC(0);
        (hdcDest, 4);
        StretchBlt(hdcDest, 10, 10, wSrc - 20, hSrc - 20, hdcDest, 0, 0, wSrc, hSrc, 0xCC0020u);
    }
}

DWORD WINAPI circles(LPVOID lpParam)
{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		HDC hdc = GetDC(0);
		int rand_num_x = rand() % w;
		int rand_num_y = rand() % h;

		int top_x = 0 + rand_num_x; // Top Left Corner
		int top_y = 0 + rand_num_y; // Top Right Corner

		int bottom_x = 100 + rand_num_x; // Bottom Left Corner
		int bottom_y = 100 + rand_num_y; // Bottom Right Corner

		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		Sleep(100);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI last(LPVOID lpParam)
{
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    _RGBQUAD* data = (_RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(_RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            data[i].rgb = (data[i].rgb * 2) % (RGB(255, 255, 255));
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}
int main() {
	if (MessageBoxW(NULL, L"Run chicken.exe? This malware was recreated after Aung the Faker made it on Scratch and called it a day. Epilepsy warning! Hit No if you have epilepsy or heart problems! Made by Tubercomiosis99.",L"chicken (skid)",MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		Sleep(3000);
		HANDLE thread1 = CreateThread(0, 0, hue, 0, 0, 0);
		HANDLE thread2 = CreateThread(0, 0, invert, 0, 0, 0);
		Sleep(15000);
		TerminateThread(thread1, 0);
		TerminateThread(thread2, 0);
		CloseHandle(thread1);
	InvalidateRect(0, 0, 0);	
	    CloseHandle(thread2);
	InvalidateRect(0, 0, 0);  
	Sleep(2000);  
	    HANDLE thread3 = CreateThread(0, 0, dupe, 0, 0, 0);
	    HANDLE thread4 = CreateThread(0, 0, transpire, 0, 0, 0);
	    Sleep(15000);
	    TerminateThread(thread3, 0);
	    TerminateThread(thread4, 0);
	    CloseHandle(thread3);
	InvalidateRect(0, 0, 0);
	    CloseHandle(thread4);
	InvalidateRect(0, 0, 0);    
	Sleep(2000);
	    HANDLE thread5 = CreateThread(0, 0, circles, 0, 0, 0);
	    Sleep(15000);
	    TerminateThread(thread5, 0);
	    CloseHandle(thread5);
	InvalidateRect(0, 0, 0);    
	Sleep(2000);
	    HANDLE thread6 = CreateThread(0, 0, last, 0, 0, 0);
	    Sleep(15000);
	    TerminateThread(thread6, 0);
	    CloseHandle(thread6);
	InvalidateRect(0, 0, 0);    
	}
}
