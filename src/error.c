#include"../includes/error.h"


char* aTranslateError( HRESULT hr)
{
	char* eMsg = NULL;

	DWORD eMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&eMsg,0,NULL
	);

	if(eMsgLen == 0 )
	{
		DWORD eMsgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&eMsg,0,NULL
		);
		if(eMsgLen == 0)
		{
			return "Error Code Unidentifyable";
		}
	}
	return eMsg;
}

HRESULT GetErrorCode()
{
	HRESULT hr;
	return hr;
}

char* aGetErrorStr()
{
	return aTranslateError(GetErrorCode());
}

void aGetError()
{
	printf("[WINDOWS ERROR CODE] %d\n", GetErrorCode());
	printf("[WINDOWS ERROR STR] %s\n", aGetErrorStr());
}

void aCerror(int line, const char* file)
{
	printf("[ARSENIC ERROR] in line %d\n[ARSENIC ERROR] in file %s\n", line, file);
	aGetError();
}