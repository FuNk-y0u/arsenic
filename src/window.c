#include"../includes/window.h"

void (*Gwinproc)(int);

BOOL a_init_window(HINSTANCE hInstance, const LPCWSTR pClassName)
{

	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = pClassName;
	wc.hIconSm = NULL;

	return RegisterClassEx(&wc);
}

BOOL a_init_instance(HINSTANCE hInstance, const LPCSTR title, int w, int h, const LPCWSTR pClassName)
{

	HWND hWnd = CreateWindowEx(
		0,pClassName,
		title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		100,100,
		w,h,
		NULL, NULL, hInstance, NULL
	);

	if(!hWnd)
		return FALSE;

	ShowWindow(hWnd, SW_SHOW);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
	(*Gwinproc)(msg);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

aWindow* a_create_window(const LPCSTR title, int w, int h, void (*procF) (int))
{
	aWindow* window = malloc(sizeof(aWindow));
	window->width = w;
	window->height = h;
	HINSTANCE hInstance;
	const LPCWSTR pClassName = L"MainWin";
	Gwinproc = procF; 

	GetModuleHandle(NULL);
	
	printf("[ARSENIC INFO] starting window..\n");
	if(!a_init_window(hInstance, pClassName))
	{
		printf("[ARSENIC  ERROR] couldn't initialize window\n");
		return 0;
	}
	printf("[ARSENIC INFO] Creating Window %dx%d\n",w,h);

	if(!a_init_instance(hInstance,title,w,h,pClassName))
	{
		printf("[ARSENIC  ERROR] couldn't create window\n");	
		return 0;
	}

	MSG msg;

	while(GetMessage(&msg, NULL, 0,0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
	
}