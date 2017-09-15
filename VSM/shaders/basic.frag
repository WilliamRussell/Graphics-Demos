#version 420

in vec2 tex_coords;
out vec4 fragData0;

//uniform sampler2DShadow textureUnit0;
uniform sampler2D textureUnit0;

void main( void )
{
    vec4 color = texture(textureUnit0, tex_coords);
	color = color / 40.0;	
    fragData0 = vec4(color.xyz, 1.0);
	
}