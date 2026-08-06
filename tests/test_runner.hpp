#pragma once

#include <cstdio>

// Checks expr; records failure with location but does not abort — all checks run.
#define CHECK(expr)                                                                  \
    do {                                                                             \
        if (!(expr)) {                                                               \
            std::fprintf(stderr, "  FAIL: %s  (%s:%d)\n", #expr, __FILE__, __LINE__); \
            ++::sst_test::g_failures;                                                \
        }                                                                            \
    } while (0)

// Runs fn(), prints PASS/FAIL, accumulates failure count.
#define RUN_TEST(fn)                               \
    do {                                           \
        int before_ = ::sst_test::g_failures;      \
        (fn)();                                    \
        if (::sst_test::g_failures == before_)     \
            std::printf("[ PASS ] " #fn "\n");     \
        else                                       \
            std::printf("[ FAIL ] " #fn "\n");     \
        ++::sst_test::g_total;                     \
    } while (0)

// Returns 0 if all tests passed, 1 otherwise. Call at end of main().
#define TEST_RESULTS() ::sst_test::test_results()

namespace sst_test {
    inline int g_failures = 0;
    inline int g_total    = 0;

    inline int test_results() {
        std::printf("\n%d/%d passed\n", g_total - g_failures, g_total);
        return g_failures > 0 ? 1 : 0;
    }
}
