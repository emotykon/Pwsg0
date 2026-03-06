#include "app_2048.h" 
#include <stdexcept>
std::wstring const app_2048::s_class_name{ L"2048 Window" };//nazwa klasy
bool app_2048::register_class() {
	WNDCLASSEXW desc{};//definiuje wlasciwosci okna
	if (GetClassInfoExW(m_instance, s_class_name.c_str(),
		&desc) != 0) return true;//sprawdza czy juz nie ma takiej klasy
	desc = { .cbSize = sizeof(WNDCLASSEXW),
	.lpfnWndProc = window_proc_static,//odbiera komunikaty
	.hInstance = m_instance,
	.hCursor = LoadCursorW(nullptr, L"IDC_ARROW"),
	.hbrBackground = CreateSolidBrush(RGB(250, 047, 238)),//kolor okna
	.lpszClassName = s_class_name.c_str() };
	return RegisterClassExW(&desc) != 0;//oficjalnie zapisuje
}
HWND app_2048::create_window()
{
	// 1. Tworzymy okno g³ówne i od razu przypisujemy do pola klasy m_main
	m_main = CreateWindowExW(
		0, s_class_name.c_str(), L"2048",
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		400, 400, // Nadaj sta³y rozmiar, ¿eby widzieæ co siê dzieje
		nullptr, nullptr, m_instance, this);

	// 2. Tworzymy kwadracik u¿ywaj¹c m_main jako rodzica
	m_rect_window = CreateWindowExW(
		0,
		L"STATIC", // U¿ywamy wbudowanej klasy STATIC [cite: 344]
		nullptr,
		WS_CHILD | WS_VISIBLE | SS_CENTER, // Style okna potomnego [cite: 346]
		10, 10,  // Pozycja X, Y wewn¹trz okna g³ównego
		60, 60,  // Rozmiar kwadratu
		m_main,  // Rodzic musi byæ ju¿ zainicjalizowany 
		nullptr, m_instance, nullptr);

	return m_main;
}

LRESULT app_2048::window_proc_static(
	HWND window,
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	app_2048* app = nullptr;
	if (message == WM_NCCREATE)
	{
		auto p = reinterpret_cast<LPCREATESTRUCTW>(lparam);
		app = static_cast<app_2048*>(p->lpCreateParams);
		SetWindowLongPtrW(window, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(app));
	}
	else
	{
		app = reinterpret_cast<app_2048*>(
			GetWindowLongPtrW(window, GWLP_USERDATA));
	}
	if (app != nullptr)
	{
		return app->window_proc(window, message,
			wparam, lparam);
	}
	return DefWindowProcW(window, message, wparam, lparam);
}
LRESULT app_2048::window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message) {
	case WM_CLOSE:
		DestroyWindow(window);
		return 0;

	case WM_DESTROY:
		if (window == m_main)
			PostQuitMessage(EXIT_SUCCESS); // [cite: 165]
		return 0;

	case WM_KEYDOWN: { // Obs³uga klawiatury [cite: 898]
		RECT rc;
		GetWindowRect(m_rect_window, &rc);

		// 2. Konwertujemy wspó³rzêdne ekranowe na wspó³rzêdne wewn¹trz okna g³ównego
		MapWindowPoints(HWND_DESKTOP, m_main, (LPPOINT)&rc, 2);

		int x = rc.left;
		int y = rc.top;
		int step = 1; // O ile pikseli przesuwamy
		switch (wparam) {
		case 'X':
			DestroyWindow(window); // [cite: 172]
			return 0;

		case 'Z': {
			HBRUSH newBrush = CreateSolidBrush(RGB(0, 255, 0)); // [cite: 36]
			HBRUSH oldBrush = (HBRUSH)SetClassLongPtrW(window, GCLP_HBRBACKGROUND, (LONG_PTR)newBrush);
			if (oldBrush) DeleteObject(oldBrush); // [cite: 20]
			InvalidateRect(window, nullptr, TRUE);
			return 0;
		}
		case 'W': y -= step; break;
		case 'S': y += step; break;
		case 'A': x -= step; break;
		case 'D': x += step; break;

		case 'C': {
			HBRUSH hBrush = (HBRUSH)GetClassLongPtrW(window, GCLP_HBRBACKGROUND);
			if (hBrush) {
				LOGBRUSH lb;
				if (GetObjectW(hBrush, sizeof(LOGBRUSH), &lb) != 0) {
					COLORREF color = lb.lbColor;
					std::wstring msg = L"R: " + std::to_wstring(GetRValue(color)) +
						L" G: " + std::to_wstring(GetGValue(color)) +
						L" B: " + std::to_wstring(GetBValue(color));
					MessageBoxW(window, msg.c_str(), L"Aktualny kolor", MB_OK);
				}
			}
			return 0;
		}
		}
		SetWindowPos(m_rect_window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		break; // Wyjœcie ze switch(wparam) do domyœlnej obs³ugi
	}
	case WM_LBUTTONDOWN: { // Obs³uga myszy - POZA blokiem klawiatury
		RECT rect;
		int screenW = GetSystemMetrics(SM_CXSCREEN); // [cite: 43]
		int screenH = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(m_main, &rect);

		if (rect.left + 100 < screenW && rect.top + 100 < screenH) {
			SetWindowPos(m_main, nullptr, rect.left + 100, rect.top + 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER); // [cite: 44, 478]
		}
		return 0;
	}
	}

	// Wa¿ne: Wszystkie nieobs³u¿one komunikaty musz¹ trafiæ tutaj [cite: 160]
	return DefWindowProcW(window, message, wparam, lparam);
}
app_2048::app_2048(HINSTANCE instance)
	: m_instance{ instance }, m_main{}
{
	register_class();
	m_main = create_window();
}
int app_2048::run(int show_command)
{
	ShowWindow(m_main, show_command);
	MSG msg{};
	BOOL result = TRUE;
	while ((result = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{
		if (result == -1)
			return EXIT_FAILURE;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return EXIT_SUCCESS;
}