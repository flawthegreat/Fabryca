#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 normals;

out vec2 uv;
out vec3 normalCameraspace;
out vec3 positionCameraspace;
out vec2 lightPositionCameraspace;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform vec3 uLightPosition;

void main() {
    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1);
    uv = textureCoordinates;
    normalCameraspace = (uViewMatrix * uModelMatrix * vec4(normals, 0)).xyz;
    positionCameraspace = (uViewMatrix * uModelMatrix * vec4(position, 1)).xyz;
    lightPositionCameraspace = (uViewMatrix * vec4(uLightPosition, 1)).xz;
}
