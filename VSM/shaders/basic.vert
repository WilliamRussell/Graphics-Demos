#version 420

uniform mat4 modelViewMat;
uniform mat4 projectionMat;

out vec2 tex_coords;

in vec3 vertex;
in vec2 texcoord;

void main( void )
{   
    gl_Position = projectionMat * modelViewMat * vec4(vertex, 1.0);
    tex_coords = texcoord;
}