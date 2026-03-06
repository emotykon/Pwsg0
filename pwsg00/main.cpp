#define WIN32_LEAN_AND_MEAN //wyklucza rzadko używane czesci biblioteki
#define NOMINMAX //konflikt z c++ wyklucza
#include <windows.h> //bib winapi
#include "app_2048.h" // biblioteka nasza
int WINAPI wWinMain(HINSTANCE instance/*naszainstancja*/,
	HINSTANCE /*starezawszenull*/,
	LPWSTR /*argumentyprogramu*/,
	int show_command/*sposóbwyswietlania*/)
{
	app_2048 app{ instance };//tworzy wszystko
	return app.run(show_command);//przetwarza wiadomosci
}



































//#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
//#include <windows.h>
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
//{
//    // 1. Poprawiona struktura (przecinki zamiast średników, dodany hInstance)
//    LPCWSTR clsname = L"My Window Class";
//    WNDCLASSEXW wcx = { 0 };
//    wcx.cbSize = sizeof(WNDCLASSEXW);
//    wcx.lpfnWndProc = DefWindowProcW;
//    wcx.hInstance = hInstance; // To jest wymagane!
//    wcx.lpszClassName = clsname;
//    wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // Dodaj kursor, żeby nie znikał
//
//    ATOM clsid = RegisterClassExW(&wcx);
//    if (!clsid) return -1;
//
//    // 2. Zmieniony styl z 0 na WS_OVERLAPPEDWINDOW, żeby okno było widać
//    HWND hWnd = CreateWindowExW(0, clsname, L"Hello World!",
//        WS_OVERLAPPEDWINDOW, 100, 100, 640, 360, nullptr,
//        nullptr, hInstance, nullptr); // hInstance zamiast nullptr
//    HWND hWnd2 = CreateWindowExW(0, clsname, L"Hello World!",
//        WS_OVERLAPPEDWINDOW, 100, 500, 640, 360, nullptr,
//        nullptr, hInstance, nullptr);
//
//    if (!hWnd) return -1;
//
//    ShowWindow(hWnd, nShowCmd);
//    ShowWindow(hWnd2, nShowCmd);
//
//    MSG msg = { 0 };
//    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
//        TranslateMessage(&msg); // Dobre praktyki
//        DispatchMessageW(&msg);
//    }
//
//    return 0;
//}
