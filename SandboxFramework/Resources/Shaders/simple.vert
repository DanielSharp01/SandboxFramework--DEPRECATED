#version 430 core
layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec2 in_UV;
layout (location = 3) in float in_TexID;

uniform mat4 proj;

out DATA
{
	vec4 position;
	vec4 color;
	vec2 UV;
	float texID;
} vs_out;

void main(void) {
	vs_out.position = in_Position;
	vs_out.color = in_Color;
	vs_out.UV = in_UV;
	vs_out.texID = in_TexID;

    gl_Position = proj * in_Position;
}