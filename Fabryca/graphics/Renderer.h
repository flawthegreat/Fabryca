#pragma once

#include "Foundation.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Animation.h"

#include <glm/glm.hpp>
#include <vector>
#include <deque>


class Renderer {
public:
    static Renderer& shared();


    const std::deque<Model*>& drawQueue() const;
    const std::vector<Animation>& animationQueue() const;
    const glm::mat4& projectionMatrix() const;
    const glm::mat4& viewMatrix() const;
    const glm::vec3& lightPosition() const;
    const glm::vec3& lightDirection() const;
    Float lightPower() const;
    Float viewDistance() const;
    const Camera& camera() const;
    glm::vec3 clearColor() const;

    Void clear() const;
    Void draw() const;

    Void draw(const Model& model) const;
    Void drawModels() const;
    Void appendModelToDrawQueue(Model* model);
    Void removeModelFromDrawQueue(Model* model);

    Void processAnimations();
    Void appendAnimationToQueue(const Animation& animation);
    Void removeAnimationFromQueue(const Animation& animation);
    Void removeAnimationFromQueue(Animation::Type type, const SceneObject& object);

    Void updateProjectionMatrix();
    Void updateProjectionMatrix(Int windowWidth, Int windowHeight);
    Void updateViewMatrix();

    Void setLightPosition(const glm::vec3& position);
    Void setLightPosition(Float x, Float y, Float z);
    Void setLightDirection(const glm::vec3& direction);
    Void setLightDirection(Float x, Float y, Float z);
    Void setLightPower(Float power);

    Void setViewDistance(Float viewDistance);

    Void setCameraFieldOfView(Float fieldOfView);
    Void setCameraPosition(const glm::vec3& position);
    Void setCameraPosition(Float x, Float y, Float z);
    Void setCameraFocusPoint(const glm::vec3& focusPoint);
    Void setCameraFocusPoint(Float x, Float y, Float z);

    Void moveCameraTo(glm::vec3 position, Double duration);
    Void moveCameraTo(Float x, Float y, Float z, Double duration);

    Void setClearColor(const glm::vec3& color);
    Void setClearColor(Float r, Float g, Float b);

private:
    static Renderer* _shared;

    std::deque<Model*> _drawQueue;
    std::vector<Animation> _animationQueue;

    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;

    glm::vec3 _lightPosition;
    glm::vec3 _lightDirection;
    Float _lightPower;
    Float _viewDistance;
    Camera _camera;


    Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    ~Renderer();


    Renderer& operator= (const Renderer&) = delete;
    Renderer& operator= (Renderer&&) = delete;

    static Void _windowSizeDidChange(Int width, Int height);
};
