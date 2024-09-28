#include <windows.h>
#include <cmath>
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

DWORD WINAPI texts(LPVOID lpParam)
{
    int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
    LPCSTR text = 0;
    LPCSTR text1 = 0;
    LPCSTR text2 = 0;
    LPCSTR text3 = 0;
    while(1)
    {
        HDC hdc = GetDC(0);
        SetBkMode(hdc, 0);
        text = "Entity 481";
        text1 = "chicken summoner";
        text2 = "Tubercomiosis99";
        text3 = "Enjoy your new PC";
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Baby Kruffy");
        SelectObject(hdc, font);
        TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
        Sleep(10);
        TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
        Sleep(10);
        TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
        Sleep(10);
        TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI epilepsy(LPVOID lpParam)
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
int main() {
	if (MessageBoxW(NULL, L"This safety malware is called Entity 481, it will not harm your PC. But i am not responsible for physical damage, like seizures and stuff. The best strat is prolly to hit no. But if you dont have epilepsy then you can run it ig?", L"Entity 481", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure you want to run this? I AINT RESPONSIBLE!!", L"Entity 481 FINAL WARNING", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			HANDLE thread1 = CreateThread(0, 0, texts, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
		InvalidateRect(0, 0, 0);
		Sleep(1000);
			HANDLE thread2 = CreateThread(0, 0, epilepsy, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
		InvalidateRect(0, 0, 0);
		Sleep(1000);
		    HANDLE thread3 = CreateThread(0, 0, dupe, 0, 0, 0);
		    HANDLE thread4 = CreateThread(0, 0, texts, 0, 0, 0);
		    Sleep(15000);
		    TerminateThread(thread3, 0);
		    TerminateThread(thread4, 0);
		    CloseHandle(thread3);
		InvalidateRect(0, 0, 0);
		    CloseHandle(thread4);
		InvalidateRect(0, 0, 0);
			}
	}
}
