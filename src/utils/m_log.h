#ifndef __M_LOG_H__
#define __M_LOG_H__


#include <fstream>
#include <time.h> 


#include "../_morisa.h"

#ifdef USE_CONCURRENCY
#include <mutex>
std::mutex m_log_mtx;
#endif 

MORISA_NAMESPACE_BEGIN


template <typename T>
void _m_log(std::ofstream& log, T t)
{
	log << t;
}

template <typename T, typename... Args>
void _m_log(std::ofstream& log, T t, Args... args)
{
	log << t;
	_m_log(log, args...);
}

template <typename... Args>
bool m_log(Args... args)
{
	using std::endl;
	using std::ofstream;

#ifdef USE_CONCURRENCY
	using std::lock_guard;
	lock_guard<std::mutex> m_mtx(m_log_mtx);
#endif

	ofstream log(LOG_PATH, std::ios::app);
	if (!log.is_open())
	{
		return false;
	}
	time_t cur;
	time(&cur);
	log << endl << ctime(&cur);

	_m_log(log, args...);

	log << endl;
	log.close();
	return true;
}

MORISA_NAMESPACE_END

#endif

