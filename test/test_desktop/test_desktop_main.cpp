using namespace std;
#include <unity.h>
#include "measure.h"
#include "service.h"
#include "controller.h"
#include "adapter.h"
#include "customQueue.h"
#include "sensor.h"
#include "sensor.cpp"

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

void test_json_data_sender_service()
{
    JsonDataSenderService service;
    service.send("test");
}

void test_json_data_sender_controller()
{
    JsonDataSenderService service;
    JsonDataSenderController controller(service);

    controller.send("test");
}

void test_json_data_sender_adapter()
{
    JsonDataSenderService service;
    JsonDataSenderController controller(service);
    JsonSerializableDataSenderAdapter adapter(controller);

    HM330XData data;
    data.pm_010_spm = 0;
    data.pm_025_spm = 0;
    data.pm_100_spm = 0;
    data.pm_010_ae = 0;
    data.pm_025_ae = 0;
    data.pm_100_ae = 0;
    Description desc;
    desc.sensor = "sensor";
    desc.version = "version";
    Measurement<HM330XData> measurement;
    measurement.data = data;
    measurement.desc = desc;
    JsonSerializableHM330XMeasurement serializable(measurement);
    adapter.send(serializable);
}

void test_sequenced_queue()
{
    SequencedQueue<string> sequencedQueue;
    TEST_ASSERT_TRUE(sequencedQueue.isEmpty());
    sequencedQueue.add("item");
    TEST_ASSERT_FALSE(sequencedQueue.isEmpty());
    const string item = sequencedQueue.pop();
    TEST_ASSERT_TRUE(sequencedQueue.isEmpty());
    TEST_ASSERT_EQUAL_STRING("item", item.c_str());
}

void test_convert_hm330x_error_code()
{
    TEST_ASSERT_TRUE(convertHM330XErrorCode(NO_ERROR) == NO_ERR);
    TEST_ASSERT_TRUE(convertHM330XErrorCode(ERROR_COMM) == ERR_CONN);
    TEST_ASSERT_TRUE(convertHM330XErrorCode(ERROR_OTHERS) == ERR_OTHER);
}

class HM330XSensorTest : public HM330XSensor
{
public:
    err_sensor_t read_sensor_value(uint8_t *data)
    {
        // We expect the buffer to have a length of 30
        // as in the private HM330XSensorReader buf property
        for (int i = 0; i < 30; ++i)
        {
            data[i] = i;
        }
        return NO_ERR;
    }
};

void test_hm330x_sensor_reader_read_parse_get()
{

    HM330XSensorTest sensor;
    HM330XSensorReader reader(sensor);
    const err_sensor_t readError = reader.read_measurement();
    TEST_ASSERT_TRUE(readError == NO_ERR);
    const err_sensor_t parseError = reader.parse_measurement();
    TEST_ASSERT_TRUE(parseError == NO_ERR);
    const Measurement<HM330XData> data = reader.get_measurement();
    const Measurement<HM330XData> expect = {{"HM330X", "v1"},
                                            {0, 1, 2, 3, 4, 5, 6}};
    TEST_ASSERT_TRUE(expect.desc.sensor == data.desc.sensor);
    TEST_ASSERT_TRUE(expect.desc.version == data.desc.version);
    TEST_ASSERT_TRUE(expect.data.pm_010_spm == data.data.pm_010_spm);
    TEST_ASSERT_TRUE(expect.data.pm_025_spm == data.data.pm_025_spm);
    TEST_ASSERT_TRUE(expect.data.pm_100_spm == data.data.pm_100_spm);
    TEST_ASSERT_TRUE(expect.data.pm_010_ae == data.data.pm_010_ae);
    TEST_ASSERT_TRUE(expect.data.pm_025_ae == data.data.pm_025_ae);
    TEST_ASSERT_TRUE(expect.data.pm_100_ae == data.data.pm_100_ae);
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_hm330x_serializable_measurement);
    RUN_TEST(test_json_data_sender_service);
    RUN_TEST(test_json_data_sender_controller);
    RUN_TEST(test_json_data_sender_adapter);
    RUN_TEST(test_sequenced_queue);
    RUN_TEST(test_convert_hm330x_error_code);
    RUN_TEST(test_hm330x_sensor_reader_read_parse_get);

    UNITY_END(); // End Unity

    return 0;
}