#include <assert.h>
#include <iostream>
#include "symphony/symphony.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void test_assert() {
    SYMPHONY_LOG_INFO(g_logger) << symphony::BacktraceToString(10);
    // SYMPHONY_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();

    int arr[] = {1, 3, 5, 7, 9, 11};

    SYMPHONY_LOG_INFO(g_logger)
        << symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0);
    SYMPHONY_LOG_INFO(g_logger)
        << symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1);
    SYMPHONY_LOG_INFO(g_logger)
        << symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4);
    SYMPHONY_LOG_INFO(g_logger)
        << symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 13);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0) == -1);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 2) == -2);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 3) == 1);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4) == -3);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 2);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 6) == -4);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 7) == 3);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 8) == -5);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 9) == 4);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == -6);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == 5);
    SYMPHONY_ASSERT(
        symphony::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 12) == -7);
    return 0;
}