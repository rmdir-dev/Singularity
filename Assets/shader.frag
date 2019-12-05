#version 450

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 inUvs;
layout (location = 3) in vec3 normals;
layout (location = 4) in vec4 light;
layout (location = 5) in vec3 fragPos;
layout (location = 6) in vec3 cameraPos;

layout (location = 0) out vec4 outFragColor;

layout(set = 1, binding = 1) uniform sampler2D texSampler;
layout(set = 1, binding = 2) uniform sampler2D normSampler;
layout(set = 1, binding = 3) uniform sampler2D specSampler;

layout(push_constant) uniform Material 
{
	layout(offset = 16) vec4 ambient;
	layout(offset = 32) vec4 diffuse;
	layout(offset = 48) vec4 specular;
	layout(offset = 64) float opacity;
	layout(offset = 68) float shininess;
} material;

void main() 
{
	vec3 nrmls = texture(normSampler, inUvs).rgb;
	vec3 norm = normalize(nrmls * 2.0 - 1.0);
	vec3 lightDir = normalize(light.xyz - fragPos);
	vec3 lightColorAmbient = vec3(0.25);
	vec3 lightColorDiffuse = vec3(1.0);
	vec3 lightColorSpecular = vec3(0.75);

	//AMBIANT
	vec3 ambiant = material.ambient.xyz * lightColorAmbient;

	//DIFFUSE
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * texture(texSampler, inUvs).xyz) * lightColorDiffuse;

	//SPECULAR
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfwayDir = normalize(lightDir + cameraPos);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
	vec3 specular = (texture(specSampler, inUvs).rgb * spec) * lightColorSpecular;

	vec3 result = ambiant + diffuse * 1.75 + specular;

	outFragColor = vec4(result, 1.0);
	//outFragColor = texture(texSampler, inUvs);
}