#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 aNormal;

uniform float u_horiOffset;
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_textureCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos.x + u_horiOffset, aPos.y, aPos.z, 1.0);
    v_textureCoords = vec2(texCoords.x, 1.0 - texCoords.y);
	v_Normal = mat3(transpose(inverse(u_Model))) * aNormal;
	v_FragPos = vec3(u_Model * vec4(aPos, 1.0f));
}