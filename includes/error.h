#include "includes.h"

typedef struct
{
	int line;
	const char* file;
	HRESULT hr;
}aError;

char* aTranslateError( HRESULT hr);
HRESULT GetErrorCode();
char* aGetErrorStr();
void aGetError();
void aCerror(int line, const char* file);



