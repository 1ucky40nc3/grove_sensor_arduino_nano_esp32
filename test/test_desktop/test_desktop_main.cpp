using namespace std;
#include <iostream>
#include <unity.h>
#include <memory>
#include "measurement.h"
#include "utils.h"

void test_parseHm330xMeasurement()
{
    uint8_t data[30] = {0, 255, 0, 0, 0, 30, 0, 38, 0, 41, 0, 24, 0, 35, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0};
    const HM330XMeasurement measurement = parseHm330xMeasurement(data);
    TEST_ASSERT_TRUE(measurement.data.pm_010_ae == 24);
    TEST_ASSERT_TRUE(measurement.data.pm_025_ae == 35);
    TEST_ASSERT_TRUE(measurement.data.pm_100_ae == 41);
    TEST_ASSERT_TRUE(measurement.data.pm_010_spm == 30);
    TEST_ASSERT_TRUE(measurement.data.pm_025_spm == 38);
    TEST_ASSERT_TRUE(measurement.data.pm_100_spm == 41);
    TEST_ASSERT_TRUE(measurement.data.sensor_num == 0);
    TEST_ASSERT_EQUAL_STRING(measurement.desc.sensor.c_str(), "HM330X");
    TEST_ASSERT_EQUAL_STRING(measurement.desc.version.c_str(), "v1.0");
}

void test_convertHm330xMeasurementToJson()
{
    HM330XData data;
    data.pm_010_spm = 0;
    data.pm_025_spm = 0;
    data.pm_100_spm = 0;
    data.pm_010_ae = 0;
    data.pm_025_ae = 0;
    data.pm_100_ae = 0;
    Description desc = {"HM330X", "v1.0"};
    HM330XMeasurement measurement;
    measurement.data = data;
    measurement.desc = desc;

    const char *expected = "{\"desc\":{\"sensor\":\"HM330X\",\"version\":\"v1.0\"},\"data\":{\"pm_010_spm\":0,\"pm_025_spm\":0,\"pm_100_spm\":0,\"pm_010_ae\":0,\"pm_025_ae\":0,\"pm_100_ae\":0}}";
    string result = convertHm330xMeasurementToJson(measurement);
    TEST_ASSERT_EQUAL_STRING(expected, result.c_str());
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_parseHm330xMeasurement);
    RUN_TEST(test_convertHm330xMeasurementToJson);

    UNITY_END(); // End Unity

    return 0;
}