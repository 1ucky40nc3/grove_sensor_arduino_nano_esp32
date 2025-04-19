#include <string>
#include "adapter.h"
#include "controller.h"
#include "serialize.h"

using namespace std;

JsonSerializableDataSenderAdapter::JsonSerializableDataSenderAdapter(JsonDataSenderController controller) : controller(controller) {}

void JsonSerializableDataSenderAdapter::send(IJsonSerializable data)
{
    controller.send(data.toJson());
}