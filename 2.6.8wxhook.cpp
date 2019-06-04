// 2.6.8wxhook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "2.6.8wxhook.h"
#include "resource.h"
#include <atlstr.h>
#include <iostream>
#include <sstream>
using namespace std;

HWND hwnd = 0;
HANDLE WxProcessID = 0;
int m_Eax = 0;
int m_Ecx = 0;
int m_Edx = 0;
int m_Ebx = 0;
int m_Esp = 0;
int m_Ebp = 0;
int m_Esi = 0;
int m_Edi = 0;

DWORD GetWxMoudle(){
	return (DWORD)GetModuleHandle(L"WeChatWin.dll");
}

// 以下为hook设置的初始化子程序

VOID SetMsgHook(DWORD AddPonit, LPVOID AddSnake,HWND Hwnd){
	hwnd = Hwnd;

	WxProcessID = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());

	BYTE m_WriteAsm[5] = { 0 };

	DWORD m_MsgAddress = GetWxMoudle() + AddPonit;

	m_WriteAsm[0] = 0xE9;

	*(DWORD*)&m_WriteAsm[1] = (DWORD)AddSnake - m_MsgAddress - 5;

	WriteProcessMemory(WxProcessID, (LPVOID)m_MsgAddress, m_WriteAsm, 5, NULL);

}

// -------------------------这块东西下写着hook消息----------------------------------

VOID OutDubug(int Address){
	DWORD MsgAddress = Address - 0x178;
	TCHAR Msg[0x1000] = { 0 };
	CString a;
	swprintf_s(Msg, L"%s\r\n", *((LPVOID *)MsgAddress));
	SetDlgItemText(hwnd, EDIT_SHOWMSG, Msg);
}

DWORD m_TouchCall1 = GetWxMoudle() + 0x2599D0;
DWORD m_ReturnCall = GetWxMoudle() + 0x315E9B;
DWORD m_ReturnCallEax = GetWxMoudle() + 0x1065E18;
VOID __declspec(naked) BackMsgHook(){
	__asm {
		mov m_Eax, eax;
		mov m_Ecx, ecx;
		mov m_Edx, edx;
		mov m_Ebx, ebx;
		mov m_Esp, esp;
		mov m_Ebp, ebp;
		mov m_Esi, esi;
		mov m_Edi, edi;
	}
	OutDubug(m_Esi);
	__asm{
		//成功的
		mov eax, m_Eax;
		mov ecx, m_Ecx;
		mov edx, m_Edx;
		mov ebx, m_Ebx;
		mov esp, m_Esp;
		mov ebp, m_Ebp;
		mov esi, m_Esi;
		mov edi, m_Edi;
		mov eax, m_ReturnCallEax;
		call m_TouchCall1;
		jmp m_ReturnCall;
		//以下是失败的
		/*pushad;
		pushfd;
		mov m_Esi, esi;
		mov eax, m_ReturnCallEax;
		call m_TouchCall1;
		popad;
		popfd;
		jmp m_ReturnCall;*/
	}
}

// -------------------------这块东西下写着发送消息----------------------------------
