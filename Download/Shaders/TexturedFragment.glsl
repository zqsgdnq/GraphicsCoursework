#version 150
uniform sampler2D diffuseTex;

in Vertex {
	vec2 texCoord;
        vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void){
	gl_FragColor = colour;
}