using namespace std;
#include <unity.h>

void test_true()
{
    TEST_ASSERT_TRUE(true);
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_true);

    UNITY_END(); // End Unity

    return 0;
}