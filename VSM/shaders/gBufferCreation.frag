#version 420

in vec2 tex_coords;
in vec3 normals;
in vec3 binormals;
in vec3 tangents;
in vec4 position;

out vec4 fragData0;
out vec4 fragData1;
out vec4 fragData2;
out uint fragData3;

uniform sampler2D textureUnit0;
uniform sampler2D textureUnit1;

uniform uint mat_ID;

void main( void )
{
    vec4 color = texture(textureUnit0, tex_coords);
	vec3 bumpNormal = normalize(((texture(textureUnit1, tex_coords).xyz) * 2.0) - 1.0);
	
	vec3 texNormal;
	texNormal.x = dot(vec3(tangents.x, binormals.x, normals.x), bumpNormal);
	texNormal.y = dot(vec3(tangents.y, binormals.y, normals.y), bumpNormal);
	texNormal.z = dot(vec3(tangents.z, binormals.z, normals.z), bumpNormal);  
	
    fragData0 = color;
    fragData1 = vec4(texNormal, 1.0);	
	fragData2 = position;
	fragData3 = mat_ID;
}