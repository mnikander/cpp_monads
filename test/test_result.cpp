#include <gtest/gtest.h>
#include <string>
#include "../src/result.hpp"

// convenience functions for unit testing

template <typename R, typename E>
bool is_successful(monads::Result<R, E> const& result)
{
    return std::holds_alternative<R>(result);
}

template <typename R, typename E>
R get_value(monads::Result<R, E> const& result)
{
    return std::get<R>(result);
}

template <typename R, typename E>
E get_error(monads::Result<R, E> const& result)
{
    return std::get<E>(result);
}

// example function which can fail with an error
auto safe_reciprocal(float denominator) -> monads::Result<float, std::string>
{
    if (denominator == 0)
    {
        return monads::error<float, std::string>("safe_reciprocal error: division by zero.");
    }
    else
    {
        return monads::success<float, std::string>(1 / denominator);
    }
};

// testcases

TEST(result, error)
{
    using namespace monads;

    auto const result = error<float, std::string>("This is an error.");

    EXPECT_FALSE(is_successful(result));
}

TEST(result, success)
{
    using namespace monads;

    auto const result = success<float, std::string>(42);

    EXPECT_TRUE(is_successful(result));
    EXPECT_FLOAT_EQ(get_value(result), 42.0f);
}

TEST(result, bind_success)
{
    using namespace monads;

    auto const a = success<float, std::string>(2.0f);

    auto const b = a >>= safe_reciprocal;
    ASSERT_TRUE(is_successful(b));
    EXPECT_FLOAT_EQ(get_value(b), 0.5F);
}

TEST(result, bind_error_divide_by_zero)
{
    using namespace monads;

    auto const a = success<float, std::string>(0.0f);

    auto const b = a >>= safe_reciprocal;
    ASSERT_FALSE(is_successful(b));
    EXPECT_EQ(get_error(b), std::string("safe_reciprocal error: division by zero."));
}

TEST(result, bind_previous_error)
{
    using namespace monads;

    auto const a = error<float, std::string>("some error message from an earlier computation");

    auto const b = a >>= safe_reciprocal;
    ASSERT_FALSE(is_successful(b));
    EXPECT_EQ(get_error(b), std::string("some error message from an earlier computation"));

}
