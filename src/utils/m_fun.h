#ifndef __M_FUN_H__
#define __M_FUN_H__

#include <type_traits>
#include <vector>

#include "../_morisa.h"


MORISA_NAMESPACE_BEGIN

template <typename...>
using m_void = void;

struct m_false { constexpr static bool value{ false }; };
struct m_true { constexpr static bool value{ true }; };

template <typename T, typename = m_void<>>
struct m_has_resize : m_false {  };
template <typename T>
struct m_has_resize<T, m_void<decltype(std::declval<T&>().resize(1U))>> : m_true{ };

template <typename T, typename = m_void<>>
struct m_has_reserve : m_false {};
template <typename T>
struct m_has_reserve<T, m_void<decltype(std::declval<T&>().reserve(1U))>> : m_true { };

template <typename T, typename V, typename = m_void<>>
struct m_has_emplace_back : m_false{ };
template <typename T, typename V>
struct m_has_emplace_back<T, V, m_void<decltype(std::declval<T&>().emplace_back(std::declval<V&>()))>> : m_true { };



auto m_composite_fun()
{
    return [](auto&& arg) -> decltype(auto)
    {
        return std::forward<decltype(arg)>(arg);
    };
}

template <typename Fn>
auto m_composite_fun(Fn&& fn)
{
    return[fn = std::forward<Fn>(fn)](auto&&... args) -> decltype(auto)
    {
        return fn(std::forward<decltype(args)>(args)...);
    };
}

template <typename Fn, typename... Fns>
auto m_composite_fun(Fn&& fn, Fns&&... fns)
{
    return[fn = std::forward<Fn>(fn), fns...](auto&&... args) -> decltype(auto)
    {
        return fn(m_composite_fun(std::move(fns)...)(std::forward<decltype(args)>(args)...));
    };
}

MORISA_NAMESPACE_END

#endif