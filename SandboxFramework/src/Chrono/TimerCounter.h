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

		int AdvanceCounter()
		{
			return ++m_Counter;
		}

		int GetCount()
		{
			return m_Counter;
		}

		double GetCountOver(double second)
		{
			double total = Get();		
			double cos = (double)m_Counter / (total - lastCheck) / second;
			
			lastCheck = total;
			m_Counter = 0;

			return cos;
		}
	};
}