#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 ModelView;		// View * Model
uniform mat4 Projection;
uniform mat3 NormalMatrix;

in vec3 vertexPosition;			// Coordenadas locais do vértice
in vec3 vertexNormals;			// Normal do vértice
in vec2 texCoords;

out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;
out vec3 textureVector;

void main()
{ 
	// Posição do vértice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vertexPosition, 1.0)).xyz;

	// Transformar a normal do vértice.
	vNormalEyeSpace = normalize(NormalMatrix * vertexNormals);

	// Coordenada de textura para o CubeMap
	textureVector = vertexPosition;

	// Posição final do vértice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(vertexPosition, 1.0f);
}
