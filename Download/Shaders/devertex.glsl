#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 textureMatrix;
uniform float time;
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour; 
layout (location = 2) in vec2 texCoord; 
layout (location = 3) in vec3 normal; 


out Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} OUT;

void main(void) {
        vec3 deposition=vec3(position.x,position.y*time,position.z);
	OUT.colour = colour;
	OUT.texCoord = (textureMatrix * vec4(texCoord, 0.0, 1.0)).xy;
	mat3 normalMatrix =  transpose(inverse(mat3(modelMatrix)));
	OUT.normal = normalize(normalMatrix * normalize(normal));
	OUT.worldPos =  (modelMatrix * vec4(deposition, 1)).xyz ;

	gl_Position = (projMatrix * viewMatrix * modelMatrix) * vec4(deposition , 1.0);
}