#include <string>
#include "serialize.h"

using namespace std;

string IJsonSerializable::toJson()
{
    // This should ideally never be called directly for the interface
    return "";
}