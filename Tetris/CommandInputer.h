#pragma once
#include <iostream>
#include <string>
#if _DEBUG
class CommandInputer
{
public:
	CommandInputer();
	~CommandInputer();
	void InputCommand();
	void OutputCommand();
private:
	std::string mCommand;
};
#endif
