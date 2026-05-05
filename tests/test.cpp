#include <gtest/gtest.h>
#include <stdexcept>
#include "LruBuffer.h"


TEST(LruBufferTest, SetAndGet) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    
    EXPECT_EQ(buffer.get(2), 20);
    EXPECT_EQ(buffer.get(1), 10);
}

TEST(LruBufferTest, GetOLd) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    buffer.set(3, 30);
    
    EXPECT_THROW(buffer.get(1), std::runtime_error);
}

TEST(LruBufferTest, GetNone) {
    LruBuffer<int, int> buffer(2);
    EXPECT_THROW(buffer.get(1), std::runtime_error);
}

TEST(LruBufferTest, GetWhile) {
    LruBuffer<int, int> buffer(2);

    buffer.set(1, 10);
    buffer.set(2, 20);
    EXPECT_EQ(buffer.get(1), 10);
    buffer.set(3, 30);
    
    EXPECT_THROW(buffer.get(2), std::runtime_error);
}

TEST(LruBufferTest, SameKeyMultipleUpdates) {
    LruBuffer<int, int> buffer(2);

    buffer.set(1, 100);
    buffer.set(1, 200);
    buffer.set(1, 300);
    buffer.set(2, 400);
    buffer.set(3, 500);
    
    EXPECT_FALSE(buffer.check(1));   
    EXPECT_TRUE(buffer.check(2));
    EXPECT_TRUE(buffer.check(3));
}

TEST(LruBufferTest, LruEviction) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    buffer.set(3, 30);
    EXPECT_FALSE(buffer.check(1));
    EXPECT_TRUE(buffer.check(2));
    EXPECT_TRUE(buffer.check(3));
}

TEST(LruBufferTest, UpdateExisting) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.set(1, 100);
    EXPECT_EQ(buffer.get(1), 100);
}

TEST(LruBufferTest, CheckKey) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    EXPECT_TRUE(buffer.check(1));
    EXPECT_FALSE(buffer.check(2));
}

TEST(LruBufferTest, EraseKey) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.erase(1);
    EXPECT_FALSE(buffer.check(1));
}

TEST(LruBufferTest, EraseNonExistentThrows) {
    LruBuffer<int, int> buffer(2);
    EXPECT_THROW(buffer.erase(1), std::runtime_error);
}

TEST(LruBufferTest, GetNonExistentThrows) {
    LruBuffer<int, int> buffer(2);
    EXPECT_THROW(buffer.get(1), std::runtime_error);
}

TEST(LruBufferTest, AccessOrderUpdate) {
    LruBuffer<int, int> buffer(2);
    buffer.set(1, 10);
    buffer.set(2, 20);
    buffer.get(1);
    buffer.set(3, 30);
    EXPECT_FALSE(buffer.check(2));
    EXPECT_TRUE(buffer.check(1));
    EXPECT_TRUE(buffer.check(3));
}

TEST(LruBufferTest, SetRvalueLvalue) {
    LruBuffer<int, int> buffer(2);
    int k = 1;
    int v = 10;
    EXPECT_NO_THROW(buffer.set(k, 10));
    EXPECT_NO_THROW(buffer.set(1, v));
    EXPECT_NO_THROW(buffer.set(k, v));
    EXPECT_NO_THROW(buffer.set(1, 10));
}

TEST(LruBufferTest, GetRvalueLvalue) {
    LruBuffer<int, int> buffer(2);
    int k = 1;
    int v = 10;
    buffer.set(1, 10);

    EXPECT_NO_THROW(buffer.get(k, 10));
    EXPECT_NO_THROW(buffer.get(1, v));
    EXPECT_NO_THROW(buffer.get(k, v));
    EXPECT_NO_THROW(buffer.get(1, 10));
}


