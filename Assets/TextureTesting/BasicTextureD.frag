//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

struct DiffuseLight
{
	vec3 position;
	vec3 color;
	float intensity;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material 
{
	vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float opacity;
    float shininess;
};

uniform Material material;

uniform DiffuseLight diffuseLight;
uniform vec3 cameraPos;

in vec4 vertColor;
in vec2 uvs;
in vec3 normals;
in vec3 fragPosition;


void main() 
{
	// ambient
    vec3 ambient = texture(material.diffuse, uvs).rgb * diffuseLight.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(diffuseLight.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * texture(material.diffuse, uvs).rgb) * diffuseLight.diffuse;

	//specular
    vec3 viewDir = normalize(cameraPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (material.specular * spec) * diffuseLight.specular; 
            
    vec3 result = ambient + diffuse + specular;

	outFragColor = vec4(result, 1.0);
}