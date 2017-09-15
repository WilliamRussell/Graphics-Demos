#version 420

uniform mat4 modelViewMat;
uniform mat4 projectionMat;
uniform mat3 textureMat;

in vec3 vertex;
in vec2 texcoord;

out vec2 tex_coords;

void main( void )
{   
    gl_Position = projectionMat * modelViewMat * vec4(vertex, 1.0);	
   
    tex_coords = vec2((textureMat * vec3(texcoord, 1.0)).xy);
}