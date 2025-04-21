#pragma once

#include <windows.h>

#include <sal.h>

#define InitDebugLogs(pwszLogFilePath) \
	DebugLogs debugLogs(pwszLogFilePath)

#define DebugComment(pwszLogString) \
	debugLogs.AddString( pwszLogString L"\n", sizeof(pwszLogString) + sizeof(L'\n') )

#define DebugErrorCode(dwErrorCode) \
	debugLogs.AddErrorCode(dwErrorCode)

class DebugLogs
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	private:
		HANDLE hLogFile;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	public:
		DebugLogs( _In_ LPCWSTR pwszLogFilePath );
		~DebugLogs();
		
		_Success_(return == TRUE ) BOOL AddString( _In_ LPCWSTR pwszLogString, _In_ DWORD dwStringSize );
		_Success_(return == TRUE ) BOOL AddErrorCode( _In_ DWORD dwErrorCode );
	
	private:
		void ConvertDwordToString( _In_ DWORD dwErrorCode, _Out_ LPWSTR pwszErrorCode );
};
