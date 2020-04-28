//Shader FRAGMENT
//Testing directional Light
#version 330 core

out vec4 outFragColor;

struct PointLight
{
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material 
{
	vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float opacity;
    float shininess;
};

uniform Material material;

uniform PointLight pointLight;
uniform vec3 cameraPos;

in vec4 vertColor;
in vec2 uvs;
in vec3 normals;
in vec3 fragPosition;

void main() 
{
    float dist = length(pointLight.position - fragPosition);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * (dist * dist));

	// ambient
    vec3 ambient = texture(material.diffuse, uvs).rgb * pointLight.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(pointLight.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * texture(material.diffuse, uvs).rgb) * pointLight.diffuse;

	//specular
    vec3 viewDir = normalize(cameraPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (texture(material.specular, uvs).rgb * spec) * pointLight.specular; 

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 result = ambient + diffuse + specular;

	outFragColor = vec4(result, 1.0);
}