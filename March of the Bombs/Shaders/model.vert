#version 150

in vec3 vertexPosition;
in vec2 vertexTextureCoordinates;
in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 shadowMatrix;

out VertexOut
{
	vec4 position;
	vec2 textureCoordinates;
	vec3 normal;

	vec4 shadowCoordinates;
} vOut;

void main()
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

	vec4 eyeSpacePosition = viewMatrix * modelMatrix * vec4(vertexPosition, 1);

	vOut.position = eyeSpacePosition;
	vOut.textureCoordinates = vertexTextureCoordinates;
	vOut.normal = normalize(normalMatrix * vertexNormal);

	vOut.shadowCoordinates = shadowMatrix * modelMatrix * vec4(vertexPosition, 1);

	gl_Position = projectionMatrix * eyeSpacePosition;
}