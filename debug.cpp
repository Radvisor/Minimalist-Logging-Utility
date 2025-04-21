#include <windows.h>

#include <sal.h>

#include "debug.h"

DebugLogs::DebugLogs( _In_ LPCWSTR pwszLogFilePath )
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	this->hLogFile = CreateFileW( 	pwszLogFilePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
}

DebugLogs::~DebugLogs()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	CloseHandle(this->hLogFile);
}

_Success_(return == TRUE )
BOOL DebugLogs::AddString( _In_ LPCWSTR pwszLogString, _In_ DWORD dwStringSize )
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BOOL bReturnValue = FALSE;

	DWORD dwBytesWritten = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if( !WriteFile( this->hLogFile, pwszLogString, dwStringSize, &dwBytesWritten, NULL ) )
		goto end;
	if( dwBytesWritten != dwStringSize )
		goto end;
	
	bReturnValue = TRUE;

end:
	return bReturnValue;
}

_Success_(return == TRUE )
BOOL DebugLogs::AddErrorCode( _In_ DWORD dwErrorCode )
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	BOOL bReturnValue = FALSE;
	
	//First part's length + number of decimals to show + escape character + string terminator.
	WCHAR wszErrorStatement[14 + 10 + 1 + 1] = L"Error code: 0d";
	
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//14 is the address of the 0-padded number.
	this->ConvertDwordToString( dwErrorCode, &wszErrorStatement[14] );
	
	if( !this->AddString( wszErrorStatement , sizeof(wszErrorStatement) ) )
		goto end;
	
	bReturnValue = TRUE;

end:
	return bReturnValue;
}

void DebugLogs::ConvertDwordToString( _In_ DWORD dwErrorCode, _Out_ LPWSTR pwszErrorCode )
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

    	DWORD dwDivisor = 1000000000;
	DWORD dwDigit;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////

	for( auto i = 0; i < 10; i++ )
    	{
		dwDigit = dwErrorCode / dwDivisor;
		pwszErrorCode[i] = (WCHAR)(L'0' + dwDigit);
		dwErrorCode %= dwDivisor;
		dwDivisor /= 10;
    	}
	pwszErrorCode[10] = L'\n';
	pwszErrorCode[10] = L'\0';
}
