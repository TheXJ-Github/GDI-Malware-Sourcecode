#include <windows.h>
#include <cmath>
#include <math.h>
#define winapi WINAPI
#define lpvoid LPVOID
#define dword DWORD
#define ulonglong ULONGLONG
#define uint UINT
#define rdtsc __rdtsc
typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;

static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
DWORD WINAPI triph(LPVOID lpParam)
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
            int x = i % w, y = i / h;
            data[i].rgb -= x & y;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}

DWORD WINAPI shuffle(LPVOID lpParam)
{
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		HDC hdc = GetDC(NULL);
		int a = rand() % sw, b = rand() % sh;
		BitBlt(hdc, a, b, 200, 200, hdc, a + rand() % 21 - 10, b + rand() % 21 - 10, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI solaris(LPVOID lpParam)
{
	HDC hdc = GetDC(HWND_DESKTOP);
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);
	while (TRUE)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int X = GetSystemMetrics(SM_CXSCREEN);
		int Y = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % (X - 0), rand() % (Y - 0), rand() % (X - 0), rand() % (Y - 0), hdc, rand() % (X - 0), rand() % (Y - 0), PATINVERT);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI memz(LPVOID lpParam)
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

DWORD WINAPI sdss(LPVOID lpParam) {

    int uVar1;
    ulonglong uVar2;
    uint uVar3;
    uint uVar4;
    HDC hdc;
    HPEN h;
    int right;
    uint uVar5;
    int top;
    int bottom;
    int left;
    int local_28;
    int local_1c;
    HBRUSH local_14;
    int local_10;
    uint local_c;
    uint local_8;

    uVar3 = GetSystemMetrics(0);
    uVar4 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_c = (uVar5 << 5 ^ uVar5) % uVar4;
    local_14 = CreateSolidBrush(0xff);
    h = CreatePen(0, 2, 0xffffff);
    local_28 = 0;
    do {
        if (local_28 == 1) {
            local_14 = CreateSolidBrush(0xa5ff);
        }
        else if (local_28 == 2) {
            local_14 = CreateSolidBrush(0xffff);
        }
        else if (local_28 == 3) {
            local_14 = CreateSolidBrush(0xff00);
        }
        else if (local_28 == 4) {
            local_14 = CreateSolidBrush(0xffff00);
        }
        else if (local_28 == 5) {
            local_14 = CreateSolidBrush(0xff0000);
        }
        else if (local_28 == 6) {
            local_14 = CreateSolidBrush(0xd30094);
        }
        else if (local_28 == 7) {
            local_14 = CreateSolidBrush(0xff00ff);
        }
        else if (local_28 == 8) {
            local_14 = CreateSolidBrush(0xff);
            local_28 = 0;
        }
        SelectObject(hdc, local_14);
        SelectObject(hdc, h);
        if (((((int)uVar3 <= (int)local_8) || ((int)uVar4 <= (int)local_c)) || ((int)local_8 < 1)) ||
            ((int)local_c < 1)) {
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_c = (uVar5 << 5 ^ uVar5) % uVar4;
        }
        uVar2 = rdtsc();
        left = local_8 - 0x3c;
        top = local_c - 0x3c;
        uVar5 = (uint)uVar2 & 3;
        right = local_8 + 0x3c;
        bottom = local_c + 0x3c;
        local_1c = 10;
        local_10 = right;
        do {
            if ((uVar2 & 3) == 0) {
                Ellipse(hdc, left, top, right, bottom);
                local_8 = local_8 + 0x14;
                left = left + 0x14;
                local_10 = local_10 + 0x14;
                bottom = bottom + 0x14;
                local_c = local_c + 0x14;
                top = top + 0x14;
            LAB_004020f7:
                Sleep(0x82);
                right = local_10;
            }
            else {
                if (uVar5 == 1) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 + 0x14;
                    local_10 = local_10 + 0x14;
                    left = left + 0x14;
                LAB_004020ed:
                    local_c = local_c - 0x14;
                    bottom = bottom + -0x14;
                    top = top + -0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 2) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    left = left + -0x14;
                    local_10 = local_10 + -0x14;
                    bottom = bottom + 0x14;
                    local_c = local_c + 0x14;
                    top = top + 0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 3) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    local_10 = local_10 + -0x14;
                    left = left + -0x14;
                    goto LAB_004020ed;
                }
            }
            local_1c = local_1c + -1;
        } while (local_1c != 0);
        local_28 = local_28 + 1;
    } while (true);
}

DWORD WINAPI sierp(LPVOID lpParam) {
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
		int x = i % w, y = i / h, t = y ^ y | x;
		data[i].rgb = x & y & t;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
} 

DWORD WINAPI bar(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 10)
            byte = randy()%0xff;
        for (int i = 0; w * h > i; i++) {
            if ((i % h) && (randy() % 110))
                v = randy() % 24;
            *((BYTE*)data + 4 * i + v) =i;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
} 

DWORD WINAPI squr(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);
	while (TRUE)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int X = GetSystemMetrics(SM_CXSCREEN);
		int Y = GetSystemMetrics(SM_CYSCREEN);
    	HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
		BitBlt(hdc, rand() % (X - 0), rand() % (Y - 0), rand() % (X - 0), rand() % (Y - 0), hdc, rand() % (X - 0), rand() % (Y - 0), PATINVERT);
    	DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI spin(LPVOID lpParam) {
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
int main () {
	Sleep(5000);
	if (MessageBoxW(NULL, L"AUNG208, This is for you.", L"Aung208", MB_OKCANCEL | MB_ICONASTERISK) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"LAST WARNING! AUNG YOU BETTER RUN THIS IT'S TUBERCOMI99 EXPOSE!", L"Aung208 - final warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		Sleep(2000);
		{
			MessageBoxW(NULL, L"AUNG WOMP WOMP LIL BRO YOUR SCRATCH MALWARES ARE FAKE AINT NOBODY WANNA BE FRIENDS WITH YOU JUST QUIT SUCKER", L"SURPRISE", MB_OK | MB_ICONERROR);
			MessageBoxW(NULL, L"Subscribe to Tubercomiosis99", L"Aung208.exe", MB_OK | MB_ICONASTERISK);
		Sleep(4000);
			HANDLE thread1 = CreateThread(0, 0, triph, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
		InvalidateRect(0, 0, 0);	
		Sleep(1000);
			HANDLE thread2 = CreateThread(0, 0, shuffle, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
		InvalidateRect(0, 0, 0);
		Sleep(1000);	
			HANDLE thread3 = CreateThread(0, 0, memz, 0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, solaris, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread3, 0);
			TerminateThread(thread4, 0);
			CloseHandle(thread3);
		InvalidateRect(0, 0, 0);
			CloseHandle(thread4);
		InvalidateRect(0, 0, 0);		
		Sleep(1000);
			HANDLE thread5 = CreateThread(0, 0, sdss, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
		InvalidateRect(0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, sierp, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
		InvalidateRect(0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, bar, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
		InvalidateRect(0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, squr, 0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, spin, 0, 0, 0);
			Sleep(15000);
			TerminateThread(thread8, 0);
			TerminateThread(thread9, 0);
			CloseHandle(thread8);
		InvalidateRect(0, 0, 0);
			CloseHandle(thread9);
		InvalidateRect(0, 0, 0);
		}
	}
}
