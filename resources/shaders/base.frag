#version 460

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D input_Tex;

void main()
{
    FragColor = texture(input_Tex, TexCoord);
}