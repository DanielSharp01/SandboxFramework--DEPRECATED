#include "Timer.h"

namespace Chrono
{
	void Timer::Start()
	{
		m_StartingPoint = Clock::now();
		m_Running = true;
	}

	double Timer::Get()
	{
		if (!m_Running) return 0;
		TimePoint endPoint = Clock::now();
		return Duration(endPoint - m_StartingPoint).count();
	}

	double Timer::Stop()
	{
		double ret = Get();
		m_Running = false;
		return ret;
	}
}