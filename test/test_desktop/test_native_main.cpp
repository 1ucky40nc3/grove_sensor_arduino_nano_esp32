using namespace std;
#include <unity.h>
#include "add.h"
#include "measure.h"

void test_addition()
{
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(-1, add(-2, 1));
    TEST_ASSERT_EQUAL(0, add(0, 0));
}

void test_measure_hm330x_data()
{
    HM330XData data(0, 0, 0, 0, 0, 0);
    const char *expected = "{ \"pm_010_spm\": 0, \"pm_025_spm\": 0, \"pm_100_spm\": 0, \"pm_010_ae\": 0, \"pm_025_ae\": 0, \"pm_100_ae\": 0 }";
    TEST_ASSERT_EQUAL_STRING(expected, data.toJson().c_str());
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    RUN_TEST(test_addition);            // Run the test
    RUN_TEST(test_measure_hm330x_data); // Run the test

    UNITY_END(); // End Unity

    return 0;
}