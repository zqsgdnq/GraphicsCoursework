#version 330 core

uniform mat4 viewProjMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;



out Vertex {
	vec4 colour;
} OUT;

void main(void)	{
	gl_Position	  = viewProjMatrix * vec4(position, 1.0);
	OUT.colour    = vec4(colour,1);
}