#version 330 core 

out vec4 FragColor;
in vec4 colour_data;
uniform float square_type;
void main()
{
    vec4 color_data = colour_data;
    FragColor = color_data;

    if(square_type == 1)
    {
        FragColor += vec4(0.0, 0.8, 0.0, 0.25);
    };
}