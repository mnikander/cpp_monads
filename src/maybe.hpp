// Definition of the Monad, i.e. type definition, unit function, and bind

#pragma once

#include <optional>

namespace monads {

// #1 type definition (i.e. type 'constructor')
template <typename T>
using Maybe = std::optional<T>;

// #2 'unit' function which takes a value and wraps it into Maybe
// just :: T -> (Maybe T)
template <typename T>
constexpr Maybe<T> just(T const& value)
{
    return Maybe<T>(value);
}

constexpr auto nothing = std::nullopt;

// #3 bind operator
// (>>=) :: (Maybe T) -> (T -> Maybe U) -> (Maybe U)
template <typename T, typename F>
std::optional<T> operator>>=(Maybe<T> const& ma, F f)
{
    if(ma.has_value())
    {
        return f(ma.value());
    }
    else
    {
        return nothing;
    }
}

}
