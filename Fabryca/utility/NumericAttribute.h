#pragma once

#include "Foundation.h"


class NumericAttribute {
public:
    NumericAttribute(Int maxValue);
    NumericAttribute(Int minValue, Int maxValue);
    NumericAttribute(Int minValue, Int maxValue, Int value);


    Int minValue() const;
    Int maxValue() const;
    Int value() const;

    Int range() const;
    Double percentage() const;

    Void setValue(Int value);

    Void setPercentage(Double percentage);

    Void increaseBy(Int amount);
    Void decreaseBy(Int amount);

private:
    Int _minValue;
    Int _maxValue;
    Int _value;
};
