#include <gtest/gtest.h>
#include <string>
#include "../src/maybe.hpp"

TEST(maybe, nothing)
{
    monads::Maybe<std::string> const maybe = monads::nothing;

    EXPECT_FALSE(maybe.has_value());
}

TEST(maybe, just)
{
    std::string const text{"hello world"};

    auto const maybe = monads::just(text);

    ASSERT_TRUE(maybe.has_value());

    std::string const s = maybe.value();
    EXPECT_EQ(s, text);
}

TEST(maybe, bind)
{
    using namespace monads;

    Maybe<float> const a = just(2.0F);
    Maybe<float> const b = nothing;

    auto safe_reciprocal = [](float denominator) -> Maybe<float>
    {
        if (denominator == 0)
        {
            return nothing;
        }
        else
        {
            return just(1.0F / denominator);
        }
    };

    auto const firstResult = a >>= safe_reciprocal;
    ASSERT_TRUE(firstResult.has_value());
    EXPECT_FLOAT_EQ(firstResult.value(), 0.5F);

    auto const secondResult = b >>= safe_reciprocal;
    ASSERT_FALSE(secondResult.has_value());
}
