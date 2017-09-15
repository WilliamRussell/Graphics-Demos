#version 420

in vec2 tex_coords;

out vec4 fragData0;
uniform sampler2D textureUnit0;


void main( void )
{
    vec4 color = texture(textureUnit0, tex_coords);	
	//vec4 color = vec4(1.0,0.0,0.0,1.0);
	//color.w = (color.x + color.y + color.z)	/ 3.0;
    fragData0 = color;   
}