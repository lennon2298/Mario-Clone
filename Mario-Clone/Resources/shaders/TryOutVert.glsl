#version 330 core
layout (location = 0) in vec2 v_Vertex; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 v_TexCoords;
layout (location = 2) in vec4 v_Offset;

out vec2 TexCoords;
out float texIndex;
out vec3 Color;
uniform mat4 u_Projection;
uniform mat4 u_Model;

void main()
{
    vec4 pos = u_Model * vec4(v_Vertex, 0.0, 1.0);
    pos.xy += v_Offset.xy;
		
    gl_Position = u_Projection * pos;
    TexCoords = v_TexCoords;
	texIndex = v_Offset.z;
	Color = vec3(1.0f, 1.0f, 1.0f);
	if(v_Offset.w == 2)
		Color = vec3(0.2f, 0.6f, 1.0f);
	else if(v_Offset.w == 3)
		Color = vec3(0.0f, 0.7f, 0.0f);
	else if(v_Offset.w == 4)
		Color = vec3(0.8f, 0.8f, 0.4f);
	else if(v_Offset.w == 5)
		Color = vec3(1.0f, 0.5f, 0.0f);
	else if(v_Offset.w == 0)
		Color = vec3(0.8f, 0.8f, 0.7f);
} 