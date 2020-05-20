#include "NumberDisplayer.h"

using namespace Game;


NumberDisplayer::NumberDisplayer(Int value, Byte fieldLength, const Configuration& configuration):
    _anchor(*configuration.models().at("empty"))
{
    for (Byte i = 0; i < 10; ++i) {
        _digitMeshes.emplace_back(*configuration.meshes().at(std::to_string(static_cast<Int>(i))));
    }

    const Model zero = *configuration.models().at("0");
    for (Byte i = 0; i < fieldLength; ++i) {
        _displayedValue.emplace_back(zero);
        _displayedValue[i].setXPosition(5.0f / 16.0f * i);
    }

    for (Byte i = 0; i < fieldLength; ++i) {
        _anchor.addChild(_displayedValue[i]);
    }
}

const Model& NumberDisplayer::anchor() const {
    return _anchor;
}

Model& NumberDisplayer::anchor() {
    return _anchor;
}

Void NumberDisplayer::setValue(Int value) {
    Int currentDigitIndex = static_cast<Int>(_displayedValue.size()) - 1;
    while (currentDigitIndex >= 0) {
        Byte digit = value % 10;
        _displayedValue[currentDigitIndex].mesh = _digitMeshes[digit];

        --currentDigitIndex;
        value /= 10;
    }
}

Void NumberDisplayer::show() const {
    for (const Model& digit: _displayedValue) {
        digit.show();
    }
}

Void NumberDisplayer::hide() const {
    for (const Model& digit: _displayedValue) {
        digit.hide();
    }
}
