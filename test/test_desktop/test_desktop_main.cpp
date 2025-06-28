using namespace std;
#include <iostream>
#include <unity.h>
#include <memory>
#include "measurement.h"
#include "utils.h"
#include "ChecksumException.h"
#include "BufferNullptfException.h"
#include "config.h"

void test_ChecksumException()
{
    try
    {
        throw ChecksumException("test");
    }
    catch (const exception &ex)
    {
        TEST_ASSERT_EQUAL_STRING("ChecksumException: test", ex.what());
    }
}

void test_BufferNulptrException()
{
    try
    {
        throw BufferNulptrException("test");
    }
    catch (const exception &ex)
    {
        TEST_ASSERT_EQUAL_STRING("BufferNulptrException: test", ex.what());
    }
}

void test_isValidHm330xBufferChecksum()
{
    uint8_t validData[30] = {0, 255, 0, 0, 0, 30, 0, 38, 0, 41, 0, 24, 0, 35, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0};
    TEST_ASSERT_TRUE(isValidHm330xBufferChecksum(validData));
    uint8_t invalidData[30] = {0, 255, 0, 0, 0, 31, 0, 38, 0, 41, 0, 24, 0, 35, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0};
    TEST_ASSERT_FALSE(isValidHm330xBufferChecksum(invalidData));
}

void test_parseHm330xMeasurement_validData()
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
    TEST_ASSERT_EQUAL_STRING(measurement.desc.sensor.c_str(), MEASUREMENT_SENSOR.c_str());
    TEST_ASSERT_EQUAL_STRING(measurement.desc.version.c_str(), MEASUREMENT_VERSION.c_str());
}

void test_parseHm330xMeasurement_undefinedBuf()
{

    try
    {
        parseHm330xMeasurement(NULL);
    }
    catch (const exception &e)
    {
        const char *message = e.what();
        TEST_ASSERT_EQUAL_STRING("BufferNulptrException: The buffer can't be a nullptr!", message);
    }
    catch (...)
    {
        // If we don't catch the assertion error we consider this test as failed
        TEST_ASSERT_TRUE(false);
    }
}

void test_parseHm330xMeasurement_invalidChecksum()
{
    uint8_t invalidData[30] = {0, 255, 0, 0, 0, 31, 0, 38, 0, 41, 0, 24, 0, 35, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0};

    try
    {
        parseHm330xMeasurement(invalidData);
    }
    catch (const exception &e)
    {
        TEST_ASSERT_EQUAL_STRING("ChecksumException: The checksum of the HM330X sensor buffer is not valid!", e.what());
    }
    catch (...)
    {
        exception_ptr ex = current_exception();
        // If we don't catch the assertion error we consider this test as failed
        TEST_ASSERT_TRUE(false);
    }
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

void test_convertHm330xMeasurementToMetrics()
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

    const char *expected = "pm_010_spm{sensor=\"HM330X\",version=\"v1.0\"} 0\npm_025_spm{sensor=\"HM330X\",version=\"v1.0\"} 0\npm_100_spm{sensor=\"HM330X\",version=\"v1.0\"} 0\npm_010_ae{sensor=\"HM330X\",version=\"v1.0\"} 0\npm_025_ae{sensor=\"HM330X\",version=\"v1.0\"} 0\npm_100_ae{sensor=\"HM330X\",version=\"v1.0\"} 0";
    string result = convertHm330xMeasurementToMetrics(measurement);
    TEST_ASSERT_EQUAL_STRING(expected, result.c_str());
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_ChecksumException);
    RUN_TEST(test_BufferNulptrException);
    RUN_TEST(test_isValidHm330xBufferChecksum);
    RUN_TEST(test_parseHm330xMeasurement_validData);
    RUN_TEST(test_parseHm330xMeasurement_undefinedBuf);
    RUN_TEST(test_parseHm330xMeasurement_invalidChecksum);
    RUN_TEST(test_convertHm330xMeasurementToJson);
    RUN_TEST(test_convertHm330xMeasurementToMetrics);

    UNITY_END(); // End Unity

    return 0;
}