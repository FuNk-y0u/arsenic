#include "includes.h"
#include "error.h"

typedef struct
{
	HINSTANCE hInstance;
	int width, height;
	const LPCSTR title;
	void (*instF)(int);
}aWindow;

BOOL a_init_window(HINSTANCE hInstance, const LPCWSTR pClassName);

BOOL a_init_instance(HINSTANCE hInstance, const LPCSTR title, int w, int h, const LPCWSTR pClassName);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

aWindow* a_create_window (const LPCSTR title, int w, int h, void (*instF) (int));

#define A_ERROR() aCerror(__LINE__, __FILE__);