#version 420

in vec2 tex_coords;
out vec2 fragData0;

uniform sampler2D textureUnit0;

void main( void )
{
    vec2 sum = vec2(0.0, 0.0);
	sum += textureOffset(textureUnit0, tex_coords, ivec2(-4, 0)).xy * 0.0162162162;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(-3, 0)).xy * 0.0540540541;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(-2, 0)).xy * 0.1216216216;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(-1, 0)).xy * 0.1945945946;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(+0, 0)).xy * 0.2270270270;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(+1, 0)).xy * 0.1945945946;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(+2, 0)).xy * 0.1216216216;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(+3, 0)).xy * 0.0540540541;
	sum += textureOffset(textureUnit0, tex_coords, ivec2(+4, 0)).xy * 0.0162162162;
	
	/*sum += texture(textureUnit0, tex_coords + vec2(-0.04, 0)).xy * 0.0162162162;
	sum += texture(textureUnit0, tex_coords + vec2(-0.03, 0)).xy * 0.0540540541;
	sum += texture(textureUnit0, tex_coords + vec2(-0.02, 0)).xy * 0.1216216216;
	sum += texture(textureUnit0, tex_coords + vec2(-0.01, 0)).xy * 0.1945945946;
	sum += texture(textureUnit0, tex_coords + vec2(+0, 0)).xy * 0.2270270270;
	sum += texture(textureUnit0, tex_coords + vec2(+0.01, 0)).xy * 0.1945945946;
	sum += texture(textureUnit0, tex_coords + vec2(+0.02, 0)).xy * 0.1216216216;
	sum += texture(textureUnit0, tex_coords + vec2(+0.03, 0)).xy * 0.0540540541;
	sum += texture(textureUnit0, tex_coords + vec2(+0.04, 0)).xy * 0.0162162162;*/
	
	/*sum = textureOffset(textureUnit0, tex_coords, ivec2(-1, -1)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+0, -1)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+1, -1)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(-1, +0)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+0, +0)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+1, +0)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(-1, +1)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+0, +1)).xy;
	sum = textureOffset(textureUnit0, tex_coords, ivec2(+1, +1)).xy;*/
	
	//sum = sum / 9.0;
	
    fragData0 = sum;
}