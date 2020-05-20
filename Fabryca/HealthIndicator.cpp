#include "HealthIndicator.h"

using namespace Game;


HealthIndicator::HealthIndicator(
    Int maxValue,
    const glm::vec3& position,
    const Configuration& configuration
):
    _frame(*configuration.models().at("healthIndicatorFrame")),
    _bar(*configuration.models().at("healthIndicatorBar"))
{
    const Float xScale = static_cast<Float>(maxValue) / 100.0f;
    _frame.setXScale(xScale);
    _bar.setXScale(xScale);
    _bar.setXZPosition(-xScale / 2.0f, 0.001f);
    _frame.addChild(_bar);

    _frame.setPosition(position);
}

Model& HealthIndicator::model() {
    return _frame;
}

Void HealthIndicator::show() {
    _frame.show();
    _bar.show();
}

Void HealthIndicator::hide() {
    _frame.hide();
    _bar.hide();
}

Void HealthIndicator::setValue(Int newValue) {
    _bar.setXScale(static_cast<Float>(newValue) / 100.0f);
}
