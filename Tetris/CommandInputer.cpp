#include "stdafx.h"
#include "CommandInputer.h"


#if _DEBUG

void CommandInputer::InputCommand()
{
	OutputDebugString(_T("入力受付開始"));
	std::cin >> mCommand;
}

void CommandInputer::OutputCommand()
{
	OutputDebugStringA(mCommand.c_str());
	OutputDebugString(_T("入力受付終了"));
}

#endif