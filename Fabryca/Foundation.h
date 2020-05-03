#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <functional>
#include <string>


using Void = void;
using Bool = bool;

using Int8 = int8_t;
const Int8 Int8Min = INT8_MIN;
const Int8 Int8Max = INT8_MAX;

using UInt8 = uint8_t;
const UInt8 UInt8Min = 0;
const UInt8 UInt8Max = UINT8_MAX;

using Byte = UInt8;
const Byte ByteMin = UInt8Min;
const Byte ByteMax = UInt8Max;

using Int16 = int16_t;
const Int16 Int16Min = INT16_MIN;
const Int16 Int16Max = INT16_MAX;

using UInt16 = uint16_t;
const UInt16 UInt16Min = 0;
const UInt16 UInt16Max = UINT16_MAX;

using Int32 = int32_t;
const Int32 Int32Min = INT32_MIN;
const Int32 Int32Max = INT32_MAX;

using UInt32 = uint32_t;
const UInt32 UInt32Min = 0;
const UInt32 UInt32Max = UINT32_MAX;

using Int = Int32;
const Int IntMin = Int32Min;
const Int IntMax = Int32Max;

using UInt = UInt32;
const UInt UIntMin = UInt32Min;
const UInt UIntMax = UInt32Max;

using Int64 = int64_t;
const Int64 Int64Min = INT64_MIN;
const Int64 Int64Max = INT64_MAX;

using UInt64 = uint64_t;
const UInt64 UInt64Min = 0;
const UInt64 UInt64Max = UINT64_MAX;

using Char = char;
using Float = float;
using Double = double;


struct Size {
    Int width;
    Int height;
};


enum class Direction {
    right = 0,
    up = 1,
    left = 2,
    down = 3
};


inline std::string resourcesPath = "resources/";
