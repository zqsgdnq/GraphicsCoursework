#version 330 core
out vec4 FragColor;


struct Material {
    sampler2D pydiffuse;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 pfragpos;
in vec2 ptexcoord;
in vec3 normal;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
 vec3 ambient=light.ambient*texture(material.pydiffuse,ptexcoord).rgb;
 
 vec3 norm=normalize(normal);
 vec3 lightDir = normalize(light.position - pfragpos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.pydiffuse, ptexcoord).rgb; 

vec3 viewDir = normalize(viewPos - pfragpos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.pydiffuse,  ptexcoord).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result ,1.0);
}