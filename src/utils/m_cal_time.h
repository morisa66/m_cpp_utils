#ifndef __M_CAL_TIME_H__
#define __M_CAL_TIME_H__

#include <time.h>
#include <algorithm>

#include "../_morisa.h"

MORISA_NAMESPACE_BEGIN


template<typename T>
struct m_ret_type
{
	T data;
	double time_ms{ 0.0 };
	double time_s{ 0.0 };

	m_ret_type(const T& _data, const double _time_ms, const double _time_s)
		noexcept:data(_data), time_ms(_time_ms), time_s(_time_s){}
};



template<typename Fn, typename... Args>
auto m_cal_time_with_return(Fn& fn, Args&&... args)
{
	time_t t1 = clock();
	auto _tmp = fn(std::forward<Args>(args)...);
	time_t t2 = clock();
	return m_ret_type<decltype(_tmp)>
	(
		_tmp,
		static_cast<double>(t2) - static_cast<double>(t1),
		(static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC
	);
}

template<typename Fn, typename... Args>
auto m_cal_time(Fn& fn, Args&&... args)
{
	time_t t1 = clock();
	fn(std::forward<Args>(args)...);
	time_t t2 = clock();
	return m_ret_type<decltype(0)>
	(
		0,
		static_cast<double>(t2) - static_cast<double>(t1),
		(static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC
	);
}

MORISA_NAMESPACE_END

#endif
