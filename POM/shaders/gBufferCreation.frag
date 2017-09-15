#version 450

#ifdef USE_BINDLESS_TEXTURES
#extension GL_ARB_bindless_texture : require
#endif

in vec2 tex_coords;
in vec3 normals;
in vec3 binormals;
in vec3 tangents;
in vec4 position;
in vec3 tSpaceLookVector;

out vec4 fragData0;
out vec4 fragData1;
out vec4 fragData2;
out uint fragData3;

struct Material
{

#ifdef USE_BINDLESS_TEXTURES
	sampler2D BaseTexture;
	sampler2D NormTexture;
	sampler2D DepthTexture;
#endif
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float reflectance;
	float roughness;
};

#ifndef USE_BINDLESS_TEXTURES
uniform sampler2D textureUnit0;
uniform sampler2D textureUnit1;
uniform sampler2D textureUnit2;
#endif

layout(std140, binding=0)uniform Materials
{	
	Material material[3];
}materials;

uniform uint mat_ID;

void main( void )
{
	const float parallaxScale = 0.10;
	const float minLayers = 50.0;
	const float maxLayers = 100.0;
	
	vec3 tPos = normalize(tSpaceLookVector);
	
	float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), tPos)));
	float layerHeight = 1.0 / numLayers;
	float currentHeight = 0.0;	
	
	vec2 dtex = parallaxScale * tPos.xy / tPos.z / numLayers;	
	
	vec2 currentTexCoord = tex_coords;
	
	
#ifdef USE_BINDLESS_TEXTURES
	float texHeight = texture(materials.material[mat_ID].DepthTexture, currentTexCoord).r;
#else
	float texHeight = texture(textureUnit2, currentTexCoord).r;
#endif

	float prevTexHeight = texHeight;
	
	while(texHeight > currentHeight)
	{
		prevTexHeight = texHeight;
		// to the next layer
		currentHeight += layerHeight;
		// shift texture coordinates along vector V
		currentTexCoord -= dtex;
		// get new depth from heightmap	
#ifdef USE_BINDLESS_TEXTURES		
		texHeight = texture(materials.material[mat_ID].DepthTexture, currentTexCoord).r;
#else
		texHeight = texture(textureUnit2, currentTexCoord).r;
#endif
	}
	
	float nextH = texHeight - currentHeight;
	float prevH = prevTexHeight - currentHeight + layerHeight;
	
	float weight = nextH / (nextH - prevH);
	
	vec2 finalTexCoords = (currentTexCoord + dtex) * weight + currentTexCoord * (1.0 - weight);
	float parallaxHeight = currentHeight + prevH * weight + nextH * (1.0 - weight);	
	
#ifdef USE_BINDLESS_TEXTURES    
	vec4 color = texture(materials.material[mat_ID].BaseTexture, finalTexCoords);
	vec3 bumpNormal = normalize(((texture(materials.material[mat_ID].NormTexture, finalTexCoords).xyz) * 2.0) - 1.0);
#else
	vec4 color = texture(textureUnit0, finalTexCoords);
	vec3 bumpNormal = normalize(((texture(textureUnit1, finalTexCoords).xyz) * 2.0) - 1.0);
#endif
	
	vec3 texNormal;
	texNormal.x = dot(vec3(tangents.x, binormals.x, normals.x), bumpNormal);
	texNormal.y = dot(vec3(tangents.y, binormals.y, normals.y), bumpNormal);
	texNormal.z = dot(vec3(tangents.z, binormals.z, normals.z), bumpNormal); 
	 
	
    fragData0 = color;
    fragData1 = vec4(texNormal, 1.0);	
	fragData2 = vec4(position.xyz - (normals * parallaxHeight * parallaxScale), 1.0);
	fragData3 = mat_ID;
}