using namespace std;
#include <unity.h>
#include "measure.h"
#include "service.h"
#include "controller.h"
#include "adapter.h"

void test_hm330x_measurement()
{
    HM330XData data;
    data.pm_010_spm = 0;
    data.pm_025_spm = 0;
    data.pm_100_spm = 0;
    data.pm_010_ae = 0;
    data.pm_025_ae = 0;
    data.pm_100_ae = 0;
    HM33XMeasurement measurement(data);
    const char *expected = "{\"sensor\":\"HM33X\",\"version\":\"v1.0\",\"data\":{\"pm_010_spm\":0,\"pm_025_spm\":0,\"pm_100_spm\":0,\"pm_010_ae\":0,\"pm_025_ae\":0,\"pm_100_ae\":0}}";
    TEST_ASSERT_EQUAL_STRING(expected, measurement.toJson().c_str());
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
    HM33XMeasurement measurement(data);
    adapter.send(measurement);
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_hm330x_measurement);
    RUN_TEST(test_json_data_sender_service);

    UNITY_END(); // End Unity

    return 0;
}