#include "GameProcessor.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
CGameProcessor * gameProcessor = nullptr;
CGraphicsProcessor * graphicsProcessor = nullptr;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  =_T("mainWin");
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            NULL);

        return 1;
    }

	static TCHAR szWindowClass[] = _T("win32app");
	static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	/*HWND hWnd = CreateWindow(
		(LPCWSTR) "mainWin",
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);*/


	HWND hWnd = CreateWindowEx(
		WS_EX_APPWINDOW, _T("mainWin"), szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		DWORD x = GetLastError();
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/*===========================================
		initialize game stuff here
	=============================================*/
	OIS::ParamList pl;
	std::ostringstream wnd;
	wnd << (size_t)hWnd;
	pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	gameProcessor = new CGameProcessor(pl);
	CAudioProcessor::initAudio();

	//resize window and change title
	SetWindowPos(hWnd, HWND_TOP, 0,0,CGameProcessor::getWinWidth(), CGameProcessor::getWinHeight(), SWP_NOMOVE);

	std::wstring x;
	std::string y = CGameProcessor::getWinTitle();
	x.assign(y.begin(), y.end());
	LPCWSTR title = (LPCWSTR)x.c_str();
	SetWindowText(hWnd, title);

	//resources
	CContent::init();

	graphicsProcessor = new	CGraphicsProcessor(hWnd, CGameProcessor::getWinWidth(), CGameProcessor::getWinHeight());
	graphicsProcessor->prepareShader();

	//need a test map - KEEP IT SIMPLE
	CMap * testMap = new CMap(true);
	CBasePlayer * testPlayer = new CBasePlayer();
	testPlayer->initialize("test",0,0,0);
	testPlayer->attachShaders(GLContext::texturedVertexShader, GLContext::texturedFragmentShader);
	testMap->insertEntity(testPlayer, 0);
	gameProcessor->setCurrentMap(testMap);

	MSG msg;
	CMap currentMap;
    while (!gameProcessor->quit())
    {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		gameProcessor->run();
		//currentMap = gameProcessor->getCurrentMap();
		//graphicsProcessor->render(&currentMap);
		graphicsProcessor->render(testMap);
		//graphicsProcessor->testDraw();
    }

	/*=============================================
		WAIT!! Don't you wanna stay and cuddle?!
		NO!! CLEAN THAT SHIT UP!!
	===============================================*/
	delete gameProcessor;
	gameProcessor = nullptr;
	delete graphicsProcessor;
	graphicsProcessor = nullptr;
	CAudioProcessor::tearDown(); //RAEGAN SMASH
	CContent::tearDown();
	delete testMap;
	testMap = nullptr;

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);


        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
		
		//Raegan sleep...
		//gameProcessor->
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}