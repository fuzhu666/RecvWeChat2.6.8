#pragma once
#include "stdafx.h"
DWORD GetWxMoudle();
VOID BackMsgHook();
VOID SetMsgHook(DWORD AddPonit, LPVOID AddSnake, HWND Hwnd);
VOID OutDubug(int Address);