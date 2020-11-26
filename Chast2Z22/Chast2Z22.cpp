#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include"resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hinst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TCHAR szAppName[] = _T("MainFrame");
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	hinst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(hInstance, szAppName);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hWnd = CreateWindow(szAppName, _T("Часть 2 Задание 22"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HDC memBit1;
	static HDC memBit2;
	static HDC memBit3;
	static HDC memBit4;
	static HBITMAP hBitmap1;
	static HBITMAP hBitmap2;
	static HBITMAP hBitmap3;
	static HBITMAP hBitmap4;
	PAINTSTRUCT ps;
	HDC hdc;
	static int t = 0;
	static BITMAP bm;
	static int cx, cy;
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 10,150, NULL);
		hBitmap1 = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hBitmap1, sizeof(bm), &bm);
		hdc = GetDC(hwnd);
		memBit1 = CreateCompatibleDC(hdc);
		SelectObject(memBit1, hBitmap1);
		ReleaseDC(hwnd, hdc);
		hBitmap2 = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP2));
		GetObject(hBitmap2, sizeof(bm), &bm);
		hdc = GetDC(hwnd);
		memBit2 = CreateCompatibleDC(hdc);
		SelectObject(memBit2, hBitmap2);
		ReleaseDC(hwnd, hdc);
		hBitmap3 = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP3));
		GetObject(hBitmap3, sizeof(bm), &bm);
		hdc = GetDC(hwnd);
		memBit3 = CreateCompatibleDC(hdc);
		SelectObject(memBit3, hBitmap3);
		ReleaseDC(hwnd, hdc);
		hBitmap4 = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP4));
		GetObject(hBitmap4, sizeof(bm), &bm);
		hdc = GetDC(hwnd);
		memBit4 = CreateCompatibleDC(hdc);
		SelectObject(memBit4, hBitmap4);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_TIMER:
		t++;
		if (t == 7)
		{
			t = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		switch (t)
		{
		case 0:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit1, 0, 0, SRCCOPY);
			break;
		case 1:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit2, 0, 0, SRCCOPY);
			break;
		case 2:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit3, 0, 0, SRCCOPY);
			break;
		case 3:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit4, 0, 0, SRCCOPY);
			break;
		case 4:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit3, 0, 0, SRCCOPY);
			break;
		case 5:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit2, 0, 0, SRCCOPY);
			break;
		case 6:
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memBit1, 0, 0, SRCCOPY);
			break;
		default:
			break;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 10);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}