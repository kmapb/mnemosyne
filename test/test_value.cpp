#include <gtest/gtest.h>
#include <pqxx/pqxx>

#include "../value.hpp"

using namespace mnem;

// This is a trivial test that always passes
TEST(TrivialTest, AlwaysPasses) {
    EXPECT_TRUE(true);
}

TEST(Dynamism, ValuePolymorphism) {
    auto v1 = Value::String("she works hard for the monkeys!");
    auto v2 = v1;
    v2 = Value::Int(123);
    EXPECT_EQ(v2.asInt(), 123);
    EXPECT_EQ(v1.asString(), std::string("she works hard for the monkeys!"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}