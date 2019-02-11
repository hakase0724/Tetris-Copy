#pragma once
#include <iostream>
#include <chrono>

class FuctionCountTimer
{
#if _DEBUG
public:
	FuctionCountTimer();
	~FuctionCountTimer();
private:
	std::chrono::system_clock::time_point start;
#endif
};

