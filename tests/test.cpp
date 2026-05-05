#include <gtest/gtest.h>
#include <stdexcept>
#include "LruBuffer.h"

TEST(LruBufferTest, SetAndGet) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    EXPECT_EQ(buffer.get(1), 10);
    EXPECT_EQ(buffer.get(2), 20);
}

TEST(LruBufferTest, LruEviction) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    buffer.set(3, 30);
    EXPECT_FALSE(buffer.check(1));
    EXPECT_TRUE(buffer.check(2));
    EXPECT_TRUE(buffer.check(3));
}

TEST(LruBufferTest, UpdateExisting) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    buffer.set(1, 100);
    EXPECT_EQ(buffer.get(1), 100);
}

TEST(LruBufferTest, CheckKey) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    EXPECT_TRUE(buffer.check(1));
    EXPECT_FALSE(buffer.check(2));
}

TEST(LruBufferTest, EraseKey) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    buffer.erase(1);
    EXPECT_FALSE(buffer.check(1));
}

TEST(LruBufferTest, EraseNonExistentThrows) {
    LruBuffer buffer(2);
    EXPECT_THROW(buffer.erase(1), std::runtime_error);
}

TEST(LruBufferTest, GetNonExistentThrows) {
    LruBuffer buffer(2);
    EXPECT_THROW(buffer.get(1), std::runtime_error);
}

TEST(LruBufferTest, AccessOrderUpdate) {
    LruBuffer buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    buffer.get(1);
    buffer.set(3, 30);
    EXPECT_FALSE(buffer.check(2));
    EXPECT_TRUE(buffer.check(1));
    EXPECT_TRUE(buffer.check(3));
}
