#version 330 core 

layout (location = 0) in vec2 position_data;
layout (location = 1) in vec4 color_data;

out vec4 colour_data;
uniform mat4 proj;
void main()
{
    gl_Position = proj * vec4(position_data,0.0f,1.0f);
    colour_data = color_data;
}