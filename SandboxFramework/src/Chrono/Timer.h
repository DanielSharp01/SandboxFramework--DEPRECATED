#pragma once

#include <chrono>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Duration = std::chrono::duration<double>;

namespace Chrono
{
	class Timer
	{
	protected:
		TimePoint m_StartingPoint;
		bool m_Running = false;

	public:
		void Start()
		{
			m_StartingPoint = Clock::now();
			m_Running = true;
		}

		double Get()
		{
			if (!m_Running) return 0;
			TimePoint endPoint = Clock::now();
			return Duration(endPoint - m_StartingPoint).count();
		}

		double Stop()
		{
			double ret = Get();
			m_Running = false;
			return ret;
		}
	};
}