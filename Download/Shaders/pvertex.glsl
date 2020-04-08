#version 330 core
layout (location = 0) in vec3 ppos;

layout (location = 2) in vec2 ptex; 
layout (location = 3) in vec3 pnormal; 

out vec3 pfragpos;
out vec2 ptexcoord;
out vec3 normal;

uniform mat4 projMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
void main()
{
    gl_Position =projMatrix*viewMatrix*modelMatrix*vec4(ppos,1.0);
    
    normal=mat3(transpose(inverse(modelMatrix))) * pnormal;
    pfragpos=vec3(modelMatrix*vec4(ppos,1.0));
    ptexcoord=ptex;    
}