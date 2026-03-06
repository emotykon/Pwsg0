


//#define WIN32_LEAN_AND_MEAN //wyklucza rzadko używane czesci biblioteki
//#define NOMINMAX //konflikt z c++ wyklucza
//#include <windows.h> //bib winapi
//#include "app_2048.h" // biblioteka nasza
//int WINAPI wWinMain(HINSTANCE instance/*naszainstancja*/,
//	HINSTANCE /*starezawszenull*/,
//	LPWSTR /*argumentyprogramu*/,
//	int show_command/*sposóbwyswietlania*/)
//{
//	app_2048 app{ instance };//tworzy wszystko
//	return app.run(show_command);//przetwarza wiadomosci
//}

//int numargs;
//lpwstr* arglist = commandlinetoargvw(getcommandlinew(), &numargs);
//if (arglist != nullptr)
//{
//    for (int i = 0; i < numargs; i++)
//    {
//        // arglist[0] to zawsze ścieżka do twojego programu .exe
//        // arglist[1], arglist[2] itd. to kolejne parametry
//    }
//    localfree(arglist); // ważne: musisz zwolnić pamięć!
//}
//
//app_2048::app_2048(hinstance instance, lpwstr lpcmdline)
//    : m_instance{ instance }, m_main{}
//{
//    // sprawdzenie czy podano jakikolwiek argument
//    if (lpcmdline && wcslen(lpcmdline) > 0)
//    {
//        messageboxw(nullptr, lpcmdline, l"otrzymano argument", mb_ok);
//    }
//
//    register_class(); [cite:180]
//        m_main = create_window(); [cite:185]
//}
//int winapi wwinmain(hinstance instance,
//    hinstance /*previnstance*/,
//    lpwstr lpcmdline, // tutaj są twoje argumenty [cite: 55]
//    int show_command)
//{
//    // możesz przekazać lpcmdline do konstruktora lub metody klasy
//    app_2048 app{ instance, lpcmdline };
//    return app.run(show_command);
//}
// app_2048.cpp
//app_2048::app_2048(HINSTANCE instance, LPWSTR lpCmdLine)
//    : m_instance{ instance }, m_main{}
//{
//    int argc;
//    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
//    int boardSize = 4; // Domyślnie 4x4
//
//    if (argv != nullptr) {
//        if (argc >= 2) boardSize = _wtoi(argv[1]); // Konwersja argumentu na int
//        LocalFree(argv);
//    }
//
//    // Ustawienie stałych w obiekcie board na podstawie boardSize
//    // (Wymaga modyfikacji klasy board, aby nie używała tylko constexpr)
//
//    register_class();
//    m_main = create_window(boardSize);
//}
//HWND app_2048::create_window(int grid)
//{
//    // Obliczamy rozmiar obszaru roboczego (klienta)
//    LONG margin = 10; [cite:287]
//        LONG tileSize = 60; [cite:289]
//        LONG totalW = grid * (tileSize + margin) + margin; [cite:291]
//        LONG totalH = grid * (tileSize + margin) + margin; [cite:291]
//
//        RECT rc = { 0, 0, totalW, totalH };
//    DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; [cite:115, 116]
//        AdjustWindowRectEx(&rc, style, FALSE, 0); [cite:322]
//
//        int winW = rc.right - rc.left; [cite:326]
//        int winH = rc.bottom - rc.top; [cite:326]
//
//        // Środkowanie na ekranie
//        int screenW = GetSystemMetrics(SM_CXSCREEN); [cite:419]
//        int screenH = GetSystemMetrics(SM_CYSCREEN); [cite:419]
//        int posX = (screenW - winW) / 2;
//    int posY = (screenH - winH) / 2;
//
//    HWND window = CreateWindowExW(0, s_class_name.c_str(), L"2048", style,
//        posX, posY, winW, winH, nullptr, nullptr, m_instance, this); [cite:120, 128]
//
//        // Tworzenie pól planszy (Child Windows)
//        for (int r = 0; r < grid; ++r) {
//            for (int c = 0; c < grid; ++c) {
//                CreateWindowExW(0, L"STATIC", nullptr, WS_CHILD | WS_VISIBLE | SS_CENTER,
//                    margin + c * (tileSize + margin), margin + r * (tileSize + margin),
//                    tileSize, tileSize, window, nullptr, m_instance, nullptr); [cite:342, 352]
//            }
//        }
//    return window;
//}

//1. Przez Wiersz poleceń(cmd) lub PowerShell
//To najbardziej bezpośredni sposób.Musisz przejść do folderu, w którym znajduje się Twój plik.exe(zazwyczaj folder x64\Debug lub Release w katalogu projektu).
//
//Otwórz folder w Eksploratorze plików.
//
//W pasku adresu wpisz cmd i naciśnij Enter.
//
//Wpisz nazwę swojego programu i po spacji dodaj argument, np.:
//
//2048_Project.exe 4
//
//2. W Visual Studio(Podczas pisania kodu)
//To najwygodniejsza metoda podczas testowania programu, ponieważ nie musisz go ręcznie uruchamiać z konsoli za każdym razem.
//
//W oknie Solution Explorer kliknij prawym przyciskiem myszy na swój projekt.
//
//Wybierz Properties(Właściwości).
//
//Przejdź do zakładki Configuration Properties->Debugging.
//
//W polu Command Arguments wpisz swój argument(np. 4).
//
//Kliknij OK i uruchom program przyciskiem Local Windows Debugger(F5).
































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
