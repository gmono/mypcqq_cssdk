// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "Stdafx.h"
extern void init();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	try
	{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH:
			init();
			break;
			//���ó�ʼ������
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}
	}
	catch (...)
	{

	}
	return TRUE;
}

