#version 440
attribute vec2 position;
attribute vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

varying mediump vec2 fsTexCoord;

void main() {
	vec4 pos = vec4(position, 0, 1);
	pos = modelMatrix * pos;
	pos = projectionMatrix * pos;

	fsTexCoord = texCoord;
	gl_Position = pos;
}
