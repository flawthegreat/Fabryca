#version 330 core

in vec2 uv;
in vec3 normalCameraspace;
in vec3 positionCameraspace;
in vec2 lightPositionCameraspace;

out vec4 fragmentColor;

uniform sampler2D uTextureSampler;
uniform float uViewDistance;
uniform vec3 uWorldColor;
uniform float uLightPower;

void main() {
    vec4 textureColor = texture(uTextureSampler, uv);

	vec3 materialDiffuseColor = textureColor.rgb;
	vec3 materialAmbientColor = vec3(0.8, 0.8, 0.8) * materialDiffuseColor;

    vec2 horizontalPositionCameraspace = vec2(positionCameraspace.x, positionCameraspace.z);
    float distanceFromLight = length(horizontalPositionCameraspace - lightPositionCameraspace);

    vec3 color = uLightPower * (materialDiffuseColor / (distanceFromLight / 32.0 + 1.0) + materialAmbientColor);

    float distanceFromCamera = length(vec2(positionCameraspace.x, positionCameraspace.z));
    float fogX = clamp(distanceFromCamera / uViewDistance, 0, 1);
    vec3 delta = (uWorldColor - color) * pow(fogX, 2) * (3 - 2 * fogX);

	fragmentColor = vec4(
        color + delta,
        textureColor.a
    );
}
