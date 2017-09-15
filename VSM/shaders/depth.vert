#version 420
uniform mat4 modelViewMat;
uniform mat4 projectionMat;

in vec3 vertex;
out vec4 position;

void main(void)
{
	position = modelViewMat * vec4(vertex, 1.0);
	gl_Position = projectionMat * modelViewMat * vec4(vertex, 1.0);
}