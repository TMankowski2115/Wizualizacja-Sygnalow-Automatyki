// P3_Ostatecznie_finalny.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "P3_Ostatecznie_finalny.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>
#include <math.h>
#include <iostream>

#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//przyciski

HWND hwndPrzycisk;

//dane
std::string nazwa;
POINT startowy;
RECT DrawArea1 = { 50, 50, 500, 400 };
std::vector<std::vector<float>> dane;
std::vector<Point> data1;
std::vector<Point> data2;
std::vector<Point> data3;
std::vector<Point> data4;
int liczba_linii = 0;
int skala_A = 0.8;
int skala_T = 1;
int r = 0, g = 0, b = 0;
int pomijane = 0;



void RysujWykres(HDC hdc, HWND hWnd, PAINTSTRUCT& ps, std::vector<Point> data, int r, int g, int b, int skala_A, int pomijane) {

	hdc = BeginPaint(hWnd, &ps);

	//pole pion: 50-500, poziom 50-400
	HDC hdcOkno = GetDC(hWnd);
	HPEN Pioro, Pudelko, PioroTlo;




	

	Pioro = CreatePen(PS_SOLID, 2, RGB(r, g, b));
	Pudelko = (HPEN)SelectObject(hdcOkno, Pioro);
	MoveToEx(hdcOkno, 50, 225, &startowy);


	for (int z = 0; z < data.size() - pomijane; z++) {

		float zmienna;
		zmienna = data[z + pomijane].Y;
		data[z].Y = zmienna;

	}


	for (int i = 1; i < 450; i++)
	{

		//for (int j = i; j < liczba_linii; j++) {

		float xp = (((data[i - 1].X) * skala_T) - ((skala_T - 1) * 50));
		float xk = (((data[i].X) * skala_T) - ((skala_T - 1) * 50));
		float yp = 225 + ((data[i - 1].Y) * skala_A);
		float yk = 225 + (data[i].Y * skala_A);


		if (yk < 400 && yk > 50 && yp < 400 && yp>50 && xp > 50 && xk < 500) {

			MoveToEx(hdcOkno, xp, yp, &startowy);
			LineTo(hdcOkno, xk, yk);
		}



		//}




	}




	SelectObject(hdcOkno, Pioro);
	DeleteObject(Pioro);
	EndPaint(hWnd, &ps);






}


void WyrysujOkno(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<Point> data, int skala) {

	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
	{	//InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
		//SkalujDane(data, skala);
		hdc = BeginPaint(hWnd, &ps);
		HDC hdcOkno = GetDC(hWnd);
		HPEN Pioro, Pudelko, PioroTlo;




		PioroTlo = CreatePen(PS_SOLID, 1, 1);
		Pudelko = (HPEN)SelectObject(hdcOkno, PioroTlo);
		MoveToEx(hdcOkno, 50, 225, &startowy);
		LineTo(hdcOkno, 500, 225);
		SelectObject(hdcOkno, PioroTlo);
		DeleteObject(PioroTlo);
		RysujWykres(hdc, hWnd, ps, data, r, g, b, skala, pomijane);
		EndPaint(hWnd, &ps);
	}
}


void ZaladujdoPunktow() {
	srand(time(NULL));

	dane.clear();
	data1.clear();
	data2.clear();
	data3.clear();
	data4.clear();

	std::ifstream plik;

	//  cout << "Podaj nazwe pliku do wczytania:" << endl;
	//  cin >> nazwa;
	plik.open(nazwa, std::ios::in);

	if (plik)
	{
		std::string linie;

		while (!plik.eof())
		{
			while (std::getline(plik, linie))
			{
				liczba_linii++;
			}
		}
	}
	//else cout << "Nie uzyskano dostepu do pliku!" << endl;
	for (int a = 0; a < liczba_linii; a++)
	{
		dane.push_back(std::vector<float>());
	}
	plik.close();

	std::ifstream plik2;
	plik2.open(nazwa, std::ios::in);
	int m = 0;
	float xd;

	while (m < liczba_linii)
	{

		float tablica[12];
		for (int i = 0; i < 12; i++)
		{

			plik2 >> tablica[i];
			xd = tablica[i];
			dane[m].push_back(xd);
		}
		m = m + 1;
	}

	plik2.close();

	float v0 = 0;
	//data1.push_back(Point(50, 225));polozenie
	for (int z = 1; z < liczba_linii; z++) {

		float a = dane[z][5];
		float x = 50 + (z);
		float y = 10000 * ((a * 0.04 * 0.04) / 2);
		float omg;
		if (dane[z - 1][5] < dane[z][5]) {
			omg = -1000 * ((a * 0.04 * 0.04) / 2);
		}
		else
		{
			omg = 1000 * ((a * 0.04 * 0.04) / 2);
		}
		data1.push_back(Point(x, (v0 + omg)));
		
		v0 = v0 + omg;

		//data.push_back(Point(50 + (4 * i), (std::rand() % 300) +51));
	}

	//data2.push_back(Point(50, 225));przyspieszenie
	for (int z = 1; z < liczba_linii; z++) {


		float x = 50 + (z);
		float y = -10 * dane[z][5];
		data2.push_back(Point(x, (y)));


		//data.push_back(Point(50 + (4 * i), (std::rand() % 300) +51));
	}
	//data3.push_back(Point(50, 225));predkosc
	v0 = 0;
	for (int z = 1; z < liczba_linii; z++) {


		float x = 50 + (z);
		float a = dane[z][5];
		float y = -10 * (a * 0.04);
		data3.push_back(Point(x, v0 + y));
		v0 = v0 + y;

		//data.push_back(Point(50 + (4 * i), (std::rand() % 300) +51));
	}
	//data4.push_back(Point(50, 225));
	for (int z = 1; z < liczba_linii; z++) {


		
		float x = 50 + (z);
		float y = log(2*3.14/(0.04 * z));// log(arg1 / arg2);
		data4.push_back(Point(x, -5*y));


		//data.push_back(Point(50 + (4 * i), (std::rand() % 300) +51));
	}

}



