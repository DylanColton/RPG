#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 UV;
out vec4 partCol;

uniform mat4 proj;
uniform vec2 offset;
uniform vec4 color;

void main() {
	float scale = 10.0f;
	UV = vertex.zw;
	partCol = color;
	gl_Position = proj * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}
