#ifndef __M_JTHREAD_H__
#define __M_JTHREAD_H__

#include <thread>

#include "../_morisa.h"

MORISA_NAMESPACE_BEGIN


class m_jthread {
public:
    template <typename... Arg>
    m_jthread(Arg&&... arg) : m_thread(std::forward<Arg>(arg)...) {}

    m_jthread(m_jthread&& other) noexcept : m_thread(std::move(other.m_thread)) {}

    m_jthread(const m_jthread&) = delete;

    ~m_jthread() { if (m_thread.joinable())  m_thread.join(); }

    m_jthread& operator=(m_jthread&& other) noexcept
    {
        using std::move;
        m_jthread(move(other)).swap(*this);
        return *this;
    }

    void swap(m_jthread& rhs)
    {
        using std::swap;
        swap(m_thread, rhs.m_thread);
    }

private:
    std::thread m_thread;
};


MORISA_NAMESPACE_END


#endif
