#include <windows.h>
#include <cmath>
#include <math.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
DWORD WINAPI epilepsy(LPVOID lpParam)
{
    HDC hdc = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;

    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(SM_CXSCREEN);
        sy = GetSystemMetrics(SM_CYSCREEN);
        rx = rand() % sx;
        ry = rand() % sy;
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225)));
        PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
        Sleep(10);
    }
}

DWORD WINAPI text(LPVOID lpParam)
{
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"glitch";
    while(1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(10);
    }
}

int main() {
	if (MessageBoxW(NULL, L"Run Skidded Safety? This malware was remade after Aung the Faker made it. Epilepsy warning!",L"glitch.exe - by Tubercomiosis99 (SKIDDED)",MB_YESNO | MB_ICONASTERISK) == IDNO)
	{
		ExitProcess(0);
	}
else
{
	HANDLE thread1 = CreateThread(0, 0, epilepsy, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread1, 0);
	CloseHandle(thread1);
InvalidateRect(0, 0, 0);
Sleep(1000);
	HANDLE thread2 = CreateThread(0, 0, epilepsy, 0, 0, 0);
	HANDLE thread3 = CreateThread(0, 0, text, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread2, 0);
	TerminateThread(thread3, 0);
	CloseHandle(thread2);
InvalidateRect(0, 0, 0);
	CloseHandle(thread3);
InvalidateRect(0, 0, 0);	
}}
