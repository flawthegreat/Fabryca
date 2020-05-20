#pragma once

#include "Foundation.h"
#include "graphics/Graphics.h"
#include "Configuration.h"

#include <vector>


namespace Game {

class HealthIndicator {
public:
    explicit HealthIndicator(
        Int maxValue,
        const glm::vec3& position,
        const Configuration& configuration
    );


    Model& model();

    Void show();
    Void hide();

    Void setValue(Int newValue);

private:
    Model _frame;
    Model _bar;
};

}
