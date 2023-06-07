#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;


in vec3 vertexPosition;			// Coordenadas locais do v�rtice
in vec3 vertexNormals;			// Normal do v�rtice
in vec2 texCoords;

out vec2 uv;
out vec3 normal;
out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;

void main()
{ 
	
	normal = vertexNormals;
	uv = texCoords;

	// Posi��o do v�rtice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vertexPosition, 1.0)).xyz;

	// Transformar a normal do v�rtice.
	vNormalEyeSpace = normalize(NormalMatrix * vertexNormals);

	// Coordenada de textura para o CubeMap
	//textureVector = vertexPosition;

	// Posi��o final do v�rtice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(vertexPosition, 1.0f);
}