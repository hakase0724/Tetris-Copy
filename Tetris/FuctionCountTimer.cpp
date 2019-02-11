#include "stdafx.h"
#include "FuctionCountTimer.h"
#include <string>
#include <sstream>

#if _DEBUG
FuctionCountTimer::FuctionCountTimer()
{
	start = std::chrono::system_clock::now();
}


FuctionCountTimer::~FuctionCountTimer()
{
	auto end = std::chrono::system_clock::now();
	double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::wstringstream ws;
	ws << elapsed << std::endl;
	OutputDebugString(ws.str().c_str());
}
#endif
