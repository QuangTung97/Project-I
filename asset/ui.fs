#version 440
varying mediump vec2 fsTexCoord;
uniform sampler2D image;

void main() {
	// gl_FragColor = texture2D(image, fsTexCoord);
	gl_FragColor = vec4(0.4, 0.4, 1, 1);
}
