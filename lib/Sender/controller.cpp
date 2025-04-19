#include <string>
#include "controller.h"
#include "service.h"

using namespace std;

JsonDataSenderController::JsonDataSenderController(JsonDataSenderService service) : service(service) {}

void JsonDataSenderController::send(string data)
{
    service.send(data);
}