#version 330 core

in vec2 uv;

out vec4 fragmentColor;

uniform sampler2D uTextureSampler;

void main() {
	fragmentColor = texture(uTextureSampler, uv);
}
