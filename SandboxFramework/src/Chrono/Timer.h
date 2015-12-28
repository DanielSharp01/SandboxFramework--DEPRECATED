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
		void Start();
		double Get();
		double Stop();
	};
}