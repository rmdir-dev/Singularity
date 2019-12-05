#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 uvs;
layout (location = 3) in vec3 inNormals;


layout (binding = 0) uniform Uniforms 
{
	mat4 projectionMatrix;
	mat4 modelMatrix;
	mat4 viewMatrix;
} ubo;

layout(push_constant) uniform lightPos 
{
	vec4 ambient;
} lPos;

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec2 outUvs;
layout (location = 3) out vec3 normals;
layout (location = 4) out vec4 light;
layout (location = 5) out vec3 fragPos;
layout (location = 6) out vec3 cameraPos;


out gl_PerVertex 
{
    vec4 gl_Position;   
};


void main() 
{
	outUvs = uvs;
	outColor = inColor;
	light = lPos.ambient;
	fragPos = vec3(ubo.modelMatrix * vec4(inPos, 1.0));
	// GET CAMERA POSITION
	mat4 camera = inverse(ubo.viewMatrix);
	cameraPos = vec3(camera[3][0], camera[3][1], camera[3][2]);
	gl_Position = ubo.projectionMatrix * ubo.viewMatrix * ubo.modelMatrix * vec4(inPos.xyz, 1.0);
	normals = mat3(transpose(inverse(ubo.modelMatrix))) * inNormals;
}