int OnCreate(HWND window)
{
	//ZaladujzPliku(dane);
	ZaladujdoPunktow();
	return 0;
}






int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: W tym miejscu umieść kod.

	// Inicjuj ciągi globalne
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_P3OSTATECZNIEFINALNY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Wykonaj inicjowanie aplikacji:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_P3OSTATECZNIEFINALNY));

	MSG msg;

	// Główna pętla komunikatów:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P3OSTATECZNIEFINALNY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_P3OSTATECZNIEFINALNY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Rysuj Położenie"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 100,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need


	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Rysuj Przyspieszenie"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 170,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Rysuj Prędkość"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 240,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Rysuj W.T. Drgań"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 310,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Wyczyść Rysunek"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 380,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Wyczyść Ustawienia"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 450,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONCLEAR,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Powiększ Y"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 100,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONPLUS,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Pomniejsz Y"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		910, 100,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONMINUS,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Powiększ X"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 170,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONPRAWO,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Pomniejsz X"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		910, 170,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONLEWO,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Usuń 20"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 240,                                  // the left and top co-ordinates
		90, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONUSUNIECIE1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Usuń 50"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		900, 240,                                  // the left and top co-ordinates
		90, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONUSUNIECIE2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Usuń 100"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1000, 240,                                  // the left and top co-ordinates
		90, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONUSUNIECIE2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("outputSpring01"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 30,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONS1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("outputSpring02"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 30,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONS2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndPrzycisk = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("outputSpring03"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1000, 30,                                  // the left and top co-ordinates
		180, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONS3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	OnCreate(hWnd);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId, wmEvent;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			r = 254;
			hdc = BeginPaint(hWnd, &ps);
			WyrysujOkno(hWnd, hdc, ps, &DrawArea1, data1, skala_A);
			EndPaint(hWnd, &ps);
			r = 0;
			break;
		case ID_BUTTON2:
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			g = 254;
			ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			// RysujWykres(hdc, hWnd, ps);
			WyrysujOkno(hWnd, hdc, ps, &DrawArea1, data2, skala_A);
			EndPaint(hWnd, &ps);
			g = 0;
			break;
		case ID_BUTTON3:
			b = 254;
			ZaladujdoPunktow();
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			WyrysujOkno(hWnd, hdc, ps, &DrawArea1, data3, skala_A);
			EndPaint(hWnd, &ps);
			b = 0;
			break;
		case ID_BUTTON4:
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			b = 254;
			g = 254;
			ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			WyrysujOkno(hWnd, hdc, ps, &DrawArea1, data4, skala_A);
			EndPaint(hWnd, &ps);
			b = 0;
			g = 0;
			break;
		case ID_BUTTON5:
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			pomijane = 0;
			ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONCLEAR:
			//::MessageBox(hWnd, _T("elo"), _T("masło"), MB_OK);
			pomijane = 0;
			skala_A = 0.8;
			skala_T = 1;
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONPLUS:
			skala_A = skala_A + 1;
			//ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONMINUS:
			skala_A = skala_A - 1;
			//ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONPRAWO:
			skala_T = skala_T + 1;
			//ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONLEWO:
			skala_T = skala_T - 1;
			//ZaladujdoPunktow();
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONUSUNIECIE1:
			pomijane = 20;

			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONUSUNIECIE2:
			pomijane = 50;
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONUSUNIECIE3:
			pomijane = 100;
			hdc = BeginPaint(hWnd, &ps);
			//RysujWykres(hdc, hWnd, ps);
			//WyrysujOkno(hWnd, hdc, ps, NULL, data4, skala_A);
			EndPaint(hWnd, &ps);
			break;
		case ID_BUTTONS1:
			nazwa = "outputSpring01.log";
			ZaladujdoPunktow();

			//OnCreate(window);
			break;
		case ID_BUTTONS2:

			nazwa = "outputSpring02.log";
			ZaladujdoPunktow();
			//OnCreate(window);
			break;
		case ID_BUTTONS3:
			nazwa = "outputSpring03.log";
			ZaladujdoPunktow();
			//OnCreate(window);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		HDC hdcOkno = GetDC(hWnd);
		HPEN PioroTlo, Pudelko;

		PioroTlo = CreatePen(PS_SOLID, 1, 1);
		Pudelko = (HPEN)SelectObject(hdcOkno, PioroTlo);


		Rectangle(hdc, 50, 50, 500, 400);


		SelectObject(hdcOkno, PioroTlo);
		DeleteObject(PioroTlo);
		PioroTlo = CreatePen(PS_SOLID, 1, 1);
		Pudelko = (HPEN)SelectObject(hdcOkno, PioroTlo);
		MoveToEx(hdcOkno, 50, 225, &startowy);
		LineTo(hdcOkno, 500, 225);
		SelectObject(hdcOkno, PioroTlo);
		DeleteObject(PioroTlo);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
