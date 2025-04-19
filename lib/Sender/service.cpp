#include <string>
#include <iostream>
#include "service.h"

using namespace std;

void JsonDataSenderService::send(string data)
{
    cout << "Would send data: " + data;
}