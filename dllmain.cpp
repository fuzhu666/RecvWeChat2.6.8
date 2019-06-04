// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "resource.h"
#include "2.6.8wxhook.h"
#include <Windows.h>
#include <stdio.h>

BOOL CALLBACK DialogProc(
	HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam
	);
void ShowWin(HINSTANCE hwnd);
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ShowWin, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void ShowWin(HINSTANCE hwnd){
	DialogBox(hwnd, MAKEINTRESOURCE(WXMAIN), 0, DialogProc);
}

BOOL CALLBACK DialogProc(
	HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam
	){
	switch (msg)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	case WM_COMMAND:
		switch (wparam)
		{
		case HOOK_MSG:
			SetMsgHook(0x315E93,&BackMsgHook,hwnd);
		default:
			break;
		}
	default:
		break;
	}
	return false;
}
