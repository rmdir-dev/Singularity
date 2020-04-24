//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

struct DiffuseLight
{
	vec3 position;
	float intensity;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material 
{
	vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
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
in mat3 tbn;


void main() 
{
	vec3 lightPosition = tbn * diffuseLight.position;
	vec3 viewPosition = tbn * cameraPos;
	vec3 fragPos = tbn * fragPosition;

	vec3 color = texture(material.diffuse, uvs).rgb;

	// ambient
    vec3 ambient = color * diffuseLight.ambient;//diffuseLight.ambient;
  	
	//Normal
	vec3 normal = normalize(texture(material.normal, uvs).rgb); 
    vec3 norm = normalize(tbn * (normal * 2.0 - 1.0));

    // diffuse
    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = (diff * color);

	//specular
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfWayDir = normalize(lightDir + viewDir); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = (vec3(texture(material.specular, uvs)) * spec); 
            
    vec3 result = ambient + diffuse + specular;

	outFragColor = vec4(result, 1.0);
}