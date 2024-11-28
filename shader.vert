#version 330 core
//layout komt overeen met de vertex attrib pointers en de VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec3 color;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = aColor;
    textureCoord = aTextureCoord;
}