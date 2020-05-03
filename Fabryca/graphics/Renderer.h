#pragma once

#include "Foundation.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Animation.h"

#include <glm/glm.hpp>
#include <vector>


class Renderer final {
public:
    static Renderer& shared();

    const std::vector<Animation>& animationQueue() const;
    const glm::mat4& projectionMatrix() const;
    const glm::mat4& viewMatrix() const;
    const glm::vec3& lightPosition() const;
    const glm::vec3& lightDirection() const;
    Float lightPower() const;
    Float viewDistance() const;
    const Camera& camera() const;
    glm::vec3 clearColor() const;
    const glm::vec4& horizontalViewBounds() const;

    Void clear() const;
    Void draw() const;

    Void addModelToDrawQueue(const Model& model, Int priority = 1);
    Void removeModelFromDrawQueue(const Model& model);

    Void processAnimations();
    Void addAnimationToQueue(
        Animation::Type type,
        SceneObject& object,
        const glm::vec3& newValue,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void addAnimationToQueue(const Animation& animation);
    Void removeAnimationFromQueue(const Animation& animation, Bool withCallback = true);

    Void updateProjectionMatrix();
    Void updateProjectionMatrix(Int windowWidth, Int windowHeight);
    Void updateViewMatrix();

    Void setLightPosition(const glm::vec3& position);
    Void setLightPosition(Float x, Float y, Float z);
    Void setLightDirection(const glm::vec3& direction);
    Void setLightDirection(Float x, Float y, Float z);
    Void setLightPower(Float power);

    Void setViewDistance(Float viewDistance);

    Void setHorizontalViewBounds(const glm::vec4& bounds);
    Void setHorizontalViewBounds(Float minX, Float maxX, Float minY, Float maxY);

    Void setClearColor(const glm::vec3& color);
    Void setClearColor(Float r, Float g, Float b);

    Void setCameraFieldOfView(Float fieldOfView);
    Void setCameraPosition(const glm::vec3& position);
    Void setCameraPosition(Float x, Float y, Float z);
    Void setCameraFocusPoint(const glm::vec3& focusPoint);
    Void setCameraFocusPoint(Float x, Float y, Float z);

    Void moveCameraTo(
        const glm::vec3& position,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveCameraTo(
        Float x,
        Float y,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );

private:
    static Renderer* _shared;

    std::vector<const Model*> _opaqueDrawQueue;
    std::vector<std::pair<Int, const Model*>> _transparentDrawQueue;
    std::vector<Animation> _animationQueue;

    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;

    glm::vec3 _lightPosition;
    glm::vec3 _lightDirection;
    Float _lightPower;
    Float _viewDistance;
    Camera _camera;

    glm::vec4 _horizontalViewBounds;


    Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator= (const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator= (Renderer&&) = delete;
    ~Renderer();


    Void _drawModel(const Model& model) const;

    static Void _windowSizeDidChange(Int width, Int height);
};
