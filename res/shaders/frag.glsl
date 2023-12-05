#version 460

in vec3 TexCoord;
out vec4 FragColor;

uniform sampler2DArray textureArray;

void main()
{
    FragColor = texture(textureArray, TexCoord);
}