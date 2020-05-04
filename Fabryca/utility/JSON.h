#pragma once

#include "Foundation.h"
#include "utility/Filepath.h"

#include <json/json.h>
#include <string>


namespace JSON {

using namespace Json;


Void read(const Filepath& filepath, Value& destination);
Value read(const Filepath& filepath);

}
