#version 430 core

uniform float light_rad;
uniform vec2 light_pos;

uniform sampler2D textures[32];

in DATA
{
	vec4 position;
	vec4 color;
	vec2 UV;
	float texID;
} fs_in;

layout(location = 0) out vec4 color;

void main(void) {
	float light = light_rad / length(fs_in.position.xy - light_pos);
	//light = 1;
	vec4 texColor = vec4(1, 1, 1, 1);

	if (fs_in.texID < 0) texColor = vec4(1, 1, 1, 1);
	else
	{
		int tid = int(fs_in.texID + 0.5);
		switch (tid)
		{
			case 0: texColor = texture(textures[0], fs_in.UV); break;
			case 1: texColor = texture(textures[1], fs_in.UV); break;
			case 2: texColor = texture(textures[2], fs_in.UV); break;
			case 3: texColor = texture(textures[3], fs_in.UV); break;
			case 4: texColor = texture(textures[4], fs_in.UV); break;
			case 5: texColor = texture(textures[5], fs_in.UV); break;
			case 6: texColor = texture(textures[6], fs_in.UV); break;
			case 7: texColor = texture(textures[7], fs_in.UV); break;
			case 8: texColor = texture(textures[8], fs_in.UV); break;
			case 9: texColor = texture(textures[9], fs_in.UV); break;
			case 10: texColor = texture(textures[10], fs_in.UV); break;
			case 11: texColor = texture(textures[11], fs_in.UV); break;
			case 12: texColor = texture(textures[12], fs_in.UV); break;
			case 13: texColor = texture(textures[13], fs_in.UV); break;
			case 14: texColor = texture(textures[14], fs_in.UV); break;
			case 15: texColor = texture(textures[15], fs_in.UV); break;
			case 16: texColor = texture(textures[16], fs_in.UV); break;
			case 17: texColor = texture(textures[17], fs_in.UV); break;
			case 18: texColor = texture(textures[18], fs_in.UV); break;
			case 19: texColor = texture(textures[19], fs_in.UV); break;
			case 20: texColor = texture(textures[20], fs_in.UV); break;
			case 21: texColor = texture(textures[21], fs_in.UV); break;
			case 22: texColor = texture(textures[22], fs_in.UV); break;
			case 23: texColor = texture(textures[23], fs_in.UV); break;
			case 24: texColor = texture(textures[24], fs_in.UV); break;
			case 25: texColor = texture(textures[25], fs_in.UV); break;
			case 26: texColor = texture(textures[26], fs_in.UV); break;
			case 27: texColor = texture(textures[27], fs_in.UV); break;
			case 28: texColor = texture(textures[28], fs_in.UV); break;
			case 29: texColor = texture(textures[29], fs_in.UV); break;
			case 30: texColor = texture(textures[30], fs_in.UV); break;
			case 31: texColor = texture(textures[31], fs_in.UV); break;
		}
	}
	texColor = texColor * fs_in.color;
	color = vec4(texColor.r * light, texColor.g * light, texColor.b * light, texColor.a);
}