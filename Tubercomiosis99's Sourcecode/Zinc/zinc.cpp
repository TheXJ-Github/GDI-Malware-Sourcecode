#include <windows.h>
#include <cmath>
#define winapi WINAPI
#define lpvoid LPVOID
#define dword DWORD
#define ulonglong ULONGLONG
#define uint UINT
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
DWORD WINAPI curdraw(LPVOID lpParam) {

	POINT cursor;
	while (1) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		GetCursorPos(&cursor);
		DrawIcon(hdc, cursor.x - icon_x, cursor.y - icon_y, LoadIcon(NULL, IDI_APPLICATION));
		ReleaseDC(0, hdc);
		//Sleep(10);
	}
	return(1);
}
DWORD WINAPI pload1(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh/10, ySize = 9;
    while (1) {
    	HDC desk = GetDC(0);
        for (int i = 0; i < sh*2; i++) {
            int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
            BitBlt(desk, i, 0, 1, sh, desk, i, wave, SRCCOPY);
        }
        for (int i = 0; i < sw*2; i++) {
            int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
            BitBlt(desk, 0, i, sw, 1, desk, wave, i, SRCCOPY);
        }
    }
}
DWORD WINAPI stretcherblt(LPVOID lpParam){
	HDC desk;
	int sw, sh;
	
	while(1){
		desk = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(desk, 0, -20, sw, sh+40, desk, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, desk);
		Sleep(100);
	}
}
DWORD WINAPI idkwhichpayload(LPVOID lpParam)
{
    HWND v3; 
    HBITMAP h; 
    HDC hdcSrc; 
    HDC hdc; 
    void* lpvBits;
    int nHeight; 
    int nWidth; 
    DWORD v12; 
    int j; 
    int v14; 
    int i; 
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}
DWORD WINAPI pload4bit(LPVOID lpParam) 
{
    HDC hdc = GetDC(0);
	RECT wRect;
    POINT wPt[3];
	while (1)
	{
	GetWindowRect(GetDesktopWindow(), &wRect);
    wPt[0].x = wRect.left + 50 + 60;
    wPt[0].y = wRect.top + 70 + 30;
    wPt[1].x = wRect.right + 10 + 0;
    wPt[1].y = wRect.top + 50 + 65;
    wPt[2].x = wRect.left + 10 + 26;
    wPt[2].y = wRect.bottom + 80 + 99;
    PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
   }
}
DWORD WINAPI gdi4sub(LPVOID lpParam){
	while(1){
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand()%5, rand()%5, rand()%sw, rand()%sh, hdc, rand()%5, rand()%5, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI move(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI txtout(LPVOID lpvd)
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
        text = "zinc";
        text1 = "get off the computer timmy";
        text2 = "tubercomi";
        text3 = "this malware is skidded a lot";
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
DWORD WINAPI aaa9(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x + y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
int main(){

	if (MessageBoxW(NULL, L"Run safe gdi", L"Zinc skidded", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
{ if (MessageBoxW(NULL, L"Are you sure", L"Zinc skidded!", MB_YESNO | MB_ICONERROR) == IDNO)
{
	ExitProcess(0);
}
else	{
		HANDLE thread1 = CreateThread(0, 0, pload1, 0, 0, 0);
		Sleep(10000);
		TerminateThread(thread1, 0);
	CloseHandle(thread1);
	InvalidateRect(0, 0, 0);	
		HANDLE thread2 = CreateThread(0, 0, stretcherblt, 0, 0, 0);
		HANDLE thread3 = CreateThread(0, 0, idkwhichpayload, 0, 0, 0);
		Sleep(10000);
		TerminateThread(thread2, 0);
		TerminateThread(thread3, 0);
		CloseHandle(thread2);
    InvalidateRect(0, 0, 0);
        CloseHandle(thread3);
    InvalidateRect(0, 0, 0);    
        HANDLE thread4 = CreateThread(0, 0, idkwhichpayload, 0, 0, 0);
        Sleep(10000);
        TerminateThread(thread4, 0);
	    CloseHandle(thread4);
	InvalidateRect(0, 0, 0);
	    HANDLE thread5 = CreateThread(0, 0, pload4bit, 0, 0, 0);
	    HANDLE thread6 = CreateThread(0, 0, gdi4sub, 0, 0, 0);
	    Sleep(10000);
	    TerminateThread(thread5, 0);
	    TerminateThread(thread6, 0);
	    CloseHandle(thread5);
	InvalidateRect(0, 0, 0);
	    CloseHandle(thread6);
	InvalidateRect(0, 0, 0);
	    HANDLE thread7 = CreateThread(0, 0, move, 0, 0, 0);
	    Sleep(10000);
	    TerminateThread(thread7, 0);
	    CloseHandle(thread7);
	InvalidateRect(0, 0, 0);
	    HANDLE thread8 = CreateThread(0, 0, move, 0, 0, 0);
	    HANDLE thread9 = CreateThread(0, 0, txtout, 0, 0, 0);
	    Sleep(10000);
	    TerminateThread(thread8, 0);
	    TerminateThread(thread9, 0);
	    CloseHandle(thread8);
    InvalidateRect(0, 0, 0);
	    CloseHandle(thread9);
	InvalidateRect(0, 0, 0);
	    HANDLE thread10 = CreateThread(0, 0, aaa9, 0, 0, 0);
	    Sleep(10000);
	    TerminateThread(thread10, 0);
	    CloseHandle(thread10);
	InvalidateRect(0, 0, 0);
	    HANDLE thread11 = CreateThread(0, 0, curdraw, 0, 0, 0);
	    HANDLE thread12 = CreateThread(0, 0, gdi4sub, 0, 0, 0);
	    Sleep(10000);
	    TerminateThread(thread11, 0);
	    TerminateThread(thread12, 0);
	    CloseHandle(thread11);
	InvalidateRect(0, 0, 0);
        CloseHandle(thread12);
    InvalidateRect(0, 0, 0);
	}
}
}
