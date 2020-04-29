//Shader FRAGMENT
//Testing directional Light
#version 330 core

out vec4 outFragColor;

struct DirectionalLight
{
	vec3 position;
    vec3 direction;
	vec3 color;
	float intensity;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool on;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutOff;
	float outerCutOff;
    float constant;
	float linear;
	float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool on;
};

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
    bool on;
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

uniform vec3 cameraPos;

in vec4 vertColor;
in vec2 uvs;
in vec3 normals;
in vec3 fragPosition;

#define POINT_LIGHT_NBR 4

uniform SpotLight spotLight;
uniform PointLight pointLight[POINT_LIGHT_NBR];
uniform DirectionalLight directionalLight;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewD);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewD);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewD);

void main() 
{
    vec3 norm = normalize(normals);
    vec3 viewDir = normalize(cameraPos - fragPosition);

    vec3 result = CalcDirectionalLight(directionalLight, norm, viewDir);

    for(int i = 0; i < POINT_LIGHT_NBR; i++)
    {
        result += CalcPointLight(pointLight[i], norm, fragPosition, viewDir);
    }

    result += CalcSpotLight(spotLight, norm, fragPosition, viewDir);

	outFragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewD)
{
    if(light.on == false)
    {
        return vec3(0.0);
    } else 
    {
         vec3 lightDir = normalize(-light.direction);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewD, reflectDir), 0.0), material.shininess);
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvs));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvs));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, uvs));
        return (ambient + diffuse + specular);
    }
   
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewD)
{
    if(light.on == false)
    {
        return vec3(0.0);
    } else
    {
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewD, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvs));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvs));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, uvs));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        return (ambient + diffuse + specular);
    }    
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewD)
{
    if(light.on == false)
    {
        return vec3(0.0);
    } else 
    {
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewD, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        // spotlight intensity
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvs));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvs));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, uvs));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return (ambient + diffuse + specular);
    }    
}