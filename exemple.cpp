#include <windows.h>

#include "debug.h"

int main(void)
{
	InitDebugLogs(L"C:\\Users\\exemple\\Desktop\\logs.txt");

	//Lets' try to retrieve the handle of a DLL that shouldn't be present
	DebugComment(L"Attempting to call GetModuleHandle :");

	HMODULE hDll = GetModuleHandleW(L"Exemple.dll");
	if(hDll)
	{
		DebugComment(L"Success!");
	}
	else DebugErrorCode( GetLastError() );

	return 0;
}
