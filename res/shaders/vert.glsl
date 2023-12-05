#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}