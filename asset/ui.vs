#version 440
attribute vec2 position;
attribute vec2 texCoord;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

varying mediump vec2 fsTexCoord;

void main() {
	vec4 pos = vec4(position, 0, 1);
	pos = modelMatrix * pos;
	pos = projectionMatrix * pos;

	fsTexCoord = texCoord;
	gl_Position = pos;
}
