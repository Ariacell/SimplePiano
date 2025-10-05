#version 460

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D input_Tex;
uniform bool isSelected;

void main()
{
    vec4 selectedHue = vec4(0.0, 1.0, 0.0, 0.4);
    if (isSelected) {
    FragColor = texture(input_Tex, TexCoord) + selectedHue;
    } else {
    FragColor = texture(input_Tex, TexCoord);
    }
}