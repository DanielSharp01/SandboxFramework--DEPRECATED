#include "TimerCounter.h"

namespace Chrono
{
	int TimerCounter::AdvanceCounter()
	{
		return ++m_Counter;
	}

	int TimerCounter::GetCount()
	{
		return m_Counter;
	}

	double TimerCounter::GetCountOver(double second)
	{
		double total = Get();
		double cntOSecond = (double)m_Counter / (total - lastCheck) / second;

		lastCheck = total;
		m_Counter = 0;

		return cntOSecond;
	}
}