#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, textureCoord), texture(texture2, vec2(-textureCoord.x, textureCoord.y)*2), 0.4) * vec4(color, 1.0);
}