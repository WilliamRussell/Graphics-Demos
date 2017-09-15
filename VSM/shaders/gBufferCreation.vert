#version 420

uniform mat4 modelViewMat;
uniform mat4 projectionMat;
uniform mat3 normalMat;

out vec2 tex_coords;
out vec3 normals;
out vec3 binormals;
out vec3 tangents;
out vec4 position;

in vec3 vertex;
in vec3 normal;
in vec3 binormal;
in vec3 tangent;
in vec2 texcoord;

void main( void )
{   
    gl_Position = projectionMat * modelViewMat * vec4(vertex, 1.0);
	
    normals = normalMat * normal;
	binormals = normalMat * binormal;
	tangents = normalMat * tangent;
	position = modelViewMat * vec4(vertex, 1.0);
    tex_coords = texcoord;
}