//Shader FRAGMENT
//Testing directional Light
#version 330 core

out vec4 outFragColor;

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutOff;
	float outerCutOff;
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

uniform SpotLight spotLight;
uniform vec3 cameraPos;

in vec4 vertColor;
in vec2 uvs;
in vec3 normals;
in vec3 fragPosition;

void main() 
{
    float dist = length(spotLight.position - fragPosition);

	// ambient
    vec3 ambient = texture(material.diffuse, uvs).rgb * spotLight.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(spotLight.position - fragPosition);
    float theta = dot(lightDir, normalize(-spotLight.direction));
    vec3 result;

    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * texture(material.diffuse, uvs).rgb) * spotLight.diffuse;

    //specular
    vec3 viewDir = normalize(cameraPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (texture(material.specular, uvs).rgb * spec) * spotLight.specular; 

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    result = ambient + diffuse + specular;
    

	outFragColor = vec4(result, 1.0);
}