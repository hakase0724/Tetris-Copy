#include "stdafx.h"
#include "CommandInputer.h"


#if _DEBUG

void CommandInputer::InputCommand()
{
	OutputDebugString(_T("���͎�t�J�n"));
	std::cin >> mCommand;
}

void CommandInputer::OutputCommand()
{
	OutputDebugStringA(mCommand.c_str());
	OutputDebugString(_T("���͎�t�I��"));
}

#endif