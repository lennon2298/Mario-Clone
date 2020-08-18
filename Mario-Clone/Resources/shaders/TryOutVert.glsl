#version 330 core
layout (location = 0) in vec2 v_Vertex; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 v_TexCoords;
layout (location = 2) in vec4 v_Offset;

out vec2 TexCoords;
out float texIndex;
out vec3 Color;
uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    vec4 pos = u_View * u_Model * vec4(v_Vertex, 0.0, 1.0);
    pos.xy += v_Offset.xy;
		
    gl_Position = u_Projection * pos;
    TexCoords = v_TexCoords;
	texIndex = v_Offset.z;
	Color = vec3(1.0f, 1.0f, 1.0f);
	Color = vec3(0.8f, 0.8f, 0.7f);
} 