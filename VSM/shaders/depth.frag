#version 420
out vec2 fragData0;

in vec4 position;

void main(void)
{
	float distance = length(position.xyz);
	fragData0 = vec2(distance, distance * distance);
}