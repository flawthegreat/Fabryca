#version 330 core

in vec2 uv;
in vec3 normalCameraspace;
in vec3 positionWorldspace;
in vec3 positionCameraspace;
in vec2 lightPositionCameraspace;

out vec4 fragmentColor;

uniform sampler2D uTextureSampler;
uniform float uViewDistance;
uniform vec3 uWorldColor;
uniform vec3 uLightDirection;
uniform float uLightPower;
uniform vec4 uHorizontalViewBounds = vec4(-10000.0, 10000.0, -10000.0, 10000.0);

void main() {
    if (
        positionWorldspace.x < uHorizontalViewBounds.x ||
        positionWorldspace.x > uHorizontalViewBounds.y ||
        positionWorldspace.z < uHorizontalViewBounds.z ||
        positionWorldspace.z > uHorizontalViewBounds.w
    ) {
        discard;
    }

    vec4 textureColor = texture(uTextureSampler, uv);

	vec3 materialDiffuseColor = textureColor.rgb;
	vec3 materialAmbientColor = vec3(0.8, 0.8, 0.8) * materialDiffuseColor;
    
	float cosTheta = clamp(dot(normalize(normalCameraspace), normalize(-uLightDirection)), 0, 1);

    vec2 horizontalPositionCameraspace = vec2(positionCameraspace.x, positionCameraspace.z);
    float distanceFromLight = length(horizontalPositionCameraspace - lightPositionCameraspace);

    vec3 color = uLightPower * (materialDiffuseColor * cosTheta / (distanceFromLight / 32 + 1) + materialAmbientColor);

    float distanceFromCamera = length(vec2(positionCameraspace.x, positionCameraspace.z));
    float fogX = clamp(distanceFromCamera / uViewDistance, 0, 1);
    vec3 delta = (uWorldColor - color) * pow(fogX, 2) * (3 - 2 * fogX);

	fragmentColor = vec4(
        color + delta,
        textureColor.a
    );
}
