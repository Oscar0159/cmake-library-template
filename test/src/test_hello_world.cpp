#include<gtest/gtest.h>

#include "hello_world.h"

TEST(HelloWorldTest, ReturnsCorrectString) {
    char* result = hello_world();
    EXPECT_STREQ(result, "Hello, world!");
}

TEST(HelloWorldTest, ReturnsCorrectStringWithFoo) {
    char* result = hello_world_foo();
    char expected[] = "Hello, world! bar";
    EXPECT_STREQ(result, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}