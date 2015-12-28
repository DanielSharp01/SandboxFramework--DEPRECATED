#pragma once

#include "Timer.h"

namespace Chrono
{
	class TimerCounter : public Timer
	{
	private:
		int m_Counter;
		double lastCheck;
	public:
		int AdvanceCounter();
		int GetCount();
		double GetCountOver(double second);
	};
}