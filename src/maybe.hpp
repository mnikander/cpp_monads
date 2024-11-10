//! \brief definition of the maybe Monad, i.e. type definition, unit function, and bind

#pragma once

#include <optional>

namespace monads {

// #1 type definition (i.e. type 'constructor')
template <typename T>
using Maybe = std::optional<T>;

// #2 'unit' function which takes a value and wraps it into Maybe
// Just :: a -> (M a)
template <typename T>
constexpr Maybe<T> Just(T const& value)
{
    return Maybe<T>(value);
}

constexpr auto Nothing = std::nullopt;

// #3 bind operator
// (>>=) :: (M a) (a -> M b) -> (M b)
template <typename T, typename F>
std::optional<T> operator>>=(Maybe<T> const& ma, F f)
{
    if(ma.has_value())
    {
        return f(ma.value());
    }
    else
    {
        return Nothing;
    }
}

}
