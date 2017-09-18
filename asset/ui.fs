#version 440
varying mediump vec2 fsTexCoord;
uniform sampler2D image;

void main() {
	gl_FragColor = texture2D(image, fsTexCoord);
}
