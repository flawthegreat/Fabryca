#pragma once

#include "Foundation.h"

#include <json/json.h>
#include <string>


namespace JSON {

using namespace Json;


Void read(const std::string& filepath, Value& destination);
Value read(const std::string& filepath);

}
