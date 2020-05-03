#include "NumericAttribute.h"

#include <algorithm>


NumericAttribute::NumericAttribute(Int maxValue):
    _minValue(0),
    _maxValue(maxValue),
    _value(maxValue)
{
    assert(_minValue <= _maxValue);
}

NumericAttribute::NumericAttribute(Int minValue, Int maxValue):
    _minValue(minValue),
    _maxValue(maxValue),
    _value(minValue)
{
    assert(minValue <= maxValue);
}

NumericAttribute::NumericAttribute(Int minValue, Int maxValue, Int value):
    _minValue(minValue),
    _maxValue(maxValue),
    _value(std::clamp(value, minValue, maxValue))
{
    assert(minValue <= maxValue);
}

Int NumericAttribute::minValue() const {
    return _minValue;
}

Int NumericAttribute::maxValue() const {
    return _maxValue;
}

Int NumericAttribute::value() const {
    return _value;
}

Int NumericAttribute::range() const {
    return _maxValue - _minValue;
}

Double NumericAttribute::percentage() const {
    return static_cast<Double>(_value - _minValue) / range();
}

Void NumericAttribute::setValue(Int value) {
    _value = std::clamp(value, _minValue, _maxValue);
}

Void NumericAttribute::setPercentage(Double percentage) {
    setValue(_minValue + range() * percentage);
}

Void NumericAttribute::increaseBy(Int amount) {
    assert(amount > 0 ? (_value <= IntMax - amount) : (_value >= IntMin - amount));

    setValue(_value + amount);
}

Void NumericAttribute::decreaseBy(Int amount) {
    assert(amount > 0 ? (_value >= IntMin + amount) : (_value <= IntMax + amount));

    setValue(_value - amount);
}
