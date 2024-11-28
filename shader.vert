#version 330 core
//layout komt overeen met de vertex attrib pointers en de VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

uniform float X;
uniform float Y;

out vec3 color;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(vec3(aPos.x + (Y*0.007) , aPos.y + (X*0.007) , aPos.z) * 0.3, 1.0);
    color = aColor;
    textureCoord = aTextureCoord;
}