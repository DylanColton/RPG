#version 330 core
out vec4 FragColor;
in vec2 UV;
in vec4 partCol;

uniform sampler2D sprite;

void main() {
	FragColor =  (texture(sprite, UV) * partCol);
}
