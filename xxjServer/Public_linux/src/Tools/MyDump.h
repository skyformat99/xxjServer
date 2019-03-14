#ifndef __MYDUMP_H_
#define __MYDUMP_H_
#include  <dbghelp.h> 
#include <winnt.h>
#include <shellapi.h>
#include <time.h>
#include <stdio.h>
#define _T 

#pragma comment(lib,  "dbghelp.lib")


class MyDmp
{
public:

	//�����쳣����ص�����
	//SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	//�����Ч 			
	//����  �������Լ����쳣�������󣬵���DisableSetUnhandledExceptionFilter ��ֹCRT ���ü��ɡ�

	//�쳣�������
	//EXCEPTION_EXECUTE_HANDLER equ 1 ��ʾ���Ѿ��������쳣,�������ŵؽ����� 
	//EXCEPTION_CONTINUE_SEARCH equ 0 ��ʾ�Ҳ�����,����������,����windows����Ĭ�ϵĴ��������ʾһ�������,������ 
	//EXCEPTION_CONTINUE_EXECUTION equ -1 ��ʾ�����Ѿ����޸�,����쳣����������ִ�� 
	static long   __stdcall   MyUnhandledExceptionFilter(_EXCEPTION_POINTERS*   ExceptionInfo)
	{
		//std::string str = (boost::format("%d.dmp") % time_t(0)).str().c_str();
		printf("------dump!\n");
		char _str[1024];
		memset(_str, 0, 1024 * sizeof(char));
		time_t t;
		time(&t);
		wsprintf(_str, "%d.dmp", t);

		HANDLE   hFile = CreateFile(_str, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			MINIDUMP_EXCEPTION_INFORMATION   ExInfo;

			ExInfo.ThreadId = ::GetCurrentThreadId();
			ExInfo.ExceptionPointers = ExceptionInfo;
			ExInfo.ClientPointers = NULL;

			//   write   the   dump
			BOOL   bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
			CloseHandle(hFile);
		}

		Sleep(60000);
		ShellExecute(NULL, "open", "AlarmMail.exe", NULL, NULL, SW_SHOWNORMAL);

		// 	WCHAR szAppPath[MAX_PATH];
		// 	GetModuleFileName(NULL, szAppPath, MAX_PATH);
		// 	(wcsrchr(szAppPath, '\\'))[1] = 0;
		// 	std::wstring strpath = L"/select, " + std::wstring(szAppPath) + L"0.dmp";

		//MessageBox(NULL, L"������ִ����뽫dmp�ļ�����������Ա��лл", L"��ʾ", MB_OK);
		//ShellExecute(NULL, L"open", L"explorer.exe", strpath.c_str(), NULL, SW_SHOWNORMAL);
		//theApp.PostThreadMessage(WM_QUIT, 0, 0);
		OnQuit();
		return EXCEPTION_EXECUTE_HANDLER;
	}

	static long  __stdcall MyUnhandledExceptionFilterNull(_EXCEPTION_POINTERS*   ExceptionInfo)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	static void DisableSetUnhandledExceptionFilter()
	{
		void *addr = (void*)GetProcAddress(LoadLibrary(_T("kernel32.dll")),
			"SetUnhandledExceptionFilter");
		if (addr)
		{
			unsigned char code[16];
			int size = 0;
			code[size++] = 0x33;
			code[size++] = 0xC0;
			code[size++] = 0xC2;
			code[size++] = 0x04;
			code[size++] = 0x00;

			DWORD dwOldFlag, dwTempFlag;
			VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
			WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
			VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
		}
	}

	static void OnQuit()
	{

	}

	static void OnExitProcess()
	{
		OnQuit();
		::ExitProcess(0);
	}
};
//�ڴ��� ����

#define MEMORY_CHICK \
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);\
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;\
	_CrtSetDbgFlag(tmpFlag);


// void detect_memory_leaks( bool on_off )  
// {  
// 	int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);  
// 	if(!on_off)  
// 		flags &= ~_CRTDBG_LEAK_CHECK_DF;  
// 	else {  
// 		flags |= _CRTDBG_LEAK_CHECK_DF;  
// 		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);  
// 		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);  
// 	}  
// 	_CrtSetDbgFlag( flags );  
// } 
////_CrtSetBreakAlloc(0x022C50A8);
#endif