#version 330 core 

layout (location = 0) in vec2 position_data;
layout (location = 1) in vec2 coordinate_data;

out vec2 texture_data;

uniform mat4 proj;
void main()
{
    gl_Position = proj * vec4(position_data,0.0f,1.0f);
    texture_data = coordinate_data;
}