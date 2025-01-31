#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 UV;

uniform mat4 model;
uniform mat4 proj;

void main() {
	UV = vertex.zw;
	gl_Position	= proj * model * vec4(vertex.xy, 0.0, 1.0);
}
