// Definition of the Monad, i.e. type definition, unit function, and bind

#pragma once

#include <variant>

namespace monads {

// Note: for your particular use-case, you could alias this type and wrap the
//       success / error functions to hardcode the error type to eliminate one
//       template parameter. You could hardcode it to std::string for example.
//       Example, in your namespace:
//
//       template <typename T>
//       using Result = monads::Result<T, std::string>;
//
//       template <typename T>
//       Result<T> success(T const& value) { return monads::success<T, std::string>(value); }
//
//       template <typename T>
//       Result<T> error(std::string const& message) { return monads::error<T, std::string>(message); }

// #1 type definition (i.e. type 'constructor')
template <typename T, typename E>
using Result = std::variant<T, E>;

// #2a 'unit' function which takes a result value and wraps it into Result
// success :: T -> (Result T)
template <typename T, typename E>
constexpr Result<T, E> success(T const& value)
{
    return Result<T, E>(value);
}

// 2b
// error :: E -> (Result E)
template <typename T, typename E>
constexpr Result<T, E> error(E const& error_value)
{
    return Result<T, E>(error_value);
}

// #3 bind operator
// (>>=) :: (Result T) -> (T -> Result U) -> (Result U)
template <typename T, typename E, typename F>
Result<T, E> operator>>=(Result<T, E> const& r, F f)
{
    if(std::holds_alternative<T>(r))
    {
        return f(get<T>(r)); // compute the result
    }
    else
    {
        return r; // do nothing, contains an error message
    }
}

}
