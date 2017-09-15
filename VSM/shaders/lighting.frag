#version 420

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float reflectance;
	float roughness;
};

layout(std140, binding=0)uniform Materials
{	
	Material material[3];
}materials;

in vec2 tex_coords;
out vec4 fragData0;

uniform sampler2D textureUnit0;
uniform sampler2D textureUnit1;
uniform sampler2D textureUnit2;
uniform usampler2D textureUnit3;
uniform sampler2D textureUnit4;

uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;
uniform vec4 light_position;

uniform mat4 transformMat;

// light bleed reduction constant
const float min_p = 0.6;


void main(void)
{
    vec4 baseColor = texture(textureUnit0, tex_coords);	
	vec3 normal = texture(textureUnit1, tex_coords).xyz;	
	vec4 position = texture(textureUnit2, tex_coords);	
	
	vec4 shadowPos = transformMat * position;
	
	shadowPos = shadowPos/shadowPos.w;
	shadowPos = (shadowPos + 1.0) * 0.5;
	
	//shadowPos.z = clamp(shadowPos.z, 0.0, 1.0);
	
	float bias = 0.005;	
	vec2 shadowMap = texture(textureUnit4, vec2(shadowPos.xy)).xy;
	
	float shade = 1.0;
	
	float fragDepth = length(light_position.xyz - position.xyz);
	
	if (fragDepth > shadowMap.x)
	{
		float variance = shadowMap.y - shadowMap.x * shadowMap.x;
		variance = max(variance, 0.00002);
		float mD = fragDepth - shadowMap.x;	
		shade = variance / (variance + mD * mD);
		
		// light bleed reduction
		//shade = smoothstep(min_p, 1.0, shade);
		shade = clamp((shade - min_p) / (1.0 - min_p), 0.0, 1.0);
	}		
	
	uint matID = texture(textureUnit3, tex_coords).x;
		
	vec3 lightDirection = normalize(light_position.xyz - position.xyz);	
	vec3 viewDirection = normalize(-position.xyz);
	vec3 halfDir = normalize(lightDirection + viewDirection);
	
	float nDotL = max(0.0, dot(lightDirection, normal));
	float vDotH = max(0.0, dot(viewDirection, halfDir));
	float nDotH = max(0.0, dot(normal, halfDir));
	float nDotV = max(0.0, dot(normal, viewDirection));
	float lDotH = max(0.0, dot(lightDirection, halfDir));	
	
	
	// FRESENEL TERM	
	float reflect = materials.material[matID].reflectance;
	float fresnel = pow(1.0f - vDotH, 5.0);	
    fresnel *= (1.0 - reflect);
    fresnel += reflect;	
	
	// GEOMETRIC TERM
	float geomAtten = min(1.0, min((2.0*nDotH*nDotV/vDotH), (2.0*nDotH*nDotL/vDotH)));	
	
	// ROUGHNESS TERM
	float rough = materials.material[matID].roughness;
	float den = nDotH*nDotH * rough*rough + (1-nDotH*nDotH);
	float slopeDist = (step(0.0, nDotH)*rough*rough) / (3.1412 * den * den);
	
	
	// COMBINE	
	float numerator   = (fresnel*geomAtten*slopeDist);
    float denomiator  = 4*nDotV*nDotL;
    float rs          = numerator/denomiator;	
	
	vec3 ambient = baseColor.xyz * light_ambient * materials.material[matID].ambient.xyz;
	vec3 diffuse = baseColor.xyz * light_diffuse * materials.material[matID].diffuse.xyz * nDotL * (shade * 0.7 + 0.3);
	vec3 specular = clamp(light_specular * materials.material[matID].specular.xyz * rs * nDotL, 0.0, 1.0) * shade;	
	
	vec3 color = max(ambient,clamp(diffuse + specular, 0.0, 1.0));
	fragData0 = vec4(color, 1.0);	

}