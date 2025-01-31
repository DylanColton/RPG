#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform bool		texLoad;
uniform sampler2D	tex;
uniform vec3		sprCol;

void main() {
	//if (texLoad)
		FragColor = vec4(sprCol, 1.0) * texture(tex, UV);
	//else
	//	FragColor = vec4(sprCol, 1.0);
}
