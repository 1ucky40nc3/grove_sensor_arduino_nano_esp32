using namespace std;
#include <unity.h>
#include "measurement.h"

void test_hm330x_serializable_measurement()
{
    HM330XData data;
    data.pm_010_spm = 0;
    data.pm_025_spm = 0;
    data.pm_100_spm = 0;
    data.pm_010_ae = 0;
    data.pm_025_ae = 0;
    data.pm_100_ae = 0;
    Description desc = {"HM330X", "v1.0"};
    Measurement<HM330XData> measurement = {desc, data};
    JsonSerializableHM330XMeasurement serializable(measurement);
    const char *expected = "{\"desc\":{\"sensor\":\"HM330X\",\"version\":\"v1.0\"},\"data\":{\"pm_010_spm\":0,\"pm_025_spm\":0,\"pm_100_spm\":0,\"pm_010_ae\":0,\"pm_025_ae\":0,\"pm_100_ae\":0}}";
    TEST_ASSERT_EQUAL_STRING(expected, serializable.toJson().c_str());
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_hm330x_serializable_measurement);

    UNITY_END(); // End Unity

    return 0;
}