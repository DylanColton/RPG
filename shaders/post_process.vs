#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 UV;

uniform bool	chaos;
uniform bool	confuse;
uniform bool	shake;
uniform float	time;

void main() {
	gl_Position	= vec4(vertex.xy, 0.0f, 1.0f);
	vec2 tex	= vertex.zw;

	if (chaos) {
		float str	= 0.3;
		vec2 pos	= vec2 (tex.x + sin(time) * str, tex.y + cos(time) * str);
		UV			= pos;
	} else if (confuse) {
		UV			= vec2(1.0 - tex.x, 1.0 - tex.y);
	} else {
		UV			= tex;
	}

	if (shake) {
		float str		 = 0.01;
		gl_Position.x	+= cos(time * 10) * str;
		gl_Position.y	+= cos(time * 15) * str;
	}
}
