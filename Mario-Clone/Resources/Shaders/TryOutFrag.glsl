#version 330 core
in vec2 TexCoords;
in float texIndex;
in vec3 Color;
out vec4 color;

uniform sampler2D u_Texture[2];
uniform vec3 u_SpriteColor;

void main()
{    
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Texture, TexCoords).r);
	vec4 sampled = texture(u_Texture[int(texIndex)], TexCoords);
	//sampled += sampled1;
    color = vec4(Color, 1.0) * sampled;
}  