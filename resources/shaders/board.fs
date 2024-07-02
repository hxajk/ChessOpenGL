#version 330 core 

out vec4 FragColor;
in vec4 colour_data;


void main()
{
    vec4 color_data = colour_data;
    FragColor = color_data;
}